#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "SPI_prv.h"
#include "stdint.h"
#include "STM32F103.h"
#include "Utils.h"


typedef enum
{
	SPI_Channel1,
	SPI_Channel2,
	SPI_Channel3,
}SPI_Channel_t;

typedef enum
{
	Two_line_unidirectional_data_mode,
	One_line_bidirectional_data_mode
}SPI_BidirectionalMode_t;
typedef enum
{
	Output_disabled,
	Output_enabled
}SPI_OutputEnableInBidirectional_t;
typedef enum
{
	SPI_CRC_Disabled,
	SPI_CRC_Enabled
}SPI_HWCRCEnable_t;

typedef enum
{
	_8_BitData,
	_16_BitData
}SPI_DataFrameFormat_t;


typedef enum
{
	SPI_full_duplex,
	SPI_Output_disabled
}SPI_ReceiveOnlyModeEnable_t;


typedef enum
{
	SPI_SW_Mng_Disabled,
	SPI_SW_Mng_Enabled
}SPI_SWSlaveMng_t;

typedef enum
{
	SPI_SlaveSelected,
	SPI_SlaveNotSelected
}SPI_InternalSlaveSelect_t;

typedef enum
{
	MSB_transmitted_first,
	LSB_transmitted_first
}SPI_LSBFirst_t;


typedef enum
{
	SPI_Disable,
	SPI_Enable
}SPI_Enable_t;

typedef enum
{
	Fclk_over_2,
	Fclk_over_4,
	Fclk_over_8,
	Fclk_over_16,
	Fclk_over_32,
	Fclk_over_64,
	Fclk_over_128,
	Fclk_over_256,

}SPI_BaudRate_t;

typedef enum
{
	SPI_Slave,
	SPI_Master,
}SPI_MasterSlave_t;

typedef enum
{
	Zero_Idle,
	One_Idle,
}SPI_ClockPolarity_t;

typedef enum
{
	The_first_clock_transition_is_the_first_data_capture_edge,
	The_second_clock_transition_is_the_first_data_capture_edge,
}SPI_ClockPhase_t;




typedef enum
{
	SPI_Disable_Interrupt,
	SPI_Enable_Interrupt,
}SPI_InterruptEnable_t;

typedef enum
{
	SPI_SSOutputDisable,
	SPI_SSOutputEnable,
}SPI_SSOutputEnable_t;


typedef enum
{
	eSPI_DMA_Tx_Disable,
	eSPI_DMA_Tx_Enable,
}SPI_DMATxEnable_t;


typedef enum
{
	eSPI_DMA_Rx_Disable,
	eSPI_DMA_Rx_Enable,
}SPI_DMARxEnable_t;

typedef enum
{
	SPI_RXBufferFull,
	SPI_TXBufferEmpty,
	SPI_UnderrunFlag=3,
	SPI_CRCErrorFlag,
	SPI_ModeFault,
	SPI_OverrunFlag,
	SPI_BusyFlag,
}SPI_Flags_t;

typedef struct
{
	SPI_Channel_t SPI_ID ;
	SPI_HWCRCEnable_t HWCRC_Enable;
	SPI_DataFrameFormat_t DataFrameFormat;
	SPI_Enable_t SPI_Enable;
	SPI_BaudRate_t SPI_BaudRate;
	SPI_MasterSlave_t MasterSlaveSelection;
	SPI_DMARxEnable_t SPI_DMARecEnable;
	SPI_DMATxEnable_t SPI_DMATransEnable;

	SPI_SWSlaveMng_t SwMngSlaveEnable;
	SPI_InternalSlaveSelect_t SwSlaveSelect;

	SPI_InterruptEnable_t TxBufferEmptyIE;
	SPI_InterruptEnable_t RxBufferNotEmptyIE;
	SPI_InterruptEnable_t ErrorIE;
}SPI_HandleTypeDef_t;

void SPI_vInit(SPI_HandleTypeDef_t* hspi);
void SPI_vSendSynch(SPI_HandleTypeDef_t* hspi, uint8_t copy_u8Data);
void SPI_vReceiveSynch(SPI_HandleTypeDef_t* hspi, uint8_t *copy_u8Data);
void SPI_vSendReceive(SPI_HandleTypeDef_t* hspi,uint8_t *copy_pu8RecData, uint8_t copy_pu8SendData);
void SPI_vSendAsynch(SPI_HandleTypeDef_t* hspi);
void SPI_vReceiveAsynch(SPI_HandleTypeDef_t* hspi);


void SPI_EnableTxBufferEmptyInterrupt(SPI_Channel_t spi_id,SPI_InterruptEnable_t copy_eInterruptEnable);
void SPI_EnableRxBufferFullInterrupt(SPI_HandleTypeDef_t* hspi,SPI_InterruptEnable_t copy_eInterruptEnable);
void SPI_EnableErrorInterrupt(SPI_HandleTypeDef_t* hspi,SPI_InterruptEnable_t copy_eInterruptEnable);
uint8_t SPI_ReadFlag(SPI_HandleTypeDef_t* hspi,SPI_Flags_t copy_eFlag);




#endif
