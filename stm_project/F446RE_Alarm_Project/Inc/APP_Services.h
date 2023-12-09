/*
 * APP_Services.h
 *
 *  Created on: Sep 23, 2023
 *      Author: ALTAWKEL
 */

#ifndef APP_SERVICES_H_
#define APP_SERVICES_H_


/***************************
 * SPI FRAME
 ***************************/

#define GetCurrentDate_SIZE 2
#define SPI_FRAME_TYPE_ID 0

// Frames IDs
#define SPI_FRAME_ID_DISPLAY_TIME_DATE  1
#define SPI_FRAME_ID_RIGHT_LOGIN 		2
#define SPI_FRAME_ID_WRONG_LOGIN 		3
#define SPI_FRAME_ID_ALARM_HIT_NU 		4

// Frame 1 Content

#define SPI_FRAME_DATA_POS_SECS         RTC_SECONDS_REGISER_ADDRESS +1
#define SPI_FRAME_DATA_POS_MINS         RTC_MINUTES_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_HOUR         RTC_HOURS_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_DAY          RTC_DAY_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_DATE         RTC_DATE_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_MONTH        RTC_MONTH_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_YEAR         RTC_YEAR_REGISER_ADDRESS+1

#define SPI_FRAME_DATA_DATE_TOTAL_SIZE  SPI_FRAME_DATA_POS_YEAR+1



/***************************
 * ALARM
 ***************************/


#define APP_ALARM_HIT_MASK 0b01110111
typedef enum
{
	ALARM_1,
	ALARM_2,
	ALARM_3,
	ALARM_4,
	ALARM_5,

}ALARM_NUMBER;
typedef enum{
	ALARM_NEVER_SET,
	ALARM_ALREADY_SET,
	ALARM_ALREADY_HIT,

}APP_ALARM_STATUS;


// ALARM
typedef struct{
	uint8_t* ALARM_ID;
	uint8_t* ALARM_NAME;
	APP_ALARM_STATUS ALARM_STATUS;
	uint8_t  ALARM_SEC;
	uint8_t  ALARM_MIN;
	uint8_t  ALARM_HOUR;
	uint8_t  ALARM_DAY;
	uint8_t  ALARM_DATE;
	uint8_t  ALARM_MONTH;
	uint8_t  ALARM_YEAR;

}APP_Alarm_t;
#define APP_TOTAL_NUMBER_OF_ALARMS 5
#define APP_ALARM_NAME_NULL 6
/***************************
 * MAIN
 ***************************/

typedef enum
{
	DISPLAY_TIME_DATE=1,
	SET_TIME_DATE,
	SET_ALARM

}MainMenu_Options;

//====================================================================
//====================================================================


// EXTERN FUNCTIONS
void APP_Services_Init(void);
void APP_Services_Get_Time_Date_User(uint8_t* ArrToRec);
void APP_WelcomeScreen_Services_Welcome();
uint8_t APP_MainMenu();
void APP_Option1_Services_Display_Time_Date();
void APP_Oprion2_Services_Set_Time_Data();
void APP_Oprion3_Services_Set_Alarm_Display_Options();
void APP_Periodically_Check_Alarms();
void APP_Make_Interrupt_To_Slave_AND_Clear_ALARM(ALARM_NUMBER copy_alarmNumber);
void APP_HASH_ON_SCREEN();
void APP_SignInScreen_Services();
//====================================================================

#endif /* APP_SERVICES_H_ */
