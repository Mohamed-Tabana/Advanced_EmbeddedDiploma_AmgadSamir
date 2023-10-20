
#include "STM32F103.h"
#include "SPI_prv.h"
#include "SPI_int.h"
#include "Utils.h"
#include "ErrType.h"

SPI_RegDef_t* SPIPeripheral [] = {SPI1, SPI2,SPI3};


//static void SPI_SetBidirectionalMode(SPI_HandleTypeDef_t* hspi,SPI_BidirectionalMode_t copy_eSPI_BidirectionalMode);
//static void SPI_SetOutputEnableInBidirectional(SPI_HandleTypeDef_t* hspi,SPI_OutputEnableInBidirectional_t copy_eOutputEnableInBidirectional);
static void SPI_SetHWCRCEnable(SPI_HandleTypeDef_t* hspi,SPI_HWCRCEnable_t copy_eHWCRCEnable);
static void SPI_SetDataFrameForamt(SPI_HandleTypeDef_t* hspi,SPI_DataFrameFormat_t copy_eDataFrameFormat);
//static void SPI_SetReceiveOnlyEnable(SPI_HandleTypeDef_t* hspi,SPI_ReceiveOnlyModeEnable_t copy_eReceiveOnlyModeEnable);
static void SPI_SetSlavengBySW(SPI_HandleTypeDef_t* hspi,SPI_SWSlaveMng_t copy_eSWSlaveMng);
static void SPI_SetSlaveSelectBySW(SPI_HandleTypeDef_t* hspi,SPI_InternalSlaveSelect_t copy_eInternalSlaveSelect);
//static void SPI_SetLSB_MSB_First(SPI_HandleTypeDef_t* hspi,SPI_LSBFirst_t copy_eSPI_LSBFirst);
static void SPI_Enable_Peripheral(SPI_HandleTypeDef_t* hspi,SPI_Enable_t copy_eSPI_Enable);
static void SPI_SetBaudRate(SPI_HandleTypeDef_t* hspi,SPI_BaudRate_t copy_eSPI_BaudRate);
static void SPI_SetMasterSlave(SPI_HandleTypeDef_t* hspi,SPI_MasterSlave_t copy_eMasterSlave);
//static void SPI_SetClockPolarity(SPI_HandleTypeDef_t* hspi,SPI_ClockPolarity_t copy_eClockPolarity);
//static void SPI_SetClockPhase(SPI_HandleTypeDef_t* hspi,SPI_ClockPhase_t copy_eClockPhase);
//static void SPI_SetSSOOutputEnable(SPI_HandleTypeDef_t* hspi,SPI_SSOutputEnable_t copy_eSSOutputEnable);
static void SPI_DMATxEnable(SPI_HandleTypeDef_t* hspi,SPI_DMATxEnable_t copy_eDMATxEnable);
static void SPI_DMARxEnable(SPI_HandleTypeDef_t* hspi,SPI_DMARxEnable_t copy_eDMARxEnable);





void SPI_vInit(SPI_HandleTypeDef_t* hspi)
{
	SPI_SetHWCRCEnable( hspi,hspi->HWCRC_Enable);
	SPI_SetDataFrameForamt( hspi,hspi->DataFrameFormat);
	SPI_SetBaudRate( hspi,hspi->SPI_BaudRate);
	SPI_SetMasterSlave( hspi,hspi->MasterSlaveSelection);

	SPI_DMATxEnable( hspi,hspi->SPI_DMATransEnable);
	SPI_DMARxEnable( hspi,hspi->SPI_DMARecEnable);

	SPI_SetSlavengBySW( hspi,hspi->SwMngSlaveEnable);
    SPI_SetSlaveSelectBySW( hspi,hspi->SwSlaveSelect);


	SPI_EnableTxBufferEmptyInterrupt( hspi->SPI_ID,hspi->TxBufferEmptyIE);
	SPI_EnableRxBufferFullInterrupt( hspi,hspi->RxBufferNotEmptyIE);
	SPI_EnableErrorInterrupt( hspi,hspi->ErrorIE);

	SPI_Enable_Peripheral( hspi,hspi->SPI_Enable);
}
void SPI_vSendSynch(SPI_HandleTypeDef_t* hspi, uint8_t copy_u8Data)
{

	SPIPeripheral[hspi->SPI_ID]->SPI_DR= copy_u8Data;

	while (!SPI_ReadFlag( hspi,SPI_TXBufferEmpty));

}
void SPI_vReceiveSynch(SPI_HandleTypeDef_t* hspi, uint8_t *copy_u8Data)
{
	while (!SPI_ReadFlag( hspi,SPI_RXBufferFull));

	*copy_u8Data=SPIPeripheral[hspi->SPI_ID]->SPI_DR ;

}
void SPI_vSendAsynch(SPI_HandleTypeDef_t* hspi);
void SPI_vReceiveAsynch(SPI_HandleTypeDef_t* hspi);

void SPI_vSendReceive(SPI_HandleTypeDef_t* hspi,uint8_t *copy_pu8RecData, uint8_t copy_pu8SendData)
{

	SPIPeripheral[hspi->SPI_ID]->SPI_DR= copy_pu8SendData;

	while(!SPI_ReadFlag( hspi,SPI_RXBufferFull)){};

	 *copy_pu8RecData=SPIPeripheral[hspi->SPI_ID]->SPI_DR;
}



//static void SPI_SetBidirectionalMode(SPI_HandleTypeDef_t* hspi,SPI_BidirectionalMode_t copy_eSPI_BidirectionalMode)
//{
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_BIDIMODE);
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eSPI_BidirectionalMode<<SPI_CR1_BIDIMODE);
//}
//
//static void SPI_SetOutputEnableInBidirectional(SPI_HandleTypeDef_t* hspi,SPI_OutputEnableInBidirectional_t copy_eOutputEnableInBidirectional)
//{
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_BIDIOE);
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eOutputEnableInBidirectional<<SPI_CR1_BIDIOE);
//}
static void SPI_SetHWCRCEnable(SPI_HandleTypeDef_t* hspi,SPI_HWCRCEnable_t copy_eHWCRCEnable)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_CRCEN);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eHWCRCEnable<<SPI_CR1_CRCEN);
}

static void SPI_SetDataFrameForamt(SPI_HandleTypeDef_t* hspi,SPI_DataFrameFormat_t copy_eDataFrameFormat)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_DFF);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eDataFrameFormat<<SPI_CR1_DFF);
}

//static void SPI_SetReceiveOnlyEnable(SPI_HandleTypeDef_t* hspi,SPI_ReceiveOnlyModeEnable_t copy_eReceiveOnlyModeEnable)
//{
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_RXONLY);
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eReceiveOnlyModeEnable<<SPI_CR1_RXONLY);
//}
//
static void SPI_SetSlavengBySW(SPI_HandleTypeDef_t* hspi,SPI_SWSlaveMng_t copy_eSWSlaveMng)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_SSM);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eSWSlaveMng<<SPI_CR1_SSM);
}

static void SPI_SetSlaveSelectBySW(SPI_HandleTypeDef_t* hspi,SPI_InternalSlaveSelect_t copy_eInternalSlaveSelect)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_SSI);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eInternalSlaveSelect<<SPI_CR1_SSI);
}
//
//static void SPI_SetLSB_MSB_First(SPI_HandleTypeDef_t* hspi,SPI_LSBFirst_t copy_eSPI_LSBFirst)
//{
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_LSBFIRST);
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eSPI_LSBFirst<<SPI_CR1_LSBFIRST);
//}

static void SPI_Enable_Peripheral(SPI_HandleTypeDef_t* hspi,SPI_Enable_t copy_eSPI_Enable)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_SPE);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eSPI_Enable<<SPI_CR1_SPE);
}

static void SPI_SetBaudRate(SPI_HandleTypeDef_t* hspi,SPI_BaudRate_t copy_eSPI_BaudRate)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b111<<SPI_CR1_BR);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eSPI_BaudRate<<SPI_CR1_BR);
}

static void SPI_SetMasterSlave(SPI_HandleTypeDef_t* hspi,SPI_MasterSlave_t copy_eMasterSlave)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_MSTR);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eMasterSlave<<SPI_CR1_MSTR);
}

//static void SPI_SetClockPolarity(SPI_HandleTypeDef_t* hspi,SPI_ClockPolarity_t copy_eClockPolarity)
//{
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_CPOL);
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eClockPolarity<<SPI_CR1_CPOL);
//}

//static void SPI_SetClockPhase(SPI_HandleTypeDef_t* hspi,SPI_ClockPhase_t copy_eClockPhase)
//{
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 &=~ (0b1<<SPI_CR1_CPHA);
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR1 |= (copy_eClockPhase<<SPI_CR1_CPHA);
//}


 void SPI_EnableTxBufferEmptyInterrupt(SPI_Channel_t spi_id,SPI_InterruptEnable_t copy_eInterruptEnable)
{
	SPIPeripheral[spi_id]->SPI_CR2 &=~ (0b1<<SPI_CR2_TXEIE);
	SPIPeripheral[spi_id]->SPI_CR2 |= (copy_eInterruptEnable<<SPI_CR2_TXEIE);
}
 void SPI_EnableRxBufferFullInterrupt(SPI_HandleTypeDef_t* hspi,SPI_InterruptEnable_t copy_eInterruptEnable)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 &=~ (0b1<<SPI_CR2_RXNEIE);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 |= (copy_eInterruptEnable<<SPI_CR2_RXNEIE);
}
 void SPI_EnableErrorInterrupt(SPI_HandleTypeDef_t* hspi,SPI_InterruptEnable_t copy_eInterruptEnable)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 &=~ (0b1<<SPI_CR2_ERRIE);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 |= (copy_eInterruptEnable<<SPI_CR2_ERRIE);
}




//static void SPI_SetSSOOutputEnable(SPI_HandleTypeDef_t* hspi,SPI_SSOutputEnable_t copy_eSSOutputEnable)
//{
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 &=~ (0b1<<SPI_CR2_SSOE);
//	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 |= (copy_eSSOutputEnable<<SPI_CR2_SSOE);
//}

static void SPI_DMATxEnable(SPI_HandleTypeDef_t* hspi,SPI_DMATxEnable_t copy_eDMATxEnable)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 &=~ (0b1<<SPI_CR2_TXDMAEN);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 |= (copy_eDMATxEnable<<SPI_CR2_TXDMAEN);
}

static void SPI_DMARxEnable(SPI_HandleTypeDef_t* hspi,SPI_DMARxEnable_t copy_eDMARxEnable)
{
	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 &=~ (0b1<<SPI_CR2_RXDMAEN);
	SPIPeripheral[hspi->SPI_ID]->SPI_CR2 |= (copy_eDMARxEnable<<SPI_CR2_RXDMAEN);
}

 uint8_t SPI_ReadFlag(SPI_HandleTypeDef_t* hspi,SPI_Flags_t copy_eFlag)
{
	return READ_BIT(SPIPeripheral[hspi->SPI_ID]->SPI_SR,copy_eFlag);
}

