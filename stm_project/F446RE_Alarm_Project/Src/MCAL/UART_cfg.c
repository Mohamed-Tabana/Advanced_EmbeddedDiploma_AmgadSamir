
#include "DMA_int.h"
#include "UART_int.h"
#include "STM32F446xx.h"
#include "Utils.h"
#include "GPIO_int.h"
#include "RCC_int.h"
#include "NVIC_int.h"

// UART Pins Handle
PinConfig_t UART_PINTX=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN2,
		.PIN_Type=ALTERNATE,
		.PIN_AF=AF7,
		.PIN_LCKSTS=UNLOCKED,

};
PinConfig_t UART_PINRX=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN3,
		.PIN_Type=ALTERNATE,
		.PIN_AF=AF7,
		.PIN_LCKSTS=UNLOCKED,

};
// UART Handle
USART_HandleTypeDef_t UART_ourUsart =
{
		.USART_ID=USART_2,
		.USARTEnable=USART_Enable,
		.TransmitterEnable=USART_Transmitter_Enable,
		.RecieverEnable=USART_Receiver_Enable,
		.DMAEnableTransmitter=DMA_enabled_for_transmission,
		.DMAEnableReciever=DMA_enabled_for_reception,
		.NumberOfStopBits=One_Stop_bit,
		.ParityEnable=USART_Disable_Parity,

		.WordLength=one_Start_bit_8_Data_bits,
		.OneSampleMethod=Three_sample_bit_method,
		.OverSamplingMode=oversampling_by_16,
		.u32BaudRate=9600,
		.RXNEInterruptEnable=USART_Interrupt_Enable,
		.PEInterruptEnable=USART_Interrupt_Disable,
		.TXEInterruptEnable=USART_Interrupt_Disable,
		.TransmissionCompleteInterruptEnable=USART_Interrupt_Disable,
		.IdleInterruptEnable=USART_Interrupt_Disable,
		.ErrorInterruptEnable=USART_Interrupt_Disable
};
// DMA Handle
DMA_HandleTypeDef_t UART_DMA_Uart=
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
