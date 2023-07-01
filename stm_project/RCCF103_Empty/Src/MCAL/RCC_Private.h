/*
 * RCC_Private.h
 *
 *  Created on: Apr 17, 2023
 *      Author: ALTAWKEL
 */

#ifndef MCAL_RCC_PRIVATE_H_
#define MCAL_RCC_PRIVATE_H_
#include "stdio.h"
#include "Utils.h"
/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Clock configuration register (RCC_CFGR) Pins   *
 * * * * * * * * * * * * * * * * * * * * * * * * * */
enum{
	SW0,
	SW1,
	SWS0,
	SWS1,
	HPRE0,
	HPRE1,
	HPRE2,
	HPRE3,
	PPRE10,
	PPRE11,
	PPRE12,
	PPRE20,
	PPRE21,
	PPRE22,
	ADCPRE0,
	ADCPRE1,
	PLLSRC,
	PLLXTPRE,
	PLLMUL0,
	PLLMUL1,
	PLLMUL2,
	PLLMUL3,
	USBPRE,
	MCO0 = 24,
	MCO1,
	MCO2
};
/* * * * * * * * * * * * * * * * * * * * * *
 *  Clock control register (RCC_CR) Pins   *
 * * * * * * * * * * * * * * * * * * * * * */
enum{
	HSION,
	HSIRDY,
	HSITRIM0 = 3,
	HSITRIM1,
	HSITRIM2,
	HSITRIM3,
	HSITRIM4,
	HSICAL0,
	HSICAL1,
	HSICAL2,
	HSICAL3,
	HSICAL4,
	HSICAL5,
	HSICAL6,
	HSICAL7,
	HSEON,
	HSERDY,
	HSEBYP,
	CSSON,
	PLLON = 24,
	PLLRDY
};
/* * * * * * * * * * * * * * * * * * * * * *
 * 				 RCC registers  		   *
 * * * * * * * * * * * * * * * * * * * * * */
typedef struct {
	uint32_t CR;
	uint32_t CFGR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_APB2RSTR;
	uint32_t RCC_APB1RSTR;
	uint32_t RCC_AHBENR;
	uint32_t RCC_APB2ENR;
	uint32_t RCC_APB1ENR;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;

} RCC_REG_t;

typedef enum {
	HSI_clock,
	HSE_clock,
	PLL_clock,

} CLKtype_t;
/* * * * * * * * * * * * * * * * * * * * * *
 *  Peripheral AHB 		   				   *
 * * * * * * * * * * * * * * * * * * * * * */
typedef enum {
	DMA1EN,
	DMA2EN,
	SRAMEN,
	FLIFTEN = 4,
	CRCEN = 6,
	FSMCEN = 8,
	SDIOEN = 10

} PeripheralAHB_t;
/* * * * * * * * * * * * * * * * * * * * * *
 *  Peripheral APB2		   				   *
 * * * * * * * * * * * * * * * * * * * * * */
typedef enum {
	AFIOEN = 0,
	IOPAEN = 2,
	IOPBEN,
	IOPCEN,
	IOPDEN,
	IOPEEN,
	IOPFEN,
	IOPGEN,
	ADC1EN,
	ADC2EN,
	TIM1REN,
	SPI1EN,
	TIM8EN,
	USART1EN,
	ADC3EN,
	TIM9EN = 19,
	TIM10EN,
	TIM11EN

} PeripheralAPB2_t;
/* * * * * * * * * * * * * * * * * * * * * *
 *  Peripheral APB1		   				   *
 * * * * * * * * * * * * * * * * * * * * * */
typedef enum {
	TIM2EN = 0,
	TIM3EN,
	TIM4EN,
	TIM5EN,
	TIM6EN,
	TIM7EN,
	TIM12EN,
	TIM13EN,
	TIM14EN,
	WWDGEN = 11,
	SPI2EN = 14,
	SPI3EN,
	USART2EN = 17,
	USART3EN,
	UART4EN,
	UART5EN,
	I2C1EN,
	I2C2EN,
	USBEN,
	CANEN = 25,
	BKPEN = 27,
	PWREN,
	DACEN

} PeripheralAPB1_t;

typedef enum {
	PLL_input_clock_x_2 ,
	PLL_input_clock_x_3 ,
	PLL_input_clock_x_4 ,
	PLL_input_clock_x_5 ,
	PLL_input_clock_x_6 ,
	PLL_input_clock_x_7 ,
	PLL_input_clock_x_8 ,
	PLL_input_clock_x_9 ,
	PLL_input_clock_x_10,
	PLL_input_clock_x_11,
	PLL_input_clock_x_12,
	PLL_input_clock_x_13,
	PLL_input_clock_x_14,
	PLL_input_clock_x_15,
	PLL_input_clock_x_16,

} PLLMUL_t;

typedef enum {
	HSE_clock_not_divided,
	HSE_clock_divided_by_2,


} HSEDIV_t;

typedef enum {
	CLK_OFF,
	CLK_ON,


} CLKStatus_t;
typedef enum {

	NOTbypasseds,
	bypasseds,

} bypassedsSTS_t;
typedef enum {

	Clock_detector_OFF,
	Clock_detector_ON,

} Clock_Detector_t;

RCC_REG_t* RCC = (RCC_REG_t*) (0x40021000);


#endif /* MCAL_RCC_PRIVATE_H_ */
