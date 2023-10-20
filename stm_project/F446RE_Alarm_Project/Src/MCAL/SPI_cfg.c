#include "DMA_int.h"
#include "SPI_int.h"
#include "STM32F446xx.h"
#include "Utils.h"
#include "GPIO_int.h"
#include "RCC_int.h"
#include "NVIC_int.h"

//
PinConfig_t SPI_PinSCK=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN5,
		.PIN_Type=ALTERNATE,
		.PIN_AF=AF5,
		.PIN_LCKSTS=UNLOCKED,

};
PinConfig_t SPI_PinMISO=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN6,
		.PIN_Type=ALTERNATE,
		.PIN_AF=AF5,
		.PIN_LCKSTS=UNLOCKED,

};
PinConfig_t SPI_PinMOSI=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN7,
		.PIN_Type=ALTERNATE,
		.PIN_AF=AF5,
		.PIN_LCKSTS=UNLOCKED,

};
PinConfig_t SPI_PinCS=
{
		.PIN_Port=PORTB,
		.PIN_Number=PIN6,
		.PIN_Type=ALTERNATE,
		.PIN_AF=AF5,
		.PIN_LCKSTS=UNLOCKED,

};
SPI_HandleTypeDef_t SPI_ourSPI =
{
		.SPI_ID=SPI_Channel1,
		.HWCRC_Enable=SPI_CRC_Disabled,
		.DataFrameFormat=_8_BitData,
		.SPI_Enable=SPI_Enable,
		.SPI_BaudRate=Fclk_over_64,
		.MasterSlaveSelection=SPI_Master,
		.SPI_DMARecEnable=eSPI_DMA_Rx_Disable,
		.SPI_DMATransEnable=eSPI_DMA_Tx_Disable,
		.SwMngSlaveEnable=SPI_SW_Mng_Enabled,
		.SwSlaveSelect=SPI_SlaveNotSelected,
		.TxBufferEmptyIE=SPI_Disable_Interrupt,
		.ErrorIE=SPI_Disable_Interrupt,
		.RxBufferNotEmptyIE=SPI_Disable_Interrupt,
};
DMA_HandleTypeDef_t SPI_DMA_Handle=
{
		.Init.Channel=channel_4,
		.Init.DMANumber=DMA_Number_1,
		.Init.Stream=Stream_5,
		.Init.Direction=peripheral_to_memory,
		.Init.MINC=memory_address_pointer_is_incremented_after_each_data_transfer,
		.Init.PINC=peripheral_address_pointer_is_fixed,
		.Init.CircularMode= circular_mode_enabled,
		.Init.PriorityLevel=high,
		.Init.DirectOrFIFOMode=direct_mode_enabled,
		.Init.MemoryBurst=single_transfer,
		.Init.PeripheralBurst=single_transfer,
		.Current_memory_target=current_target_memory_is_Memory_0,
		.double_buffer_mode=No_buffer_switching_at_the_end_of_transfer,
		.MemorySIZE=byte,
		.PeripheralSIZE=byte,

};








//
//PinConfig_t SPI_PinSCK=
//{
//		.PIN_Port=PORTA,
//		.PIN_Number=PIN5,
//		.PIN_Type=ALTERNATE,
//		.PIN_AF=AF5,
//		.PIN_LCKSTS=UNLOCKED,
//
//};
//PinConfig_t SPI_PinMISO=
//{
//		.PIN_Port=PORTA,
//		.PIN_Number=PIN6,
//		.PIN_Type=ALTERNATE,
//		.PIN_AF=AF5,
//		.PIN_LCKSTS=UNLOCKED,
//
//};
//PinConfig_t SPI_PinMOSI=
//{
//		.PIN_Port=PORTA,
//		.PIN_Number=PIN7,
//		.PIN_Type=ALTERNATE,
//		.PIN_AF=AF5,
//		.PIN_LCKSTS=UNLOCKED,
//
//};
//PinConfig_t SPI_PinCS=
//{
//		.PIN_Port=PORTB,
//		.PIN_Number=PIN6,
//		.PIN_Type=ALTERNATE,
//		.PIN_AF=AF5,
//		.PIN_LCKSTS=UNLOCKED,
//
//};
//SPI_HandleTypeDef_t SPI_ourSPI =
//{
//		.SPI_ID=SPI_Channel1,
//		.HWCRC_Enable=SPI_CRC_Disabled,
//		.DataFrameFormat=_8_BitData,
//		.SPI_Enable=SPI_Enable,
//		.SPI_BaudRate=Fclk_over_2,
//		.MasterSlaveSelection=0,
//		.SPI_DMARecEnable=eSPI_DMA_Rx_Disable,
//		.SPI_DMATransEnable=eSPI_DMA_Tx_Disable,
//		.SwMngSlaveEnable=SPI_SW_Mng_Enabled,
//		.SwSlaveSelect=0,
//		.TxBufferEmptyIE=SPI_Disable_Interrupt,
//		.ErrorIE=SPI_Disable_Interrupt,
//		.RxBufferNotEmptyIE=SPI_Disable_Interrupt,
//};
