#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

#include "DMA_prv.h"
#include "stdint.h"
#include "STM32F446xx.h"
#include "Utils.h"

typedef enum {
	DMA_Number_1,
	DMA_Number_2
}DMA_Peripheral_Number_t;

typedef enum {
	Stream_0,
	Stream_1,
	Stream_2,
	Stream_3,
	Stream_4,
	Stream_5,
	Stream_6,
	Stream_7
}Stream_Selection_t;
typedef enum {
	channel_0,
	channel_1,
	channel_2,
	channel_3,
	channel_4,
	channel_5,
	channel_6,
	channel_7
}Channel_Selection_t;
typedef enum {
	current_target_memory_is_Memory_0,
	current_target_memory_is_Memory_1
}Current_memory_target_t;

typedef enum {
	single_transfer,
	INCR4,
	INCR8 ,
	INCR16,
}M_P_Burst_Transfer_Configuration_t;
typedef enum {
	No_buffer_switching_at_the_end_of_transfer,
	memory_target_switched_at_the_end_of_the_DMA_transfer
}double_buffer_mode_t;
typedef enum {
	low,
	medium,
	high,
	very_high
}priority_level_t;
typedef enum {
	The_offset_size_for_the_peripheral_address_calculation_is_linked_to_the_PSIZE,
	The_offset_size_for_the_peripheral_address_calculation_is_fixed_to_4
}peripheral_increment_offset_size_t;

typedef enum {
	byte,
	half_word,
	word
}P_M_SIZE_t;
typedef enum {
	memory_address_pointer_is_fixed,
	memory_address_pointer_is_incremented_after_each_data_transfer
}Memory_Increment_Mode_t;

typedef enum {
	peripheral_address_pointer_is_fixed,
	peripheral_address_pointer_is_incremented_after_each_data_transfer
}peripheral_Increment_Mode_t;
typedef enum {
	circular_mode_disabled,
	circular_mode_enabled
}circular_mode_t;
typedef enum {
	peripheral_to_memory,
	memory_to_peripheral,
	memory_to_memory
}data_transfer_direction_t;
typedef enum {
	DMA_is_the_flow_controller,
	The_peripheral_is_the_flow_controller
}peripheral_flow_controller_t;

typedef enum {
	TC_interrupt_disabled,
	TC_interrupt_enabled
}transfer_complete_interrupt_enable_t;
typedef enum {
	HT_interrupt_disabled,
	HT_interrupt_enabled
}half_transfer_interrupt_enable_t;
typedef enum {
	TE_interrupt_disabled,
	TE_interrupt_enabled
}transfer_error_interrupt_enable_T;
typedef enum {
	DME_interrupt_disabled,
	DME_interrupt_enabled
}direct_mode_error_interrupt_enable_t;

typedef enum {
	stream_disabled,
	stream_enabled
}stream_enable_t;

typedef enum {
	FE_interrupt_disabled,
	FE_interrupt_enabled
}FIFO_error_interrupt_enable_t;
typedef enum {
	direct_mode_enabled,
	direct_mode_disabled
}direct_mode_disable_t;

typedef enum {
	full_FIFO_1_4,
	full_FIFO_1_2,
	full_FIFO_3_4,
	full_FIFO,
}FIFO_threshold_t;
typedef enum {
	Half_transfer_reached_Interrupt=0,
	Transfer_complete_Interrupt=2,
	Transfer_error_Interrupt=3,
	FIFO_erro_Interruptr=4,
	Direct_mode_error_Interrupt=5,
	Total_Number_Of_Interrupts
}DMA_Interrupt_t;

typedef struct{
	Channel_Selection_t Channel;
	DMA_Peripheral_Number_t DMANumber;
	Stream_Selection_t Stream;
	data_transfer_direction_t Direction;
	Memory_Increment_Mode_t MINC;
	peripheral_Increment_Mode_t PINC;
	circular_mode_t CircularMode;
	priority_level_t PriorityLevel;
	direct_mode_disable_t DirectOrFIFOMode;
	FIFO_threshold_t FIFOThreshold;
	M_P_Burst_Transfer_Configuration_t MemoryBurst;
	M_P_Burst_Transfer_Configuration_t PeripheralBurst;


}DMA_InitTypeDef_t;

typedef struct{
	DMA_InitTypeDef_t Init;

	Current_memory_target_t Current_memory_target;
	double_buffer_mode_t double_buffer_mode;
	peripheral_increment_offset_size_t peripheral_increment_offset_size;
	P_M_SIZE_t PeripheralSIZE;
	P_M_SIZE_t MemorySIZE;
	peripheral_flow_controller_t peripheral_flow_controller;
	transfer_complete_interrupt_enable_t transfer_complete_interrupt_enable;
	half_transfer_interrupt_enable_t half_transfer_interrupt_enable;
	transfer_error_interrupt_enable_T transfer_error_interrupt_enable;
	direct_mode_error_interrupt_enable_t direct_mode_error_interrupt_enable;
	FIFO_error_interrupt_enable_t FIFO_error_interrupt_enable;

	void (*TxCpltCallBack_t) (void);
	void (*HalfTxCpltCallBack_t) (void);
	void (*TxErrorCallBack_t) (void);
	void (*DirectErrModeCallBack_t) (void);


}DMA_HandleTypeDef_t;

void DMA_vInit(DMA_HandleTypeDef_t* copy_eDMAConfig);
void DMA_vSetDMAStreamChannelSelection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,Channel_Selection_t copy_eChannel_Selection);
void DMA_vSetDMAStreamMemoryBurstTransferSelection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,M_P_Burst_Transfer_Configuration_t copy_eM_P_Burst_Transfer_Configuration);
void DMA_vSetDMAStreamPeripheralBurstTransferSelection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,M_P_Burst_Transfer_Configuration_t copy_eM_P_Burst_Transfer_Configuration);
void DMA_vSetDMAStreamCurrentMemoryTarget(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,Current_memory_target_t copy_Current_memory_target);
void DMA_vSetDMAStreamDoubleBufferMode(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,double_buffer_mode_t copy_double_buffer_mode);
void DMA_vSetDMAStreamPriorityLevel(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,priority_level_t copy_epriority_level);
void DMA_vSetDMAStreamIncreamentalOffset(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,peripheral_increment_offset_size_t copy_eperipheral_increment_offset_size);
void DMA_vSetDMAStreamMemorySize(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,P_M_SIZE_t copy_eP_M_SIZE);
void DMA_vSetDMAStreamPeripheralSize(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,P_M_SIZE_t copy_eP_M_SIZE);
void DMA_vSetDMAMemoryIncrementMode(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,Memory_Increment_Mode_t copy_eMemory_Increment_Mode);
void DMA_vSetDMAPeripheralIncrementMode(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,peripheral_Increment_Mode_t copy_peripheral_Increment_Mode);
void DMA_vSetDMACircularMode(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,circular_mode_t copy_eCircular_mode);
void DMA_vSetDMAStreamDataTransferDirection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,data_transfer_direction_t copy_edata_transfer_direction);
void DMA_vSetDMAStreamPeripheralFlowController(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,peripheral_flow_controller_t copy_eperipheral_flow_controller);
void DMA_vSetTransferCompleteInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,transfer_complete_interrupt_enable_t copy_etransfer_complete_interrupt_enable);
void DMA_vSetHalfTransferCompleteInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,half_transfer_interrupt_enable_t half_transfer_interrupt_enable);
void DMA_vSetTransferErrorInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,transfer_error_interrupt_enable_T copy_etransfer_error_interrupt_enable);
void DMA_vSetDirectModeErrorInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,direct_mode_error_interrupt_enable_t copy_edirect_mode_error_interrupt_enable);
void DMA_vEnableStream(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection, stream_enable_t copy_estream_enable);
void DMA_vSetNumberOfDataToBeTransefered(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,uint16_t copy_u16NumberOfData);
void DMA_vSetAddressOfPeripheral(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,uint32_t copy_u32AddressOfPeripheral);
void DMA_vSetAddressOfMemory0(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,uint32_t copy_u32AddressOfMemory0);
void DMA_vSetAddressOfMemory1(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,uint32_t copy_u32AddressOfMemory1);
void DMA_vSetFIFOErrorInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,FIFO_error_interrupt_enable_t copy_eFIFO_error_interrupt_enable);
//uint8_t DMA_u8GetFIFOStatus();
void DMA_vSetDirectModeStatus(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,direct_mode_disable_t copy_edirect_mode_disable);
void DMA_vSetFIFOThresholdSelection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,FIFO_threshold_t copy_eFIFO_threshold);

void DMA_vStart(DMA_HandleTypeDef_t* copy_eDMAConfig,uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
void DMA_vStart_IT(DMA_HandleTypeDef_t* copy_eDMAConfig,uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);

void DMA_vReadFlagStatus(DMA_Peripheral_Number_t DMA_Number,Stream_Selection_t Stream_Number,DMA_Interrupt_t copy_eDMA_Interrupt,uint8_t *interruptStatusFlag);
void DMA_vSetCallBack(DMA_HandleTypeDef_t* copy_eDMAConfig,DMA_Interrupt_t copy_eDMA_Interrupt, void (*PtrToFunc)(void));
void DMA_vIRQHandler(DMA_Peripheral_Number_t DMA_Number,Stream_Selection_t Stream_Number);

#endif