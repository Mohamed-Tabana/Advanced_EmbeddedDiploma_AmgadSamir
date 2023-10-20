
#include "SPI_int.h"
#include "GPIO_int.h"
//
PinConfig_t PinMOSI=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN7,
		.PIN_Mode=INPUT,
		.PIN_InputType=Floating_input,
		.PIN_LCKSTS=UNLOCKED,

//				.PIN_Mode=Output_mode_max_speed_50_MHz,
//				.PIN_OutputType=Alternate_function_output_Push_pull,
//				.PIN_LCKSTS=UNLOCKED,
};
PinConfig_t PinMISO=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN6,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_OutputType=Alternate_function_output_Push_pull,
		.PIN_LCKSTS=UNLOCKED,

//		.PIN_Mode=Output_mode_max_speed_50_MHz,
//						.PIN_OutputType=Alternate_function_output_Push_pull,
//						.PIN_LCKSTS=UNLOCKED,


};
PinConfig_t PinSCK=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN5,
		.PIN_Mode=INPUT,
		.PIN_InputType=Floating_input,
		.PIN_LCKSTS=UNLOCKED,

//		.PIN_Mode=Output_mode_max_speed_50_MHz,
//						.PIN_OutputType=Alternate_function_output_Push_pull,
//						.PIN_LCKSTS=UNLOCKED,

};
//PinConfig_t PinCS=
//{
//		.PIN_Port=PORTB,
//		.PIN_Number=PIN12,
//		.PIN_Mode=Output_mode_max_speed_50_MHz,
//		.PIN_InputType=Alternate_function_output_Open_drain,
//		.PIN_LCKSTS=UNLOCKED,
//
//};

SPI_HandleTypeDef_t SPI_ourSPI =
{
		.SPI_ID=SPI_Channel1,
		.HWCRC_Enable=SPI_CRC_Disabled,
		.DataFrameFormat=_8_BitData,
		.SPI_Enable=SPI_Enable,
		.SPI_BaudRate=Fclk_over_2,
		.MasterSlaveSelection=SPI_Slave,
		.SPI_DMARecEnable=eSPI_DMA_Rx_Disable,
		.SPI_DMATransEnable=eSPI_DMA_Tx_Disable,

		.SwMngSlaveEnable=SPI_SW_Mng_Enabled,
		.SwSlaveSelect=SPI_SlaveSelected,

		.TxBufferEmptyIE=SPI_Disable_Interrupt,
		.ErrorIE=SPI_Disable_Interrupt,
		.RxBufferNotEmptyIE=SPI_Disable_Interrupt,
};











//
//PinConfig_t PinMOSI=
//{
//		.PIN_Port=PORTA,
//		.PIN_Number=PIN7,
//		.PIN_Mode=Output_mode_max_speed_50_MHz,
//		.PIN_OutputType=Alternate_function_output_Push_pull,
//		.PIN_LCKSTS=UNLOCKED,
//};
//PinConfig_t PinMISO=
//{
//		.PIN_Port=PORTA,
//		.PIN_Number=PIN6,
//				.PIN_Mode=INPUT,
//				.PIN_InputType=Floating_input,
//				.PIN_LCKSTS=UNLOCKED,
//
//
//
//};
//PinConfig_t PinSCK=
//{
//		.PIN_Port=PORTA,
//		.PIN_Number=PIN5,
//		.PIN_Mode=Output_mode_max_speed_50_MHz,
//		.PIN_OutputType=Alternate_function_output_Push_pull,
//		.PIN_LCKSTS=UNLOCKED,
//
//};
//
//
//SPI_HandleTypeDef_t SPI_ourSPI =
//{
//		.SPI_ID=SPI_Channel1,
//		.HWCRC_Enable=SPI_CRC_Disabled,
//		.DataFrameFormat=_8_BitData,
//		.SPI_Enable=SPI_Enable,
//		.SPI_BaudRate=Fclk_over_2,
//		.MasterSlaveSelection=1,
//		.SPI_DMARecEnable=eSPI_DMA_Rx_Disable,
//		.SPI_DMATransEnable=eSPI_DMA_Tx_Disable,
//
//		.SwMngSlaveEnable=SPI_SW_Mng_Enabled,
//		.SwSlaveSelect=1,
//
//		.TxBufferEmptyIE=SPI_Disable_Interrupt,
//		.ErrorIE=SPI_Disable_Interrupt,
//		.RxBufferNotEmptyIE=SPI_Disable_Interrupt,
//};
////
////
