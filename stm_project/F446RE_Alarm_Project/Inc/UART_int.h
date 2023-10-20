#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "DMA_int.h"
#include "UART_prv.h"
#include "stdint.h"
#include "STM32F446xx.h"
#include "Utils.h"

typedef enum {
	Parity_Error,
	Framing_Error,
	Noise_Detected_Flag,
	Overrun_Error,
	IDLE_Line_Detected,
	Read_Data_Register_Not_Empty,
	Transmission_Complete,
	Transmit_Data_Register_Empty,
	LIN_Break_Detection_Flag,
	CTS_flag,

}USART_Flag_t;

typedef enum {
	USART_1,
	USART_2,
	USART_3,
	UART_4,
	UART_5,
	USART_6
}USART_Peripheral_Number_t;

typedef enum {
	USART_Receiver_Disable,
	USART_Receiver_Enable,
}USART_Receiver_Enable_t;
typedef enum {
	USART_Transmitter_Disable,
	USART_Transmitter_Enable,
}USART_Transmitter_Enable_t;
typedef enum {
	USART_Interrupt_Disable,
	USART_Interrupt_Enable,
}USART_Interrupt_Enable_t;

typedef enum {
	USART_Even_Parity,
	USART_Odd_Parity,
}USART_Parity_t;
typedef enum {
	USART_Disable_Parity,
	USART_Enable_Parity,
}USART_Parity_Enable_t;
typedef enum {
	one_Start_bit_8_Data_bits,
	one_Start_bit_9_Data_bits,
}USART_WordLength_t;
typedef enum {
	USART_Disable,
	USART_Enable,
}USART_Enable_t;
typedef enum {
	oversampling_by_16,
	oversampling_by_8,
}USART_Oversampling_Mode_t;

typedef enum {
	One_Stop_bit,
	half_Stop_bit,
	Two_Stop_bit,
	One_And_Half_Stop_bit,

}USART_STOP_bits_t;

typedef enum {
	Three_sample_bit_method,
	One_sample_bit_method,

}USART_One_sample_bit_method_t;

typedef enum {
	DMA_disabled_for_reception,
	DMA_enabled_for_reception,

}USART_DMA_enable_transmitter_t;

typedef enum {
	DMA_disabled_for_transmission,
	DMA_enabled_for_transmission,

}USART_DMA_enable_receiver_t;

typedef struct{
	USART_Peripheral_Number_t USART_ID;
	USART_Enable_t USARTEnable;
	USART_Transmitter_Enable_t TransmitterEnable;
	USART_Receiver_Enable_t RecieverEnable;
	USART_DMA_enable_receiver_t DMAEnableReciever;
	USART_DMA_enable_transmitter_t DMAEnableTransmitter;
	USART_STOP_bits_t NumberOfStopBits;
	USART_Parity_Enable_t ParityEnable;
	USART_Parity_t ParityType;
	USART_WordLength_t WordLength;
	USART_One_sample_bit_method_t OneSampleMethod;
	USART_Oversampling_Mode_t OverSamplingMode;
	uint32_t u32BaudRate;
	USART_Interrupt_Enable_t ErrorInterruptEnable;
	USART_Interrupt_Enable_t IdleInterruptEnable;
	USART_Interrupt_Enable_t RXNEInterruptEnable;
	USART_Interrupt_Enable_t TransmissionCompleteInterruptEnable;
	USART_Interrupt_Enable_t TXEInterruptEnable;
	USART_Interrupt_Enable_t PEInterruptEnable;
}USART_HandleTypeDef_t;

void UART_vInit(USART_HandleTypeDef_t* huart);
void UART_vSendSynch(USART_HandleTypeDef_t* huart, uint8_t copy_u8Data);
void UART_vReceiveSynch(USART_HandleTypeDef_t* huart, uint8_t *copy_u8Data);
void UART_vSendAsynch(USART_HandleTypeDef_t* huart);
void UART_vReceiveAsynch(USART_HandleTypeDef_t* huart);

void UART_vReceive_DMA(DMA_HandleTypeDef_t* hdma, uint32_t copy_u32DstAddress, uint8_t copy_u32DataLength);
void UART_vSend_DMA(DMA_HandleTypeDef_t* hdma, uint32_t copy_u32SrcAddress, uint8_t copy_u32DataLength);

void UART_vSendStringSynch(USART_HandleTypeDef_t* huart, uint8_t* copy_pu8Data);
void UART_vReceiveSynchString(USART_HandleTypeDef_t* huart, uint8_t *copy_pu8Data);
void UART_vReceiveSynchSize(USART_HandleTypeDef_t* huart, uint8_t *copy_u8Data, uint8_t copy_u8Size);


#endif
