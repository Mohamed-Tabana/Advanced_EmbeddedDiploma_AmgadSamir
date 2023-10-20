/*
 * APP_Services.c
 *
 *  Created on: Sep 28, 2023
 *      Author: ALTAWKEL
 */
#include <stdint.h>
#include "EXTI_int.h"
#include "GPIO_int.h"
#include "NVIC_int.h"
#include "RCC_int.h"
#include "SPI_int.h"
#include "SysTick_int.h"
#include "SPI_Services.h"
#include "APP_Services.h"
#include "LCD.h"
#include "EXTI_int.h"

//LCD Pins
extern PinConfig_t LCD_RS; //A11
extern PinConfig_t LCD_EN; //A8
extern PinConfig_t LCD_D4; //B15
extern PinConfig_t LCD_D5; //B14
extern PinConfig_t LCD_D6; //B13
extern PinConfig_t LCD_D7; //B12
//SPI Pins
extern PinConfig_t PinMOSI; //A7
extern PinConfig_t PinMISO; //A6
extern PinConfig_t PinSCK;  //A5
extern PinConfig_t PinCS;   //B12 USELESS
extern SPI_HandleTypeDef_t SPI_ourSPI ;
// LEDs - BUZZER
extern PinConfig_t GPIO_RED_LED;
extern PinConfig_t GPIO_GREEN_LED;
extern PinConfig_t GPIO_BLUE_LED;
extern PinConfig_t GPIO_BUZZER;
// EXTI
extern EXTI_EXTIConfig_t ourEXTI;



extern volatile uint8_t GlobalSPI_u8NoOfRecFrames;
#define SPI_FRAME_TOTAL_SIZE 20
uint8_t SPIRecDataFromNucleo[SPI_FRAME_TOTAL_SIZE];
//
uint8_t Global_u8TimeTakenFromNucleo=0;
uint8_t BluePillTime[10]={0};

void APP_Services_Init()
{
	// LCD INIT
	RCC_APB2EnableCLK(IOPAEN);
	RCC_APB2EnableCLK(IOPBEN);

	GPIO_u8PinInit(&LCD_RS); //A11
	GPIO_u8PinInit(&LCD_EN); //A8
	GPIO_u8PinInit(&LCD_D4); //B15
	GPIO_u8PinInit(&LCD_D5); //B14
	GPIO_u8PinInit(&LCD_D6); //B13
	GPIO_u8PinInit(&LCD_D7); //B12
	STK_vInit();
	LCD_Init();

	// SPI INIT
	RCC_APB2EnableCLK(IOPAEN);
	RCC_APB2EnableCLK(IOPBEN);
	RCC_APB2EnableCLK(IOPCEN);
	RCC_APB2EnableCLK(SPI1EN);

	GPIO_u8PinInit(&PinSCK);  //A5
	GPIO_u8PinInit(&PinMISO); //A6
	GPIO_u8PinInit(&PinMOSI); //A7
	SPI_vInit(&SPI_ourSPI);

	// Buzzer - GREEN LED - RED LED
	RCC_APB2EnableCLK(IOPAEN);
	RCC_APB2EnableCLK(IOPBEN);
	RCC_APB2EnableCLK(IOPCEN);

	GPIO_u8PinInit(&GPIO_RED_LED); //A1
	GPIO_u8PinInit(&GPIO_GREEN_LED); //C15
	GPIO_u8PinInit(&GPIO_BLUE_LED); //C14

	GPIO_u8PinInit(&GPIO_BUZZER); //B4

	// EXTI
	EXTI_Init( &ourEXTI );//A0
	RCC_APB2EnableCLK(AFIOEN);
	NVIC_vEnableInterrupt(EXTI0_IRQn);


}
void togglell()
{
	GPIO_vToggleOutputPinValue(PinSCK.PIN_Port, PinSCK.PIN_Number);
	GPIO_vToggleOutputPinValue(PinMISO.PIN_Port, PinMISO.PIN_Number);
	GPIO_vToggleOutputPinValue(PinMOSI.PIN_Port, PinMOSI.PIN_Number);
	STK_Delay_s(2);
}
void APP_Services_Ping_SPI_Asynch()
{

	//		for (uint8_t i=0;i<10;i++)
	//		{
	//			SPI_vReceiveSynch(&SPI_ourSPI,&SPIRecDataFromNucleo[i]);
	//			LCD_SetCursor(0,i);
	//			LCD_WriteNumber(SPIRecDataFromNucleo[i]);
	////	SPI_vSendSynch(&SPI_ourSPI,i+10);
	//
	//		}

	SPI_vReceiveDataAsynch( &SPI_ourSPI, 10 ,SPIRecDataFromNucleo );

}
void APP_Services_Set_GREEN_LED()
{
	GPIO_vSetOutputPinValue(GPIO_GREEN_LED.PIN_Port,GPIO_GREEN_LED.PIN_Number,OUTPUT_HIGH);
	APP_Services_Clear_RED_LED();
}
void APP_Services_Clear_GREEN_LED()
{
	GPIO_vSetOutputPinValue(GPIO_GREEN_LED.PIN_Port,GPIO_GREEN_LED.PIN_Number,OUTPUT_LOW);

}

void APP_Services_Set_RED_LED()
{
	GPIO_vSetOutputPinValue(GPIO_RED_LED.PIN_Port,GPIO_RED_LED.PIN_Number,OUTPUT_HIGH);
	APP_Services_Clear_GREEN_LED();
}
void APP_Services_Clear_RED_LED()
{
	GPIO_vSetOutputPinValue(GPIO_RED_LED.PIN_Port,GPIO_RED_LED.PIN_Number,OUTPUT_LOW);

}

void APP_Services_Turn_on_Buzzer()
{
	GPIO_vSetOutputPinValue(GPIO_BUZZER.PIN_Port,GPIO_BUZZER.PIN_Number,OUTPUT_HIGH);

}

void APP_Services_Turn_off_Buzzer()
{
	GPIO_vSetOutputPinValue(GPIO_BUZZER.PIN_Port,GPIO_BUZZER.PIN_Number,OUTPUT_LOW);

}

void APP_Services_Periodic_Receive_Frame_Check()
{

	if(GlobalSPI_u8NoOfRecFrames)
	{
		GlobalSPI_u8NoOfRecFrames--;

		APP_Services_Decode_Frame();
	}
}
void APP_Services_Display_Time_Date()
{
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_WriteString((uint8_t*) "Time: ");
	LCD_WriteNumber(SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_HOUR]);
	LCD_WriteString((uint8_t*) ":");
	LCD_WriteNumber(SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_MINS]);
	LCD_WriteString((uint8_t*) ":");
	LCD_WriteNumber(SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_SECS]);
	//LCD_WriteString((uint8_t*) " : ");


	LCD_SetCursor(1,0);
	LCD_WriteString((uint8_t*) "Date ");
	LCD_WriteNumber(SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_DATE]);
	LCD_WriteString((uint8_t*) "/");
	LCD_WriteNumber(SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_MONTH]);
	LCD_WriteString((uint8_t*) "/");
	LCD_WriteNumber(SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_YEAR]);
	//LCD_WriteString((uint8_t*) " : ");

}
void APP_Services_Display_Time_Date_BluePill_Time()
{
//	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_WriteString((uint8_t*) "Time: ");
	LCD_WriteNumber(BluePillTime[SPI_FRAME_DATA_POS_HOUR]);
	LCD_WriteString((uint8_t*) ":");
	LCD_WriteNumber(BluePillTime[SPI_FRAME_DATA_POS_MINS]);
	LCD_WriteString((uint8_t*) ":");
	LCD_WriteNumber(BluePillTime[SPI_FRAME_DATA_POS_SECS]);

	LCD_SetCursor(1,0);
	LCD_WriteString((uint8_t*) "Date: ");
	LCD_WriteNumber(BluePillTime[SPI_FRAME_DATA_POS_DATE]);
	LCD_WriteString((uint8_t*) "/");
	LCD_WriteNumber(BluePillTime[SPI_FRAME_DATA_POS_MONTH]);
	LCD_WriteString((uint8_t*) "/");
	LCD_WriteNumber(BluePillTime[SPI_FRAME_DATA_POS_YEAR]);

}
void APP_Services_Display_Alarm_Number()
{
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_WriteString((uint8_t*) "ALARM HIT ");
	LCD_SetCursor(1,0);
	LCD_WriteString((uint8_t*) "Number: ");
	LCD_WriteNumber(SPIRecDataFromNucleo[1]);

}
void APP_Services_Periodic_increase_Time()
{
	if (Global_u8TimeTakenFromNucleo==1)
	{
		if (STK_vGetRemainingTime()<1000)
		{

			BluePillTime[SPI_FRAME_DATA_POS_SECS]++;
			if (BluePillTime[SPI_FRAME_DATA_POS_SECS] == 60)
			{
				BluePillTime[SPI_FRAME_DATA_POS_SECS]=0;
				BluePillTime[SPI_FRAME_DATA_POS_MINS]++;
			}
			if (BluePillTime[SPI_FRAME_DATA_POS_MINS] == 60)
			{
				BluePillTime[SPI_FRAME_DATA_POS_MINS]=0;
				BluePillTime[SPI_FRAME_DATA_POS_HOUR]++;
			}
		}
	}
}
void APP_Services_Decode_Frame()
{
	if (SPIRecDataFromNucleo[SPI_FRAME_TYPE_ID] == SPI_FRAME_ID_DISPLAY_TIME_DATE)
	{
		APP_Services_Display_Time_Date();
		BluePillTime[SPI_FRAME_DATA_POS_SECS]=SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_SECS];
		BluePillTime[SPI_FRAME_DATA_POS_MINS]=SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_MINS];
		BluePillTime[SPI_FRAME_DATA_POS_HOUR]=SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_HOUR];
		BluePillTime[SPI_FRAME_DATA_POS_DATE]=SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_DATE];
		BluePillTime[SPI_FRAME_DATA_POS_MONTH]=SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_MONTH];
		BluePillTime[SPI_FRAME_DATA_POS_YEAR]=SPIRecDataFromNucleo[SPI_FRAME_DATA_POS_YEAR];
		Global_u8TimeTakenFromNucleo=1;

		//Turn off alarm hit led
		GPIO_vSetOutputPinValue(GPIO_BLUE_LED.PIN_Port,GPIO_BLUE_LED.PIN_Number,OUTPUT_LOW);
		//start timer
		STK_vStartTimer(1000000);
	}
	else if (SPIRecDataFromNucleo[SPI_FRAME_TYPE_ID] == SPI_FRAME_ID_ALARM_HIT_NU)
	{
		APP_Services_Display_Alarm_Number();

	}
	else if (SPIRecDataFromNucleo[SPI_FRAME_TYPE_ID] == SPI_FRAME_ID_RIGHT_LOGIN)
	{
		APP_Services_Set_GREEN_LED();

	}
	else if (SPIRecDataFromNucleo[SPI_FRAME_TYPE_ID] == SPI_FRAME_ID_WRONG_LOGIN)
	{
		APP_Services_Set_RED_LED();
	}
	// clear buffer
	for (uint8_t i=0 ;i<SPI_FRAME_TOTAL_SIZE; i++)
	{
		SPIRecDataFromNucleo[i]=0;
	}
}

void sedas()
{
	static uint8_t da[10]={10,20,30,40,50,60,70,80,90,99};
	SPI_vSendDataAsynch(&SPI_ourSPI, 10,da );
}






