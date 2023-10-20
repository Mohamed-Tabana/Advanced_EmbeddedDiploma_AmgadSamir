
#include "STM32F446xx.h"
#include "I2C_prv.h"
#include "I2C_int.h"
#include "Utils.h"
#include "ErrType.h"

static uint8_t I2C_ReadStatusFlag(I2C_HandleTypeDef_t* hi2c,I2C_Status_Flags copy_eStatusFlag);
static void I2C_DMA_TxCRxC_CallBack();
static void I2C_SetPeripheralEnable(I2C_HandleTypeDef_t* hi2c,I2C_Peripheral_Enable copy_eI2CEnable);
static void I2C_SetSMBusMode(I2C_HandleTypeDef_t* hi2c,I2C_SMBus_Mode copy_eSmBusMode);
static void I2C_SetSMBusType(I2C_HandleTypeDef_t* hi2c,I2C_SMBTYPE copy_eSMBTYPE);
static void I2C_SetARPEnable(I2C_HandleTypeDef_t* hi2c,I2C_ARP_Enable copy_eARPEnable);
static void I2C_SetPECEnable(I2C_HandleTypeDef_t* hi2c,I2C_PEC_Enable copy_ePECEnable);
static void I2C_SetGeneralCallEnable(I2C_HandleTypeDef_t* hi2c,I2C_General_Call_Enable copy_eGCEnable);
static void I2C_ClkStretchingEnable(I2C_HandleTypeDef_t* hi2c,I2C_STRETCH_Enable copy_eStretchEnable);
static void I2C_SetStartCondition(I2C_HandleTypeDef_t* hi2c,I2C_START_Generation copy_eStartCondition);
static void I2C_SetStopCondition(I2C_Peripheral_Channel copy_eI2C_channel,I2C_STOP_Generation copy_eStopCondition);
static void I2C_AckEnable(I2C_HandleTypeDef_t* hi2c,I2C_ACK_Enable copy_eAckEnable);
static void I2C_SetAckPos(I2C_HandleTypeDef_t* hi2c,I2C_POS_Options copy_eAckPos);
static void I2C_PECEnable(I2C_HandleTypeDef_t* hi2c,I2C_PEC_Options copy_ePECEnable);
static void I2C_SMBusAlertEnable(I2C_HandleTypeDef_t* hi2c,I2C_ALERT_Options copy_eAlertEnable);
static void I2C_SetSWReset(I2C_HandleTypeDef_t* hi2c,I2C_SWRESET copy_eSWReset);
static void I2C_SetI2CFreq(I2C_HandleTypeDef_t* hi2c,uint32_t copy_efreq);
static void I2C_ErrorInterruptEnable(I2C_HandleTypeDef_t* hi2c,I2C_InterruptEnable copy_eInterruptEnable);
static void I2C_EventInterruptEnable(I2C_HandleTypeDef_t* hi2c,I2C_InterruptEnable copy_eInterruptEnable);
static void I2C_BufferInterruptEnable(I2C_HandleTypeDef_t* hi2c,I2C_InterruptEnable copy_eInterruptEnable);
static void I2C_I2cDMAEnable(I2C_HandleTypeDef_t* hi2c,I2C_DMAEnable copy_eInterruptEnable);
static void I2C_DMANextTransferIsLast(I2C_HandleTypeDef_t* hi2c,I2C_DMALastTransfer copy_eLastTransfer);
static void I2C_SetAddressingMode(I2C_HandleTypeDef_t* hi2c,I2C_Addressing_Mode copy_eaddrMode);
static void I2C_SetInterfaceAddress7Bit(I2C_HandleTypeDef_t* hi2c,uint8_t copy_eInterfaceAdd);
static void I2C_SetDataRegister(I2C_HandleTypeDef_t* hi2c,uint8_t copy_u8Data);
static void I2C_ReadDataRegister(I2C_HandleTypeDef_t* hi2c,uint8_t* copy_pu8Data);
static void I2C_SetI2CMasterModer(I2C_HandleTypeDef_t* hi2c,I2C_Select_Master_Mode copy_eMasterMode);
static void I2C_SetCCRRegister(I2C_HandleTypeDef_t* hi2c,uint32_t copy_u32Data);
static void I2C_ClearAddrBit(I2C_HandleTypeDef_t* hi2c);
static void I2C_SetAddress(I2C_HandleTypeDef_t* hi2c,uint8_t copy_u8Data);

typedef enum
{
	I2C_InterruptSource_TX,
	I2C_InterruptSource_RX,


}I2C_InterruptSource;
I2C_InterruptSource I2C_IntSrc=3;


I2C_RegDef_t* I2CPeripheral [] = {I2C1, I2C2,I2C3};



void I2C_vInit(I2C_HandleTypeDef_t* hi2c)
{
	//	Stretching Enable/Disable
	I2C_ClkStretchingEnable(hi2c,hi2c->I2C_StretchClk);
	// set chip address
	I2C_SetAddress(hi2c,hi2c->I2C_InterfaceAddress);


	//Set SM
	I2C_SetI2CMasterModer(hi2c,hi2c->I2C_MasterMode);
	//Set FREQ
	I2C_SetI2CFreq(hi2c,42); //Revise me
	//Set CCR for 100KHZ CLK I2C
	I2C_SetCCRRegister(hi2c,80);//80


	/**
	 * Don't forget to Enable DMA transfer complete interrupt from peripheral and NVIC
	 *
	 * */

}
void I2C_SendDataToSlaveSynch(I2C_HandleTypeDef_t* hi2c, uint8_t copy_u8SlaveAdd,uint8_t copy_u8DataLength,uint8_t* copy_pu8Data)
{
	/*Enable I2C*/
	I2C_SetPeripheralEnable( hi2c,I2C_Peripheral_EN);

	/*bus id free*/
	while(I2C_ReadStatusFlag(hi2c,I2C_FLAG_BUS_BUSY_BUSY));

	/*Enable ACK*/
	//	I2C_AckEnable( hi2c,I2C_ACK_Enabled);

	/*1.Start Condition*/
	I2C_SetStartCondition(hi2c, I2C_START_Start);
	/*2. loop until SB generated*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_START_CONDITION_SB));
	//	temp1=I2CPeripheral[hi2c->I2C_ID]->I2C_SR1 ; //fix me

	/*3. Fill DR with Slave add*/
	I2C_SetDataRegister(hi2c,(copy_u8SlaveAdd<<1)|0);

	/*4. loop until ADDR generated (There is ACK from slave)*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_ADDRESS_SENT_ADDR));
	/*5. loop until TRA=Transmitter, We cleared Addr after sr1 and sr2 read*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_TRANSMITTER_RECEIVER_TRA));
	I2C_ClearAddrBit(hi2c);
	/* send All data*/
	for (uint8_t i=0;i<copy_u8DataLength;i++)
	{
		/*6. loop until buffer Empty*/
		while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_DATA_REG_EMPTY_TxE));
		/*7. Fill DR with Data*/
		I2C_SetDataRegister(hi2c,copy_pu8Data[i]);
		/*8. loop until BTF=1 so data is moved to bus*/
		while(!I2C_ReadStatusFlag(hi2c,I2C_BYTE_TRANSFER_FINISHED_BTF));
	}
	/*9. Send Stop Condition*/
	I2C_SetStopCondition( hi2c->I2C_ID,I2C_STOP_Stop);

}
/*
 * @brief: this function is used only for receiving Data >2
 *
 * */
void I2C_RequestDataFromSlaveSynch(I2C_HandleTypeDef_t* hi2c, uint8_t copy_u8SlaveAdd,uint8_t copy_u8DataLength,uint8_t* copy_pu8Data)
{
	/*Enable I2C*/
	I2C_SetPeripheralEnable( hi2c,I2C_Peripheral_EN);

	/*bus id free*/
	while(I2C_ReadStatusFlag(hi2c,I2C_FLAG_BUS_BUSY_BUSY));
	/*Enable ACK*/
	I2C_AckEnable( hi2c,I2C_ACK_Enabled);

	/*1.Start Condition*/
	I2C_SetStartCondition(hi2c, I2C_START_Start);
	/*2. loop until SB generated, read SR1*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_START_CONDITION_SB));

	/*3. Fill DR with Slave add, write DR so clear SB bit*/
	I2C_SetDataRegister(hi2c,(copy_u8SlaveAdd<<1)|1);
	/*4. loop until ADDR generated (There is ACK from slave)*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_ADDRESS_SENT_ADDR));
	/*5. loop until TRA=Receiver, We cleared Addr after sr1 and sr2 read*/
	while(I2C_ReadStatusFlag(hi2c,I2C_FLAG_TRANSMITTER_RECEIVER_TRA));
	I2C_ClearAddrBit(hi2c);


	/* Receive All data*/
	for (uint8_t i=0;i<copy_u8DataLength;i++)
	{
		if (i == copy_u8DataLength-1)
		{
			while(!I2C_ReadStatusFlag(hi2c,I2C_BYTE_TRANSFER_FINISHED_BTF));
			I2C_AckEnable( hi2c,I2C_ACK_Disabled);
		}
		/*7. loop until RxE=1 so data is moved to me as a master*/
		while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_DATA_REG_FULL_RxNE));
		/*6. bring DR with Data*/
		I2C_ReadDataRegister(hi2c,copy_pu8Data+i);
		/*8. loop until BTF=1 so data is moved to bus*/
		while(!I2C_ReadStatusFlag(hi2c,I2C_BYTE_TRANSFER_FINISHED_BTF));

		if (i == copy_u8DataLength-1)
		{
			/*8. Send Stop Condition*/
			I2C_SetStopCondition( hi2c->I2C_ID,I2C_STOP_Stop);
		}
	}
}
void I2C_SendDataToSlave_DMA(I2C_HandleTypeDef_t* hi2c, DMA_HandleTypeDef_t* copy_eDMAConfig,uint8_t copy_u8SlaveAdd,uint32_t copy_u32DataLength,uint8_t* copy_pu8Data)
{
	I2C_IntSrc=I2C_InterruptSource_TX;
	/*Enable  Peripheral*/
	I2C_SetPeripheralEnable( hi2c,I2C_Peripheral_EN);

	/*bus id free*/
	while(I2C_ReadStatusFlag(hi2c,I2C_FLAG_BUS_BUSY_BUSY));
	/*Enable  DMA*/
	I2C_I2cDMAEnable( hi2c,I2C_DMA_Enable);

	/*Enable ACK*/
	//	I2C_AckEnable( hi2c,I2C_ACK_Enabled);

	/*1.Start Condition*/
	I2C_SetStartCondition(hi2c, I2C_START_Start);
	/*2. loop until SB generated*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_START_CONDITION_SB));

	/*3. Fill DR with Slave add*/
	I2C_SetDataRegister(hi2c,(copy_u8SlaveAdd<<1)|0);
	/*4. loop until ADDR generated (There is ACK from slave)*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_ADDRESS_SENT_ADDR));
	/*5. loop until TRA=Transmitter, We cleared Addr after sr1 and sr2 read*/
	//	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_TRANSMITTER_RECEIVER_TRA));
	I2C_ClearAddrBit(hi2c);
	DMA_vSetCallBack(copy_eDMAConfig,Transfer_complete_Interrupt, I2C_DMA_TxCRxC_CallBack);

	DMA_vStart_IT(copy_eDMAConfig,(uint32_t) copy_pu8Data,(uint32_t) &I2CPeripheral[hi2c->I2C_ID]->I2C_DR , copy_u32DataLength);



}
void I2C_ReceiveDataFromSlave_DMA(I2C_HandleTypeDef_t* hi2c, DMA_HandleTypeDef_t* copy_eDMAConfig,uint8_t copy_u8SlaveAdd,uint32_t copy_u32DataLength,uint8_t* copy_pu8Data)
{
	I2C_IntSrc=I2C_InterruptSource_RX;
	I2C_SetPeripheralEnable( hi2c,I2C_Peripheral_EN);

	/*bus id free*/
	while(I2C_ReadStatusFlag(hi2c,I2C_FLAG_BUS_BUSY_BUSY));
	/*Enable ACK and automatically NACK for DMA*/
	I2C_DMANextTransferIsLast( hi2c,I2C_Next_Is_Last);
	if (copy_u32DataLength == 1)
	{
		I2C_AckEnable( hi2c,I2C_ACK_Disabled);
	}
	else
	{
		I2C_AckEnable( hi2c,I2C_ACK_Enabled);
	}
	/*Enable I2C and DA*/
	I2C_I2cDMAEnable( hi2c,I2C_DMA_Enable);

	/*1.Start Condition*/
	I2C_SetStartCondition(hi2c, I2C_START_Start);
	/*2. loop until SB generated*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_START_CONDITION_SB));

	/*3. Fill DR with Slave add*/
	I2C_SetDataRegister(hi2c,(copy_u8SlaveAdd<<1)|1);
	/*4. loop until ADDR generated (There is ACK from slave)*/
	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_ADDRESS_SENT_ADDR));
	/*5. loop until TRA=Transmitter, We cleared Addr after sr1 and sr2 read*/
	//	while(!I2C_ReadStatusFlag(hi2c,I2C_FLAG_TRANSMITTER_RECEIVER_TRA));
	I2C_ClearAddrBit(hi2c);
	DMA_vSetCallBack(copy_eDMAConfig,Transfer_complete_Interrupt, I2C_DMA_TxCRxC_CallBack);

	DMA_vStart(copy_eDMAConfig, (uint32_t) &I2CPeripheral[hi2c->I2C_ID]->I2C_DR,(uint32_t) copy_pu8Data , copy_u32DataLength);


}


/***************
 *
 * STATIC Functions
 *
 *
 *
 */
static uint8_t I2C_ReadStatusFlag(I2C_HandleTypeDef_t* hi2c,I2C_Status_Flags copy_eStatusFlag)
{
	if (copy_eStatusFlag<32)
	{
		return (READ_BIT(I2CPeripheral[hi2c->I2C_ID]->I2C_SR1,copy_eStatusFlag));
	}
	// here i made the flags for SR2 starts from 32 to differentiate between them and SR1
	else
	{
		return (READ_BIT(I2CPeripheral[hi2c->I2C_ID]->I2C_SR2,(copy_eStatusFlag-32)));

	}
}

static void I2C_DMA_TxCRxC_CallBack()
{

	if(I2C_IntSrc==I2C_InterruptSource_TX)
	{
		//Disable DMA
		I2C_I2cDMAEnable( I2C_Channel_1,I2C_DMA_Disable);

		// if transmission
		uint8_t cc=0;
		while(!I2C_ReadStatusFlag(I2C_Channel_1,I2C_FLAG_DATA_REG_EMPTY_TxE) && cc<50)			//FIXME
		{
			cc++;
		}

	}
	else if (I2C_IntSrc== I2C_InterruptSource_RX)
	{
		//Disable DMA
		I2C_I2cDMAEnable( I2C_Channel_1,I2C_DMA_Disable);

		while(I2C_ReadStatusFlag(I2C_Channel_1,I2C_FLAG_DATA_REG_FULL_RxNE)); //FIXME

	}

	// configure this
	I2C_SetStopCondition( I2C_Channel_1,I2C_STOP_Stop);

}

static void I2C_SetPeripheralEnable(I2C_HandleTypeDef_t* hi2c,I2C_Peripheral_Enable copy_eI2CEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_PE);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eI2CEnable<<I2C_CR1_PE);
}

static void I2C_SetSMBusMode(I2C_HandleTypeDef_t* hi2c,I2C_SMBus_Mode copy_eSmBusMode)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_SMBUS);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eSmBusMode<<I2C_CR1_SMBUS);
}

static void I2C_SetSMBusType(I2C_HandleTypeDef_t* hi2c,I2C_SMBTYPE copy_eSMBTYPE)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_SMBTYPE);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eSMBTYPE<<I2C_CR1_SMBTYPE);
}

static void I2C_SetARPEnable(I2C_HandleTypeDef_t* hi2c,I2C_ARP_Enable copy_eARPEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_ENARP);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eARPEnable<<I2C_CR1_ENARP);
}

static void I2C_SetPECEnable(I2C_HandleTypeDef_t* hi2c,I2C_PEC_Enable copy_ePECEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_ENPEC);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_ePECEnable<<I2C_CR1_ENPEC);
}

static void I2C_SetGeneralCallEnable(I2C_HandleTypeDef_t* hi2c,I2C_General_Call_Enable copy_eGCEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_ENGC);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eGCEnable<<I2C_CR1_ENGC);
}

static void I2C_ClkStretchingEnable(I2C_HandleTypeDef_t* hi2c,I2C_STRETCH_Enable copy_eStretchEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_NOSTRETCH);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eStretchEnable<<I2C_CR1_NOSTRETCH);
}

static void I2C_SetStartCondition(I2C_HandleTypeDef_t* hi2c,I2C_START_Generation copy_eStartCondition)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_START);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eStartCondition<<I2C_CR1_START);
}

static void I2C_SetStopCondition(I2C_Peripheral_Channel copy_eI2C_channel,I2C_STOP_Generation copy_eStopCondition)
{
	I2CPeripheral[copy_eI2C_channel]->I2C_CR1 &=~ (0b1<<I2C_CR1_STOP);
	I2CPeripheral[copy_eI2C_channel]->I2C_CR1 |= (copy_eStopCondition<<I2C_CR1_STOP);
}

static void I2C_AckEnable(I2C_HandleTypeDef_t* hi2c,I2C_ACK_Enable copy_eAckEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_ACK);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eAckEnable<<I2C_CR1_ACK);
}
static void I2C_SetAckPos(I2C_HandleTypeDef_t* hi2c,I2C_POS_Options copy_eAckPos)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_POS);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eAckPos<<I2C_CR1_POS);
}

static void I2C_PECEnable(I2C_HandleTypeDef_t* hi2c,I2C_PEC_Options copy_ePECEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_PEC);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_ePECEnable<<I2C_CR1_PEC);
}

static void I2C_SMBusAlertEnable(I2C_HandleTypeDef_t* hi2c,I2C_ALERT_Options copy_eAlertEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_ALERT);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eAlertEnable<<I2C_CR1_ALERT);
}

static void I2C_SetSWReset(I2C_HandleTypeDef_t* hi2c,I2C_SWRESET copy_eSWReset)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 &=~ (0b1<<I2C_CR1_SWRST);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR1 |= (copy_eSWReset<<I2C_CR1_SWRST);
}

static void I2C_SetI2CFreq(I2C_HandleTypeDef_t* hi2c,uint32_t copy_efreq)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 &=~ (0b111111<<I2C_CR2_Freq0_5);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 |= (copy_efreq<<I2C_CR2_Freq0_5);
}

static void I2C_ErrorInterruptEnable(I2C_HandleTypeDef_t* hi2c,I2C_InterruptEnable copy_eInterruptEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 &=~ (0b1<<I2C_CR2_ITERREN);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 |= (copy_eInterruptEnable<<I2C_CR2_ITERREN);
}
static void I2C_EventInterruptEnable(I2C_HandleTypeDef_t* hi2c,I2C_InterruptEnable copy_eInterruptEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 &=~ (0b1<<I2C_CR2_ITEVTEN);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 |= (copy_eInterruptEnable<<I2C_CR2_ITEVTEN);
}

static void I2C_BufferInterruptEnable(I2C_HandleTypeDef_t* hi2c,I2C_InterruptEnable copy_eInterruptEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 &=~ (0b1<<I2C_CR2_ITBUFEN);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 |= (copy_eInterruptEnable<<I2C_CR2_ITBUFEN);
}


static void I2C_I2cDMAEnable(I2C_HandleTypeDef_t* hi2c,I2C_DMAEnable copy_eInterruptEnable)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 &=~ (0b1<<I2C_CR2_DMAEN);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 |= (copy_eInterruptEnable<<I2C_CR2_DMAEN);
}

static void I2C_DMANextTransferIsLast(I2C_HandleTypeDef_t* hi2c,I2C_DMALastTransfer copy_eLastTransfer)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 &=~ (0b1<<I2C_CR2_LAST);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CR2 |= (copy_eLastTransfer<<I2C_CR2_LAST);
}

static void I2C_SetAddressingMode(I2C_HandleTypeDef_t* hi2c,I2C_Addressing_Mode copy_eaddrMode)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_OAR1 &=~ (0b1<<I2C_OAR1_ADDMODE);
	I2CPeripheral[hi2c->I2C_ID]->I2C_OAR1 |= (copy_eaddrMode<<I2C_OAR1_ADDMODE);
}

static void I2C_SetInterfaceAddress7Bit(I2C_HandleTypeDef_t* hi2c,uint8_t copy_eInterfaceAdd)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_OAR1 &=~ (0b1111111<<I2C_OAR1_ADD7_1);
	I2CPeripheral[hi2c->I2C_ID]->I2C_OAR1 |= (copy_eInterfaceAdd<<I2C_OAR1_ADD7_1);
}
static void I2C_SetDataRegister(I2C_HandleTypeDef_t* hi2c,uint8_t copy_u8Data)
{
	I2CPeripheral[hi2c->I2C_ID]->I2C_DR = copy_u8Data;
}
static void I2C_ReadDataRegister(I2C_HandleTypeDef_t* hi2c,uint8_t* copy_pu8Data)
{

	* copy_pu8Data=I2CPeripheral[hi2c->I2C_ID]->I2C_DR ;
}

static void I2C_SetI2CMasterModer(I2C_HandleTypeDef_t* hi2c,I2C_Select_Master_Mode copy_eMasterMode)
{

	I2CPeripheral[hi2c->I2C_ID]->I2C_CCR &=~ (0b1<<I2C_CCR_MASTERMODE);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CCR |= (copy_eMasterMode<<I2C_CCR_MASTERMODE);
}
static void I2C_SetCCRRegister(I2C_HandleTypeDef_t* hi2c,uint32_t copy_u32Data)
{

	I2CPeripheral[hi2c->I2C_ID]->I2C_CCR &=~ (0b111111111111<<0);
	I2CPeripheral[hi2c->I2C_ID]->I2C_CCR |= (copy_u32Data<<0);

	I2CPeripheral[hi2c->I2C_ID]->I2C_TRISE &=~ (0b111111<<0);
	I2CPeripheral[hi2c->I2C_ID]->I2C_TRISE |= (0x2B<<0);


}

static void I2C_ClearAddrBit(I2C_HandleTypeDef_t* hi2c)
{
	uint32_t temp1=0;
	uint32_t temp2=0;

	temp1=I2CPeripheral[hi2c->I2C_ID]->I2C_SR1 ;
	temp2=I2CPeripheral[hi2c->I2C_ID]->I2C_SR2 ;
}


static void I2C_SetAddress(I2C_HandleTypeDef_t* hi2c,uint8_t copy_u8Data)
{

	//	I2CPeripheral[hi2c->I2C_ID]->I2C_OAR1 &=~ (0b11111111<<1);
	//	I2CPeripheral[hi2c->I2C_ID]->I2C_OAR1 |= (copy_u8Data<<1);
	I2CPeripheral[hi2c->I2C_ID]->I2C_OAR1 |= (0x4000);

}


