#ifndef SPI_Services_INTERFACE_H_
#define SPI_Services_INTERFACE_H_

#include "DMA_int.h"
#include "SPI_prv.h"
#include "stdint.h"
#include "STM32F446xx.h"
#include "Utils.h"
#include "NVIC_int.h"

typedef enum
{
	SPI_IRQSend,
	SPI_IRQReceive,


}SPI_IRQReason;

void SPI_SendReceiveCallBack(SPI_Channel_t copy_eSPI);
void SPI_vSendDataAsynch(SPI_HandleTypeDef_t* hspi, uint8_t copy_u8Data_Size,uint8_t* copy_pu8Data );
void SPI_vReceiveDataAsynch(SPI_HandleTypeDef_t* hspi, uint8_t copy_u8Data_Size,uint8_t* copy_pu8Data );





#endif
