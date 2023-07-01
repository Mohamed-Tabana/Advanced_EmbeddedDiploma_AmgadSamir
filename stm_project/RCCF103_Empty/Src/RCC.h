/*
 * RCC.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Mohamed TABANA
 */

#ifndef RCC_H_
#define RCC_H_

#include "Utils.h"

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

typedef enum {
	DMA1EN,
	DMA2EN,
	SRAMEN,
	FLIFTEN = 4,
	CRCEN = 6,
	FSMCEN = 8,
	SDIOEN = 10

} PeripheralAHB_t;

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

RCC_REG_t* RCC = (RCC_REG_t*) (0x40021000);

void RCC_SetCLKSTS(CLKtype_t copy_tCLKtype, CLKStatus_t copy_tCLKStatus);

void RCC_SetSYSCLK(CLKtype_t copy_tCLKtype);
void RCC_HSECONFIG(HSEDIV_t copy_tHSEDIV);
void RCC_PLLCONFIG(PLLMUL_t copy_tPLLMUX,CLKtype_t copy_tCLKtype);

void RCC_AHBEnableCLK(PeripheralAHB_t peripheral);
void RCC_AHBDisableCLK(PeripheralAHB_t peripheral);
void RCC_APB1EnableCLK(PeripheralAPB1_t peripheral);
void RCC_APB1DisableCLK(PeripheralAPB1_t peripheral);
/*
 * sdkd
 */

void RCC_APB2EnableCLK(PeripheralAPB2_t peripheral);

void RCC_APB2DisableCLK(PeripheralAPB2_t peripheral);


#endif /* RCC_H_ */
