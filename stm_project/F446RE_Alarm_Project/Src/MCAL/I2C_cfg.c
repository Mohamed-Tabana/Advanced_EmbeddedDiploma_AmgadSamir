
#include "DMA_int.h"
#include "I2C_int.h"
#include "STM32F446xx.h"
#include "Utils.h"
#include "GPIO_int.h"
#include "RCC_int.h"
#include "NVIC_int.h"

// DMA Handles
DMA_HandleTypeDef_t I2C_DMA_I2C1_TX=
{
		.Init.Channel=channel_1,
		.Init.DMANumber=DMA_Number_1,
		.Init.Stream=Stream_7,
		.Init.Direction=memory_to_peripheral,
		.Init.MINC=memory_address_pointer_is_incremented_after_each_data_transfer,
		.Init.PINC=peripheral_address_pointer_is_fixed,
		.Init.CircularMode= circular_mode_disabled,
		.Init.PriorityLevel=high,
		.Init.DirectOrFIFOMode=direct_mode_enabled,
		.Init.MemoryBurst=single_transfer,
		.Init.PeripheralBurst=single_transfer,

		.Current_memory_target=current_target_memory_is_Memory_0,
		.double_buffer_mode=No_buffer_switching_at_the_end_of_transfer,
		.peripheral_increment_offset_size=The_offset_size_for_the_peripheral_address_calculation_is_linked_to_the_PSIZE,
		.MemorySIZE=byte,
		.PeripheralSIZE=byte,
		.peripheral_flow_controller=DMA_is_the_flow_controller,
		.transfer_complete_interrupt_enable=TC_interrupt_enabled,
		.half_transfer_interrupt_enable=HT_interrupt_disabled,
		.transfer_error_interrupt_enable=TE_interrupt_disabled,
		.transfer_error_interrupt_enable=TE_interrupt_disabled,
		.direct_mode_error_interrupt_enable=DME_interrupt_disabled,
		.FIFO_error_interrupt_enable=FE_interrupt_disabled

};
DMA_HandleTypeDef_t I2C_DMA_I2C1_RX=
{
		.Init.Channel=channel_1,
		.Init.DMANumber=DMA_Number_1,
		.Init.Stream=Stream_0,
		.Init.Direction=peripheral_to_memory,
		.Init.MINC=memory_address_pointer_is_incremented_after_each_data_transfer,
		.Init.PINC=peripheral_address_pointer_is_fixed,
		.Init.CircularMode= circular_mode_disabled,
		.Init.PriorityLevel=high,
		.Init.DirectOrFIFOMode=direct_mode_enabled,
		.Init.MemoryBurst=single_transfer,
		.Init.PeripheralBurst=single_transfer,

		.Current_memory_target=current_target_memory_is_Memory_0,
		.double_buffer_mode=No_buffer_switching_at_the_end_of_transfer,
		.peripheral_increment_offset_size=The_offset_size_for_the_peripheral_address_calculation_is_linked_to_the_PSIZE,
		.MemorySIZE=byte,
		.PeripheralSIZE=byte,
		.peripheral_flow_controller=DMA_is_the_flow_controller,
		.transfer_complete_interrupt_enable=TC_interrupt_enabled,
		.half_transfer_interrupt_enable=HT_interrupt_disabled,
		.transfer_error_interrupt_enable=TE_interrupt_disabled,
		.transfer_error_interrupt_enable=TE_interrupt_disabled,
		.direct_mode_error_interrupt_enable=DME_interrupt_disabled,
		.FIFO_error_interrupt_enable=FE_interrupt_disabled
};
// I2C Handles
I2C_HandleTypeDef_t I2C_ourI2C=
{
		.I2C_ID=I2C_Channel_1,
		.I2C_MasterMode=I2C_SM_MODE,
		.I2C_InterfaceAddress=0x11,
		.I2C_StretchClk=I2C_CLK_STRETCH_Enabled,
};

// I2C pins Handles

PinConfig_t I2C_PinSCK=
{
		.PIN_Port=PORTB,
		.PIN_Number=PIN6,
		.PIN_Type=ALTERNATE,
		.PIN_PullUpDown=PULL_UP,
		.PIN_OType=OPEN_DRAIN,
		.PIN_AF=AF4,
		.PIN_LCKSTS=UNLOCKED,
		.PIN_OSpeed=HIGH_SPEED
};
PinConfig_t I2C_PinSDA=
{
		.PIN_Port=PORTB,
		.PIN_Number=PIN7,
		.PIN_Type=ALTERNATE,
		.PIN_PullUpDown=PULL_UP,
		.PIN_OType=OPEN_DRAIN,
		.PIN_AF=AF4,
		.PIN_LCKSTS=UNLOCKED,
		.PIN_OSpeed=HIGH_SPEED

};
