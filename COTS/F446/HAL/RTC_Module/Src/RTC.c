
#include "STM32F446xx.h"
#include "I2C_int.h"
#include "Utils.h"
#include "ErrType.h"
#include "RTC.h"
 uint8_t cfg_RTC_prg_Array[7][2]=
{
		{RTC_SECONDS_REGISER_ADDRESS,        00	        }, //RTC_SECONDS;
		{RTC_MINUTES_REGISER_ADDRESS,        00         }, //RTC_MINUTES;
		{RTC_HOURS_REGISER_ADDRESS  ,        04         }, //RTC_HOURS;
		{RTC_DAY_REGISER_ADDRESS    ,        THURSDAY   }, //RTC_DAY;
		{RTC_DATE_REGISER_ADDRESS   ,        21         }, //RTC_DATE;
		{RTC_MONTH_REGISER_ADDRESS  ,         9         }, //RTC_MONTH;
		{RTC_YEAR_REGISER_ADDRESS   ,        23         }  //RTC_YEAR;
};
uint8_t Getter_RTC_prg_Array[7][2]=
{
		{RTC_SECONDS_REGISER_ADDRESS,        00 		}, //RTC_SECONDS;
		{RTC_MINUTES_REGISER_ADDRESS,        00         }, //RTC_MINUTES;
		{RTC_HOURS_REGISER_ADDRESS  ,        00         }, //RTC_HOURS;
		{RTC_DAY_REGISER_ADDRESS    ,        00         }, //RTC_DAY;
		{RTC_DATE_REGISER_ADDRESS   ,        00         }, //RTC_DATE;
		{RTC_MONTH_REGISER_ADDRESS  ,        00         }, //RTC_MONTH;
		{RTC_YEAR_REGISER_ADDRESS   ,        00         } //RTC_YEAR;
};

void RTC_Programming(I2C_HandleTypeDef_t* hi2c,DMA_HandleTypeDef_t* copy_eDMAConfig)
{
	I2C_SendDataToSlave_DMA(hi2c, copy_eDMAConfig,RTC_ADDRESS,(uint32_t) 14,(uint8_t*)cfg_RTC_prg_Array);
}
void RTC_Program_Specific_Field(I2C_HandleTypeDef_t* hi2c,DMA_HandleTypeDef_t* copy_eDMAConfig,RTC_Reg_Addresses copy_eReg)
{
	I2C_SendDataToSlave_DMA(hi2c, copy_eDMAConfig,RTC_ADDRESS,(uint32_t)2,(uint8_t*)cfg_RTC_prg_Array[copy_eReg]);
}

void RTC_Get_CurrentTime(I2C_HandleTypeDef_t* hi2c,DMA_HandleTypeDef_t* copy_eDMAConfig,uint8_t* copy_pu8Data)
{
	for (int i=0 ; i<RTC_TOTAL_NUMBER_REGISERS_ADDRESS ;i++)
	{
		//Give X Address Reg
		I2C_SendDataToSlave_DMA(hi2c, copy_eDMAConfig,RTC_ADDRESS,(uint32_t) 1,Getter_RTC_prg_Array[i]+1);
		//Get X Data
		I2C_ReceiveDataFromSlave_DMA(hi2c, copy_eDMAConfig,RTC_ADDRESS,(uint32_t) 1,(uint8_t*)(Getter_RTC_prg_Array[i]+1));
		copy_pu8Data[i]=Getter_RTC_prg_Array[i][1];
	}
}

void RTC_Get_Specific_Time(I2C_HandleTypeDef_t* hi2c,DMA_HandleTypeDef_t* copy_eDMAConfig,RTC_Reg_Addresses copy_eReg, uint8_t* copy_pu8Data)
{

	//Give X Address Reg
	I2C_SendDataToSlave_DMA(hi2c, copy_eDMAConfig,RTC_ADDRESS,(uint32_t) 1,Getter_RTC_prg_Array[copy_eReg]+1);
	//Get X Data
	I2C_ReceiveDataFromSlave_DMA(hi2c, copy_eDMAConfig,RTC_ADDRESS,(uint32_t) 1,(uint8_t*)(Getter_RTC_prg_Array[copy_eReg]+1));

	*copy_pu8Data=Getter_RTC_prg_Array[copy_eReg][1];
}


