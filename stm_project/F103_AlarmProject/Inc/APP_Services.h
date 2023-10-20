/*
 * APP_Services.h
 *
 *  Created on: Sep 28, 2023
 *      Author: ALTAWKEL
 */

#ifndef APP_SERVICES_H_
#define APP_SERVICES_H_

enum {
	RTC_SECONDS_REGISER_ADDRESS,
	RTC_MINUTES_REGISER_ADDRESS,
	RTC_HOURS_REGISER_ADDRESS,
	RTC_DAY_REGISER_ADDRESS,
	RTC_DATE_REGISER_ADDRESS,
	RTC_MONTH_REGISER_ADDRESS,
	RTC_YEAR_REGISER_ADDRESS,
	RTC_TOTAL_NUMBER_REGISERS_ADDRESS,

};

// Frame 1 Content
#define SPI_FRAME_TYPE_ID 0
#define SPI_FRAME_ID_DISPLAY_TIME_DATE  1

#define SPI_FRAME_DATA_POS_SECS         RTC_SECONDS_REGISER_ADDRESS +1
#define SPI_FRAME_DATA_POS_MINS         RTC_MINUTES_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_HOUR         RTC_HOURS_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_DAY          RTC_DAY_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_DATE         RTC_DATE_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_MONTH        RTC_MONTH_REGISER_ADDRESS+1
#define SPI_FRAME_DATA_POS_YEAR         RTC_YEAR_REGISER_ADDRESS+1

#define SPI_FRAME_DATA_DATE_TOTAL_SIZE  SPI_FRAME_DATA_POS_YEAR+1

#define SPI_FRAME_ID_RIGHT_LOGIN 		2
#define SPI_FRAME_ID_WRONG_LOGIN 		3
#define SPI_FRAME_ID_ALARM_HIT_NU 		4






void APP_Services_Init();
void APP_Services_Ping_SPI_Asynch();
void APP_Services_Set_GREEN_LED();
void APP_Services_Clear_GREEN_LED();
void APP_Services_Set_RED_LED();
void APP_Services_Clear_RED_LED();
void APP_Services_Turn_on_Buzzer();
void APP_Services_Turn_off_Buzzer();
void APP_Services_Periodic_Receive_Frame_Check();
void APP_Services_Display_Time_Date();
void APP_Services_Display_Alarm_Number();
void APP_Services_Decode_Frame();

void APP_Services_Periodic_increase_Time();
void APP_Services_Display_Time_Date_BluePill_Time();









#endif /* APP_SERVICES_H_ */
