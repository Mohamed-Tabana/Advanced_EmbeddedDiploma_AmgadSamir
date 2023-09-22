/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 10/4/2023				  	  **************/
/********* FILE NAME : RCC_Interface.h				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/


#ifndef MCAL_RCC_INC_RCC_INTERFACE_H_
#define MCAL_RCC_INC_RCC_INTERFACE_H_

#include <stdint.h>
#include "RCC_Private.h"

/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetClockStatus()
 *     FUNCTIONALITY : Set the selected clock state (ON/OFF)
 *     ARGUMENT 	 : UINT8 Clock Type {HSE,HSI,LSE,LSI,PLL} , UINT8 State of Clock {ON,OFF}
 *     RETURN   	 : Void
 *
 *---------------------------------------------------------------------------------*/
void RCC_SetClockStatus(uint8_t CLK_TYPE , uint8_t Status);




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetSystemClock()
 *     FUNCTIONALITY : Set the selected clock as System Clock
 *     ARGUMENT 	 : UINT8 Clock Type {HSE,HSI,LSE,LSI,PLL}
 *     RETURN   	 : Void
 *
 *---------------------------------------------------------------------------------*/
void RCC_SetSystemClock(uint8_t CLK_TYPE);




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_HSE_Divider()
 *     FUNCTIONALITY : Set the selected Factor to divide HSE Clock by
 *     ARGUMENT 	 : UINT8 Factor {HSE_DivideBy2 , HSE_DivideBy1 }
 *     RETURN   	 : Void
 *
 *---------------------------------------------------------------------------------*/
void RCC_SetHSE_Divider(uint8_t Factor);




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetPLL_Configs()
 *     FUNCTIONALITY : Set the PLL With chosen configurations
 *     ARGUMENT 	 : UINT8 PLL_MultiFactor {BY_2,BY_3,BY_4,BY_5,BY_6,BY_7,BY_8,BY_9,BY_10,BY_11,BY_12,BY_13,BY_14,BY_15,BY_16};
 *     				   UINT8 Pll_Source {HSE,HSI}
 *     RETURN   	 : Void
 *	   NOTES 		 : Before using this function, PLL state Must be off
 *---------------------------------------------------------------------------------*/
void RCC_SetPLL_Configs(uint8_t PLL_MultiFactor , uint8_t Pll_Source);




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_AHBPeripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To AHB Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name {  DMA1,
 *	                                            DMA2,
 *	                                            SRAM,
 *	                                            FLITF,
 *	                                            CRC,
 *	                                            FSMC,
 *	                                            SDIO }
 *
 *                     UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : Void
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
void RCC_Set_AHBPeripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State);



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_APB2Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To APB2 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name { AFIO,
 * 	                                           IOPA,
 * 	                                           IOPB,
 * 	                                           IOPC,
 * 	                                           IOPD,
 * 	                                           IOPE,
 * 	                                           IOPF,
 * 	                                           IOPG,
 * 	                                           ADC1,
 * 	                                           ADC2,
 * 	                                           TIM1,
 * 	                                           SPI1,
 * 	                                           TIM8,
 * 	                                           USART1,
 * 	                                           ADC3,
 * 	                                           TIM9,
 * 	                                           TIM10,
 * 	                                           TIM11  } ,
 *     				   UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : Void
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
void RCC_Set_APB2Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State);



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_APB1Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To APB1 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name { TIM2,
 * 	                                           TIM3,
 * 	                                           TIM4,
 * 	                                           TIM5,
 * 	                                           TIM6,
 * 	                                           TIM7,
 * 	                                           TIM12,
 * 	                                           TIM13,
 * 	                                           TIM14,
 * 	                                           WWDG,
 * 	                                           SPI2,
 * 	                                           SPI3,
 * 	                                           USART2,
 * 	                                           USART3,
 * 	                                           UART4,
 * 	                                           UART5,
 * 	                                           I2C1,
 * 	                                           I2C2,
 * 	                                           USB,
 * 	                                           CAN,
 * 	                                           BKP,
 * 	                                           PWR,
 * 	                                           DAC  } ,
 *
 *     				   UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : Void
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
void RCC_Set_APB1Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State);




#endif /* MCAL_RCC_INC_RCC_INTERFACE_H_ */
