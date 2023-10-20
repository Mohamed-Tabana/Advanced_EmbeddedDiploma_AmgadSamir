#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

#include "I2C_int.h"
#include "stdint.h"
#include "STM32F446xx.h"
#include "Utils.h"

#define RTC_ADDRESS (uint8_t)0b01101000

enum {
	FRIDAY,
	SATURDAY,
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY
};
typedef enum {
	RTC_SECONDS_REGISER_ADDRESS,
	RTC_MINUTES_REGISER_ADDRESS,
	RTC_HOURS_REGISER_ADDRESS,
	RTC_DAY_REGISER_ADDRESS,
	RTC_DATE_REGISER_ADDRESS,
	RTC_MONTH_REGISER_ADDRESS,
	RTC_YEAR_REGISER_ADDRESS,
	RTC_TOTAL_NUMBER_REGISERS_ADDRESS,

}RTC_Reg_Addresses;

typedef struct
{
	uint8_t RTC_SECONDS;
	uint8_t RTC_MINUTES;
	uint8_t RTC_HOURS;
	uint8_t RTC_DAY;
	uint8_t RTC_DATE;
	uint8_t RTC_MONTH;
	uint8_t RTC_YEAR;


}RTC_Programming_Info;
enum
{
 RTC_SECONDS,
 RTC_MINUTES,
 RTC_HOURS,
 RTC_DAY,
 RTC_DATE,
 RTC_MONTH,
 RTC_YEAR,
};


void RTC_Programming(I2C_HandleTypeDef_t* hi2c,DMA_HandleTypeDef_t* copy_eDMAConfig);
void RTC_Program_Specific_Field(I2C_HandleTypeDef_t* hi2c,DMA_HandleTypeDef_t* copy_eDMAConfig,RTC_Reg_Addresses copy_eReg);
void RTC_Get_CurrentTime(I2C_HandleTypeDef_t* hi2c,DMA_HandleTypeDef_t* copy_eDMAConfig,uint8_t* copy_pu8Data);
void RTC_Get_Specific_Time(I2C_HandleTypeDef_t* hi2c,DMA_HandleTypeDef_t* copy_eDMAConfig,RTC_Reg_Addresses copy_eReg, uint8_t* copy_pu8Data);







#endif
