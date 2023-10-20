
#include "STM32F446xx.h"
#include "UART_prv.h"
#include "UART_int.h"
#include "Utils.h"
#include "ErrType.h"

USART_RegDef_t* USARTPeripheral [] = {USART1, USART2,USART3,UART4,UART5,USART6};


static uint8_t UART_vReadFlag(USART_HandleTypeDef_t* huart,USART_Flag_t copy_eUSART_Flag );
static void UART_vSetDataRegister(USART_HandleTypeDef_t* huart,uint8_t copy_u8Data );
static void UART_vReadDataRegister(USART_HandleTypeDef_t* huart,uint8_t* copy_pu8Data );
static void UART_vReceiverEnable(USART_HandleTypeDef_t* huart,USART_Receiver_Enable_t copy_eReceiver_Enable);
static void UART_vTransmitterEnable(USART_HandleTypeDef_t* huart,USART_Transmitter_Enable_t copy_eTransmitter_Enable);
static void UART_vIdleInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable);
static void UART_vRXNEInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable);
static void UART_vTransmissionCompleteInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable);
static void UART_vTXEInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable);
static void UART_vPEInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable);
static void UART_vSetParity(USART_HandleTypeDef_t* huart,USART_Parity_t copy_eParity);
static void UART_vEnableParity(USART_HandleTypeDef_t* huart,USART_Parity_Enable_t copy_eParity_Enable);
static void UART_vSetWordLength(USART_HandleTypeDef_t* huart,USART_WordLength_t copy_eWordLength);
static void UART_vEnale(USART_HandleTypeDef_t* huart,USART_Enable_t copy_eEnable);
static void UART_vSetOversamplingMode(USART_HandleTypeDef_t* huart,USART_Oversampling_Mode_t copy_eOversampling_Mode);
static void UART_vSetOneSampleBitMethod(USART_HandleTypeDef_t* huart,USART_One_sample_bit_method_t copy_eOne_sample_bit_method);
static void UART_vSetStopBits(USART_HandleTypeDef_t* huart,USART_STOP_bits_t copy_eSTOP_bits);
static void UART_vDMAEnablReceiver(USART_HandleTypeDef_t* huart,USART_DMA_enable_receiver_t copy_eDMA_enable_receiver);
static void UART_vDMAEnableTransmitter(USART_HandleTypeDef_t* huart,USART_DMA_enable_transmitter_t copy_eDMA_enable_transmitter);
static void UART_vEnableErrorInterrupt(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable);
static void UART_vSetBaudRate(USART_HandleTypeDef_t* huart,uint32_t copy_u32BaudRate);


void UART_vInit(USART_HandleTypeDef_t* huart)
{
	UART_vEnale(huart,huart->USARTEnable);
	UART_vReceiverEnable(huart,huart->RecieverEnable);
	UART_vTransmitterEnable(huart,huart->TransmitterEnable);
	UART_vDMAEnablReceiver(huart,huart->DMAEnableReciever);
	UART_vDMAEnableTransmitter(huart,huart->DMAEnableTransmitter);
	UART_vSetStopBits(huart,huart->NumberOfStopBits);
	UART_vEnableParity(huart,huart->ParityEnable);
	if (huart->ParityEnable == USART_Enable_Parity)
	{
		UART_vSetParity(huart,huart->ParityType);
	}
	UART_vSetWordLength(huart,huart->WordLength);
	UART_vSetOversamplingMode( huart,huart->OverSamplingMode);
	UART_vSetOneSampleBitMethod( huart,huart->OneSampleMethod);
	UART_vSetBaudRate( huart,huart->u32BaudRate);



	UART_vEnableErrorInterrupt(huart,huart->ErrorInterruptEnable);
	UART_vIdleInterruptEnable(huart, huart->IdleInterruptEnable);
	UART_vRXNEInterruptEnable(huart, huart->RXNEInterruptEnable);
	UART_vTransmissionCompleteInterruptEnable(huart, huart->TransmissionCompleteInterruptEnable);
	UART_vTXEInterruptEnable(huart, huart->TXEInterruptEnable);
	UART_vPEInterruptEnable(huart, huart->PEInterruptEnable);



}
void UART_vSendSynch(USART_HandleTypeDef_t* huart, uint8_t copy_u8Data)
{
	while (!UART_vReadFlag( huart,Transmit_Data_Register_Empty ));

	UART_vSetDataRegister( huart,copy_u8Data );

}
void UART_vSendStringSynch(USART_HandleTypeDef_t* huart, uint8_t* copy_pu8Data)
{
	for (uint8_t i=0;copy_pu8Data[i];i++)
	{
		while (	!UART_vReadFlag( huart,Transmit_Data_Register_Empty));
		UART_vSetDataRegister( huart,copy_pu8Data[i] );
	}

}

void UART_vReceiveSynch(USART_HandleTypeDef_t* huart, uint8_t *copy_u8Data)
{
	while (!UART_vReadFlag( huart,Read_Data_Register_Not_Empty));
	UART_vReadDataRegister( huart,copy_u8Data );
}
void UART_vReceiveSynchSize(USART_HandleTypeDef_t* huart, uint8_t *copy_u8Data, uint8_t copy_u8Size)
{
	uint8_t Temp_RecData=0;
	*copy_u8Data=0;
	for (uint8_t i =0 ;i<copy_u8Size; i++)
	{

	while (!UART_vReadFlag( huart,Read_Data_Register_Not_Empty));
	UART_vReadDataRegister( huart,&Temp_RecData );

	*copy_u8Data=(*copy_u8Data)*10+(Temp_RecData- '0');
	}
}

void UART_vReceiveSynchString(USART_HandleTypeDef_t* huart, uint8_t *copy_pu8Data)
{
	while (!UART_vReadFlag( huart,Read_Data_Register_Not_Empty));
	UART_vReadDataRegister( huart,&copy_pu8Data[0] );
	uint8_t i=0;
	while (copy_pu8Data[i] != 13)
	{
		i++;
		while (!UART_vReadFlag( huart,Read_Data_Register_Not_Empty));
		UART_vReadDataRegister( huart,&copy_pu8Data[i] );
	}
}
void UART_vSendAsynch(USART_HandleTypeDef_t* huart);
void UART_vReceiveAsynch(USART_HandleTypeDef_t* huart);


void UART_vSend_DMA(DMA_HandleTypeDef_t* hdma, uint32_t copy_u32SrcAddress, uint8_t copy_u32DataLength)
{
	DMA_vStart(hdma,(uint32_t)copy_u32SrcAddress, (uint32_t)0x40004404 , copy_u32DataLength);

}
void UART_vReceive_DMA(DMA_HandleTypeDef_t* hdma, uint32_t copy_u32DstAddress, uint8_t copy_u32DataLength)
{
	DMA_vStart(hdma,(uint32_t)0x40004404, (uint32_t)copy_u32DstAddress , copy_u32DataLength);
}


static uint8_t UART_vReadFlag(USART_HandleTypeDef_t* huart,USART_Flag_t copy_eUSART_Flag )
{
	return READ_BIT(USARTPeripheral[huart->USART_ID]->USART_SR,copy_eUSART_Flag);
}
static void UART_vSetDataRegister(USART_HandleTypeDef_t* huart,uint8_t copy_u8Data )
{
	USARTPeripheral[huart->USART_ID]->USART_DR=copy_u8Data;
}
static void UART_vReadDataRegister(USART_HandleTypeDef_t* huart,uint8_t* copy_pu8Data )
{
	*copy_pu8Data=USARTPeripheral[huart->USART_ID]->USART_DR;

}
static void UART_vReceiverEnable(USART_HandleTypeDef_t* huart,USART_Receiver_Enable_t copy_eReceiver_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_RE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eReceiver_Enable<<USART_CR1_RE);

}
static void UART_vTransmitterEnable(USART_HandleTypeDef_t* huart,USART_Transmitter_Enable_t copy_eTransmitter_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_TE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eTransmitter_Enable<<USART_CR1_TE);

}

static void UART_vIdleInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_IDLEIE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eInterrupt_Enable<<USART_CR1_IDLEIE);

}
static void UART_vRXNEInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_RXNEIE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eInterrupt_Enable<<USART_CR1_RXNEIE);

}

static void UART_vTransmissionCompleteInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_TCIE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eInterrupt_Enable<<USART_CR1_TCIE);

}
static void UART_vTXEInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_TXEIE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eInterrupt_Enable<<USART_CR1_TXEIE);

}
static void UART_vPEInterruptEnable(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_PEIE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eInterrupt_Enable<<USART_CR1_PEIE);

}

static void UART_vSetParity(USART_HandleTypeDef_t* huart,USART_Parity_t copy_eParity)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_PS);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eParity<<USART_CR1_PS);

}
static void UART_vEnableParity(USART_HandleTypeDef_t* huart,USART_Parity_Enable_t copy_eParity_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_PCE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eParity_Enable<<USART_CR1_PCE);

}

static void UART_vSetWordLength(USART_HandleTypeDef_t* huart,USART_WordLength_t copy_eWordLength)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_M);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eWordLength<<USART_CR1_M);

}

static void UART_vEnale(USART_HandleTypeDef_t* huart,USART_Enable_t copy_eEnable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_UE);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eEnable<<USART_CR1_UE);

}
static void UART_vSetOversamplingMode(USART_HandleTypeDef_t* huart,USART_Oversampling_Mode_t copy_eOversampling_Mode)
{
	USARTPeripheral[huart->USART_ID]->USART_CR1 &=~ (0b1<<USART_CR1_OVER8);
	USARTPeripheral[huart->USART_ID]->USART_CR1 |= (copy_eOversampling_Mode<<USART_CR1_OVER8);
}


static void UART_vSetStopBits(USART_HandleTypeDef_t* huart,USART_STOP_bits_t copy_eSTOP_bits)
{
	USARTPeripheral[huart->USART_ID]->USART_CR2 &=~ (0b11<<USART_CR2_STOP);
	USARTPeripheral[huart->USART_ID]->USART_CR2 |= (copy_eSTOP_bits<<USART_CR2_STOP);

}
static void UART_vSetOneSampleBitMethod(USART_HandleTypeDef_t* huart,USART_One_sample_bit_method_t copy_eOne_sample_bit_method)
{
	USARTPeripheral[huart->USART_ID]->USART_CR3 &=~ (0b1<<USART_CR3_ONEBIT);
	USARTPeripheral[huart->USART_ID]->USART_CR3 |= (copy_eOne_sample_bit_method<<USART_CR3_ONEBIT);
}

static void UART_vDMAEnablReceiver(USART_HandleTypeDef_t* huart,USART_DMA_enable_receiver_t copy_eDMA_enable_receiver)
{
	USARTPeripheral[huart->USART_ID]->USART_CR3 &=~ (0b1<<USART_CR3_DMAR);
	USARTPeripheral[huart->USART_ID]->USART_CR3 |= (copy_eDMA_enable_receiver<<USART_CR3_DMAR);

}

static void UART_vDMAEnableTransmitter(USART_HandleTypeDef_t* huart,USART_DMA_enable_transmitter_t copy_eDMA_enable_transmitter)
{
	USARTPeripheral[huart->USART_ID]->USART_CR3 &=~ (0b1<<USART_CR3_DMAT);
	USARTPeripheral[huart->USART_ID]->USART_CR3 |= (copy_eDMA_enable_transmitter<<USART_CR3_DMAT);

}

static void UART_vEnableErrorInterrupt(USART_HandleTypeDef_t* huart,USART_Interrupt_Enable_t copy_eInterrupt_Enable)
{
	USARTPeripheral[huart->USART_ID]->USART_CR3 &=~ (0b1<<USART_CR3_EIE);
	USARTPeripheral[huart->USART_ID]->USART_CR3 |= (copy_eInterrupt_Enable<<USART_CR3_EIE);

}

static void UART_vSetBaudRate(USART_HandleTypeDef_t* huart,uint32_t copy_u32BaudRate)
{
	uint8_t sampling =0;
	if(huart->OverSamplingMode == oversampling_by_16)
	{
		sampling=16;
	}
	else if (huart->OverSamplingMode == oversampling_by_8)
	{
		sampling=8;

	}
	uint32_t Result= (((uint64_t)16000000/16)*1000)/copy_u32BaudRate;
	uint32_t Mantissa= Result/1000; //Result / 1000;
	uint32_t Fraction= (((Result%1000) *sampling )+500)/1000; //((Result % 1000)*16 +500)/1000;

	USARTPeripheral[huart->USART_ID]->USART_BRR &=~ (0b1111<<0);
	USARTPeripheral[huart->USART_ID]->USART_BRR |= (Fraction<<0);

	USARTPeripheral[huart->USART_ID]->USART_BRR &=~ (0b111111111111<<4);
	USARTPeripheral[huart->USART_ID]->USART_BRR |= (Mantissa<<4);

}

