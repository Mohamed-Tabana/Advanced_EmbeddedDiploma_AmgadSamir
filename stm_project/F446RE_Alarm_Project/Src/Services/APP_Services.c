
#include <stdint.h>
#include "DMA_int.h"
#include "EXTI_int.h"
#include "GPIO_int.h"
#include "I2C_int.h"
#include "NVIC_int.h"
#include "RCC_int.h"
#include "SPI_int.h"
#include "SysTick_int.h"
#include "UART_int.h"
#include "RTC.h"
#include "SPI_Services.h"
#include "APP_Services.h"


//Extern Config Structs

extern PinConfig_t I2C_PinSDA; //B7
extern PinConfig_t I2C_PinSCK; //B6
extern I2C_HandleTypeDef_t I2C_ourI2C;
extern DMA_HandleTypeDef_t I2C_DMA_I2C1_RX;
extern DMA_HandleTypeDef_t I2C_DMA_I2C1_TX;

extern DMA_HandleTypeDef_t SPI_DMA_Handle;
extern SPI_HandleTypeDef_t SPI_ourSPI;
extern PinConfig_t SPI_PinCS;
extern PinConfig_t SPI_PinMOSI; //A7
extern PinConfig_t SPI_PinMISO; //A6
extern PinConfig_t SPI_PinSCK;  //A5

extern DMA_HandleTypeDef_t UART_DMA_Uart;
extern USART_HandleTypeDef_t UART_ourUsart;
extern PinConfig_t UART_PINRX; //A3
extern PinConfig_t UART_PINTX; //A2


PinConfig_t Pin_To_EXTI=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN10,
		.PIN_Type=OUTPUT,
		.PIN_OValue=OUTPUT_HIGH,
		.PIN_OSpeed=HIGH_SPEED,
		.PIN_OType=PUSH_PULL,
		.PIN_LCKSTS=UNLOCKED,
};


/***************************
 * SPI FRAME
 ***************************/
uint8_t APP_SPIFrame[20]={0,1,2,3,4,5,6,7,8,9};

/***************************
 * ALARM
 ***************************/

uint8_t APP_AlarmName [6][10]={0};
APP_Alarm_t APP_Alarms[APP_TOTAL_NUMBER_OF_ALARMS]={{.ALARM_ID=(uint8_t*)"1.",.ALARM_STATUS=ALARM_NEVER_SET},{.ALARM_ID=(uint8_t*)"2.",.ALARM_STATUS=ALARM_NEVER_SET},{.ALARM_ID=(uint8_t*)"3.",.ALARM_STATUS=ALARM_NEVER_SET},{.ALARM_ID=(uint8_t*)"4.",.ALARM_STATUS=ALARM_NEVER_SET},{.ALARM_ID=(uint8_t*)"5.",.ALARM_STATUS=ALARM_NEVER_SET}};

//====================================================================
//====================================================================

void APP_Services_Init(void)
{
	/**********************
	 *  INITIALIZATION PART
	 **********************/


	// SPI
	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOAEN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOCEN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOBEN);

	RCC_AHB1EnableCLK(RCC_AHB1ENR_DMA1EN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_DMA2EN);

	RCC_APB1EnableCLK(RCC_APB1ENR_USART2EN);
	RCC_APB1EnableCLK(RCC_APB1ENR_SPI3EN);
	RCC_APB1EnableCLK(RCC_APB1ENR_SPI2EN);

	RCC_APB2EnableCLK(RCC_APB2ENR_SPI1EN);
	RCC_APB2EnableCLK(RCC_APB2ENR_SPI4EN);

	GPIO_u8PinInit(&SPI_PinSCK);  // A5
	GPIO_u8PinInit(&SPI_PinMISO); // A6
	GPIO_u8PinInit(&SPI_PinMOSI); // A7
	//	GPIO_u8PinInit(&SPI_PinCS);   // B6 useless

	SPI_vInit(&SPI_ourSPI);
	//UART
	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOAEN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOCEN);

	RCC_AHB1EnableCLK(RCC_AHB1ENR_DMA1EN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_DMA2EN);

	RCC_APB1EnableCLK(RCC_APB1ENR_USART2EN);
	RCC_APB1EnableCLK(RCC_APB1ENR_SPI3EN);

	GPIO_u8PinInit(&UART_PINTX); // A2
	GPIO_u8PinInit(&UART_PINRX); // A3
	UART_vInit( &UART_ourUsart);
	DMA_vInit( &UART_DMA_Uart);

	// I2C
	RCC_AHB1EnableCLK(RCC_AHB1ENR_DMA1EN);
	RCC_APB1EnableCLK(RCC_APB1ENR_I2C1EN);


	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOBEN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOCEN);

	//Enable DMA interrupts
	NVIC_vEnableInterrupt(NVIC_DMA1_Stream7);
	NVIC_vEnableInterrupt(NVIC_DMA1_Stream0);

	DMA_vInit(&I2C_DMA_I2C1_TX);
	DMA_vInit(&I2C_DMA_I2C1_RX);

	GPIO_u8PinInit(&I2C_PinSCK); // B6
	GPIO_u8PinInit(&I2C_PinSDA); // B7
	I2C_vInit(&I2C_ourI2C);

	//to EXTI
	GPIO_u8PinInit(&Pin_To_EXTI); // A1


	//===============================================================
}




void APP_Services_Get_Time_Date_User(uint8_t* ArrToRec)
{
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Please set the Date \n\r");
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"DD/MM/YY\r");
	UART_vReceiveSynchSize(&UART_ourUsart, ArrToRec+RTC_DATE_REGISER_ADDRESS, GetCurrentDate_SIZE);
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"/");
	UART_vReceiveSynchSize(&UART_ourUsart, ArrToRec+RTC_MONTH_REGISER_ADDRESS, GetCurrentDate_SIZE);
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"/");
	UART_vReceiveSynchSize(&UART_ourUsart, ArrToRec+RTC_YEAR_REGISER_ADDRESS, GetCurrentDate_SIZE);

	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"\n\rPlease set the Time \n\r");
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"HH/MM/SS\r");
	UART_vReceiveSynchSize(&UART_ourUsart, ArrToRec+RTC_HOURS_REGISER_ADDRESS, GetCurrentDate_SIZE);
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"/");
	UART_vReceiveSynchSize(&UART_ourUsart, ArrToRec+RTC_MINUTES_REGISER_ADDRESS, GetCurrentDate_SIZE);
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"/");
	UART_vReceiveSynchSize(&UART_ourUsart, ArrToRec+RTC_SECONDS_REGISER_ADDRESS, GetCurrentDate_SIZE);
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"\n\r");

}
uint8_t APP_Check_Password(uint8_t* APP_password)
{
	if (	APP_password[0] == 1 &&
			APP_password[1] == 2 &&
			APP_password[2] == 3 &&
			APP_password[3] == 4)
	{
		return 1;
	}
	return 0;
}
static void Set_RedLED();
static void Set_GreenLED();

void APP_SignInScreen_Services()
{
	uint8_t APP_password [10]={0};
	uint8_t correct_password=0;
	uint8_t wrong_password_counter=0;

	while (correct_password==0)
	{
		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Hello Please enter the password\n\r");
		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"XXXX\r");
		UART_vReceiveSynchSize(&UART_ourUsart, APP_password+0, 1);
		UART_vReceiveSynchSize(&UART_ourUsart, APP_password+1, 1);
		UART_vReceiveSynchSize(&UART_ourUsart, APP_password+2, 1);
		UART_vReceiveSynchSize(&UART_ourUsart, APP_password+3, 1);

		if (APP_Check_Password(APP_password))
		{
			Set_GreenLED();
			correct_password=1;
		}
		else
		{
			Set_RedLED();
			wrong_password_counter++;
			if (wrong_password_counter == 3)
			{
				wrong_password_counter=0;
				STK_vSetBusyWait(6000000);//3 sec block
			}

		}
	}

}
void APP_WelcomeScreen_Services_Welcome()
{
	uint8_t APP_CurrentData [10]={0};

	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Hello Welcome to The Real Time Alarm\n\r");
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Please Update the real date and time \n\r");
	APP_Services_Get_Time_Date_User(APP_CurrentData);
	RTC_ProgrammingArr(&I2C_ourI2C,&I2C_DMA_I2C1_TX,APP_CurrentData);
	APP_HASH_ON_SCREEN();

}
uint8_t APP_MainMenu()
{
	uint8_t Option_MainMenu;
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Please Select Which Option do you need\n\r");
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"1.Display Time and Date\n\r");
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"2.Set Time and Date\n\r");
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"3.Set Alarm\n\r");

	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"X\r");
	UART_vReceiveSynchSize(&UART_ourUsart, &Option_MainMenu, 1);
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"\n\r");
	APP_HASH_ON_SCREEN();

	return Option_MainMenu;
}

//DONE
void APP_Option1_Services_Display_Time_Date()
{
	uint8_t APP_DataFromRTC [20]={0};

	APP_SPIFrame[SPI_FRAME_TYPE_ID]=SPI_FRAME_ID_DISPLAY_TIME_DATE;
	RTC_Get_CurrentTime(&I2C_ourI2C,&I2C_DMA_I2C1_TX,&I2C_DMA_I2C1_RX,APP_DataFromRTC);
	for (uint8_t i=0;i<SPI_FRAME_DATA_DATE_TOTAL_SIZE;i++)
	{
		APP_SPIFrame[i+1]=APP_DataFromRTC[i] ;
	}
	APP_HASH_ON_SCREEN();
	SPI_vSendDataAsynch(&SPI_ourSPI, 10,APP_SPIFrame);
}
//DONE
void APP_Oprion2_Services_Set_Time_Data()
{
	uint8_t APP_CurrentData [10]={0};

	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Update The Current Time and Date\n\r");
	APP_Services_Get_Time_Date_User(APP_CurrentData);
	RTC_ProgrammingArr(&I2C_ourI2C,&I2C_DMA_I2C1_TX,APP_CurrentData);
	APP_HASH_ON_SCREEN();

}

//DONE
void APP_Oprion3_Services_Set_Alarm_Display_Options()
{
	uint8_t AlarmNumberData=10;
	// Display All Alarms
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Set Alarm Options\n\r");
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Please select Alarm Number\n\r");
	for (uint8_t i=0 ;i<5;i++)
	{
		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*) (APP_Alarms[i].ALARM_ID));
		//		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"\n\r");
		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*) (APP_Alarms[i].ALARM_NAME));
		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"\n\r");
	}
	//Receive Alarm Number
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Select Alarm: \n\r");
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"X\r");
	UART_vReceiveSynchSize(&UART_ourUsart, &AlarmNumberData, 1);
	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"\n\r");
	APP_HASH_ON_SCREEN();

	// Check if it is set before
	if (APP_Alarms[AlarmNumberData-1].ALARM_STATUS == ALARM_ALREADY_SET)
	{
		// Tell him it is set and did not come
		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Alarm is SET\n\r");
		APP_HASH_ON_SCREEN();

	}
	// Make him set the Data
	else
	{
		uint8_t APP_AlarmData [10]={0};
		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Please Write Alarm Name\n\r");
		UART_vReceiveSynchString(&UART_ourUsart, APP_AlarmName[AlarmNumberData-1]);

		APP_Alarms[AlarmNumberData-1].ALARM_NAME=APP_AlarmName[AlarmNumberData-1];
		UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"Please Set your Date and time Alarm\n\r");

		APP_Services_Get_Time_Date_User(APP_AlarmData);
		// Set the Alarm in struct
		APP_Alarms[AlarmNumberData-1].ALARM_SEC=APP_AlarmData[RTC_SECONDS_REGISER_ADDRESS];
		APP_Alarms[AlarmNumberData-1].ALARM_MIN=APP_AlarmData[RTC_MINUTES_REGISER_ADDRESS];
		APP_Alarms[AlarmNumberData-1].ALARM_HOUR=APP_AlarmData[RTC_HOURS_REGISER_ADDRESS];
		APP_Alarms[AlarmNumberData-1].ALARM_DATE=APP_AlarmData[RTC_DATE_REGISER_ADDRESS];
		APP_Alarms[AlarmNumberData-1].ALARM_MONTH=APP_AlarmData[RTC_MONTH_REGISER_ADDRESS];
		APP_Alarms[AlarmNumberData-1].ALARM_YEAR=APP_AlarmData[RTC_YEAR_REGISER_ADDRESS];

		APP_Alarms[AlarmNumberData-1].ALARM_STATUS=ALARM_ALREADY_SET;
		APP_HASH_ON_SCREEN();

	}
}




void APP_Periodically_Check_Alarms()
{
	uint8_t APP_DataFromRTC [10]={0};
	RTC_Get_CurrentTime(&I2C_ourI2C,&I2C_DMA_I2C1_TX,&I2C_DMA_I2C1_RX,APP_DataFromRTC);
	uint8_t Flag_Time_Hit_Alarm[APP_TOTAL_NUMBER_OF_ALARMS]={0};
	for (uint8_t loc_AlarmNumber=0;loc_AlarmNumber<APP_TOTAL_NUMBER_OF_ALARMS;loc_AlarmNumber++)
	{
		// compare only if alarm set and did not hit
		if (APP_Alarms[loc_AlarmNumber].ALARM_STATUS!=ALARM_ALREADY_SET)
		{
			continue;
		}
		// compare sec
		if(APP_Alarms[loc_AlarmNumber].ALARM_SEC<=APP_DataFromRTC[RTC_SECONDS_REGISER_ADDRESS])
		{
			Flag_Time_Hit_Alarm[loc_AlarmNumber]|=1<<RTC_SECONDS_REGISER_ADDRESS;
		}
		//compare min
		if(APP_Alarms[loc_AlarmNumber].ALARM_MIN==APP_DataFromRTC[RTC_MINUTES_REGISER_ADDRESS])
		{
			Flag_Time_Hit_Alarm[loc_AlarmNumber]|=1<<RTC_MINUTES_REGISER_ADDRESS;
		}
		//compare hour
		if(APP_Alarms[loc_AlarmNumber].ALARM_HOUR==APP_DataFromRTC[RTC_HOURS_REGISER_ADDRESS])
		{
			Flag_Time_Hit_Alarm[loc_AlarmNumber]|=1<<RTC_HOURS_REGISER_ADDRESS;
		}
		//compare date
		if(APP_Alarms[loc_AlarmNumber].ALARM_DATE==APP_DataFromRTC[RTC_DATE_REGISER_ADDRESS])
		{
			Flag_Time_Hit_Alarm[loc_AlarmNumber]|=1<<RTC_DATE_REGISER_ADDRESS;
		}
		//compare month
		if(APP_Alarms[loc_AlarmNumber].ALARM_MONTH==APP_DataFromRTC[RTC_MONTH_REGISER_ADDRESS])
		{
			Flag_Time_Hit_Alarm[loc_AlarmNumber]|=1<<RTC_MONTH_REGISER_ADDRESS;
		}
		//compare year
		if(APP_Alarms[loc_AlarmNumber].ALARM_YEAR==APP_DataFromRTC[RTC_YEAR_REGISER_ADDRESS])
		{
			Flag_Time_Hit_Alarm[loc_AlarmNumber]|=1<<RTC_YEAR_REGISER_ADDRESS;
		}
		//make interrupt Change Status if ALARM hit
		if ((Flag_Time_Hit_Alarm[loc_AlarmNumber] & APP_ALARM_HIT_MASK) == APP_ALARM_HIT_MASK )
		{
			APP_Make_Interrupt_To_Slave_AND_Clear_ALARM(loc_AlarmNumber);
		}
	}


}

void APP_Make_Interrupt_To_Slave_AND_Clear_ALARM(ALARM_NUMBER copy_alarmNumber)
{
	// MAKE Interrupt only set pin for 100 mS//FIXME
	//TODO interrupt blue pill
	GPIO_vSetOutputPinValue(Pin_To_EXTI.PIN_Port,Pin_To_EXTI.PIN_Number,OUTPUT_LOW);
	STK_vSetBusyWait(4000); // 2ms
	GPIO_vSetOutputPinValue(Pin_To_EXTI.PIN_Port,Pin_To_EXTI.PIN_Number,OUTPUT_HIGH);


	// send to the slave the number of the alarm to display
	APP_SPIFrame[SPI_FRAME_TYPE_ID]=SPI_FRAME_ID_ALARM_HIT_NU;
	APP_SPIFrame[1]=copy_alarmNumber;

	SPI_vSendDataAsynch(&SPI_ourSPI, 10,APP_SPIFrame);

	// CLEAR ALARM
	APP_Alarms[copy_alarmNumber].ALARM_SEC=0;
	APP_Alarms[copy_alarmNumber].ALARM_MIN=0;
	APP_Alarms[copy_alarmNumber].ALARM_HOUR=0;
	APP_Alarms[copy_alarmNumber].ALARM_DATE=0;
	APP_Alarms[copy_alarmNumber].ALARM_MONTH=0;
	APP_Alarms[copy_alarmNumber].ALARM_YEAR=0;
	APP_Alarms[copy_alarmNumber].ALARM_NAME=APP_AlarmName[APP_ALARM_NAME_NULL];
	APP_Alarms[copy_alarmNumber].ALARM_STATUS=ALARM_ALREADY_HIT;


}

void APP_HASH_ON_SCREEN()
{

	UART_vSendStringSynch(&UART_ourUsart,(uint8_t*)"==========================================\n\r");

}



void Set_RedLED()
{
	APP_SPIFrame[SPI_FRAME_TYPE_ID]=SPI_FRAME_ID_WRONG_LOGIN;
	SPI_vSendDataAsynch(&SPI_ourSPI, 10,APP_SPIFrame);
}

void Set_GreenLED()
{
	APP_SPIFrame[SPI_FRAME_TYPE_ID]=SPI_FRAME_ID_RIGHT_LOGIN;
	SPI_vSendDataAsynch(&SPI_ourSPI, 10,APP_SPIFrame);
}















