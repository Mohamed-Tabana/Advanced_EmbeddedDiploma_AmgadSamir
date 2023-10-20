
#include "STM32F446xx.h"
#include "SPI_prv.h"
#include "SPI_int.h"
#include "Utils.h"
#include "ErrType.h"
#include "SPI_Services.h"

static void SPI_NVICEnaleInterrupt(SPI_HandleTypeDef_t* hspi);

extern SPI_RegDef_t* SPIPeripheral [] ;

volatile SPI_IRQReason SPI_IRQ_Reason;
volatile uint8_t* GlobalSPI_pu8SendData[3]={0};
volatile uint8_t GlobalSPI_u8SizeSendData[3]={0};
volatile uint8_t GlobalSPI_u8CalledTimes=0;

volatile uint8_t GlobalSPI_u8SizeReceiveData[3]={0};
volatile uint8_t* GlobalSPI_pu8ReceiveData[3]={0};

void SPI_SendReceiveCallBack(SPI_Channel_t copy_eSPI)
{
	if (SPI_IRQ_Reason==SPI_IRQSend)
	{
//		for(uint32_t i=0;i<10;i++)
//		{
//			__asm volatile("nop");
//		}
		static uint8_t SBufferNumbberCB=0;
		static uint8_t i=1;

		if (i<GlobalSPI_u8SizeSendData[SBufferNumbberCB])
		{

			SPIPeripheral[copy_eSPI]->SPI_DR= GlobalSPI_pu8SendData[SBufferNumbberCB][i++];

		}
		else
		{
			GlobalSPI_u8CalledTimes--; //FIXME
			i=1;
//			SBufferNumbberCB++;//FIXME
//			SBufferNumbberCB= SBufferNumbberCB==3?0:SBufferNumbberCB;//FIXME

//			if (GlobalSPI_u8CalledTimes)//FIXME
//			{//FIXME
//				SPIPeripheral[copy_eSPI]->SPI_DR= GlobalSPI_pu8SendData[SBufferNumbberCB][0];//FIXME
//			}//FIXME
//			else//FIXME
			{
				SPI_EnableTxBufferEmptyInterrupt(copy_eSPI,SPI_Disable_Interrupt);

			}
		}

	}
	else if (SPI_IRQ_Reason==SPI_IRQReceive)
	{


		static uint8_t RBufferNumbberCB=0;
		static uint8_t i=0;

		if (i!=GlobalSPI_u8SizeReceiveData[RBufferNumbberCB])
		{
			GlobalSPI_pu8ReceiveData[RBufferNumbberCB][i++]=SPIPeripheral[copy_eSPI]->SPI_DR;
		}
		else
		{
//			SPI_EnableRxBufferFullInterrupt(copy_eSPI,SPI_Disable_Interrupt);
			i=0;
			RBufferNumbberCB++;
			RBufferNumbberCB= RBufferNumbberCB==3?0:RBufferNumbberCB;

		}
	}


}
void SPI_vSendDataAsynch(SPI_HandleTypeDef_t* hspi, uint8_t copy_u8Data_Size,uint8_t* copy_pu8Data )
{
	static uint8_t BufferNumbber=0;
	static uint8_t FirtTimmeFlag=0;
	SPI_IRQ_Reason=SPI_IRQSend;
	GlobalSPI_pu8SendData[BufferNumbber]=copy_pu8Data;
	GlobalSPI_u8SizeSendData[BufferNumbber]=copy_u8Data_Size;
	GlobalSPI_u8CalledTimes++;
	//Make Sure there is no data is transmitted
	while (!SPI_ReadFlag( hspi,SPI_TXBufferEmpty));

	//Transmit first byte
//	if(FirtTimmeFlag==0) //FIXME
		SPIPeripheral[hspi->SPI_ID]->SPI_DR= GlobalSPI_pu8SendData[BufferNumbber][0];
	//Enable Interrupt and NVIC
	SPI_EnableTxBufferEmptyInterrupt(hspi->SPI_ID,SPI_Enable_Interrupt);
	SPI_NVICEnaleInterrupt(hspi);

	//	GlobalSPI_u8SizeSendData[BufferNumbber]--;
//	BufferNumbber++; //FIXME
//	BufferNumbber= BufferNumbber==3?0:BufferNumbber;//FIXME
//	FirtTimmeFlag++;//FIXME

}

void SPI_vReceiveDataAsynch(SPI_HandleTypeDef_t* hspi, uint8_t copy_u8Data_Size,uint8_t* copy_pu8Data )
{
	SPI_IRQ_Reason=SPI_IRQReceive;

	static uint8_t BufferNumbber=0;
	GlobalSPI_pu8ReceiveData[BufferNumbber]=copy_pu8Data;
	GlobalSPI_u8SizeReceiveData[BufferNumbber]=copy_u8Data_Size;

	//Set CallBack to complete data transmission
//	SPI_SetCallBack(hspi,SPI_ReceiveAsynchCallBack);
	//Enable Interrupt and NVIC
	SPI_EnableRxBufferFullInterrupt(hspi->SPI_ID,SPI_Enable_Interrupt);
	SPI_NVICEnaleInterrupt(hspi);

	BufferNumbber++;
	BufferNumbber= BufferNumbber==3?0:BufferNumbber;

}


static void SPI_NVICEnaleInterrupt(SPI_HandleTypeDef_t* hspi)
{
	switch(hspi->SPI_ID)
	{
	case SPI_Channel1:
		NVIC_vEnableInterrupt(NVIC_SPI1);
		break;
	case SPI_Channel2:
		NVIC_vEnableInterrupt(NVIC_SPI2);
		break;
	case SPI_Channel3:
		NVIC_vEnableInterrupt(NVIC_SPI3);
		break;
	case SPI_Channel4:
		NVIC_vEnableInterrupt(NVIC_SPI4);
		break;
	}
}

/********************************
 *
 * CallBacks
 *
 ********************************/

//void SPI_SetCallBack(SPI_HandleTypeDef_t* hspi,IntCallBack_t copy_eCallBack)
//{
//	GlobalSPI_arrCallBack[hspi->SPI_ID]=copy_eCallBack;
//}


void SPI1_IRQHandler(void)
{
	SPI_SendReceiveCallBack(SPI_Channel1);

}
void SPI2_IRQHandler(void)
{
	SPI_SendReceiveCallBack(SPI_Channel2);
}
void SPI3_IRQHandler(void)
{
	SPI_SendReceiveCallBack(SPI_Channel3);

}
void SPI4_IRQHandler(void)
{
	SPI_SendReceiveCallBack(SPI_Channel4);

}
