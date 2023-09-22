/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 10/4/2023				  	  **************/
/********* FILE NAME : RCC_Private.h				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/
#ifndef MCAL_RCC_INC_RCC_PRIVATE_H_
#define MCAL_RCC_INC_RCC_PRIVATE_H_

enum ClockTypes 		{HSE,HSI,LSE,LSI,PLL};
enum ClockStatus 		{ON,OFF};

#define TIME_OUT 		10000

#define HSE_DivideBy2 	1
#define HSE_DivideBy1 	0

#define ENABLED			1
#define DISABLED		0



enum PLL_MUL
{
	BY_2,
	BY_3,
	BY_4,
	BY_5,
	BY_6,
	BY_7,
	BY_8,
	BY_9,
	BY_10,
	BY_11,
	BY_12,
	BY_13,
	BY_14,
	BY_15,
	BY_16
};

enum AHB_Periphrals {
	AHB_DMA1,
	AHB_DMA2,
	AHB_SRAM,
	AHB_FLITF=4,
	AHB_CRC=6,
	AHB_FSMC=8,
	AHB_SDIO=10
};


enum APB2_Periphrals {
	APB2_AFIO,
	APB2_IOPA=2,
	APB2_IOPB,
	APB2_IOPC,
	APB2_IOPD,
	APB2_IOPE,
	APB2_IOPF,
	APB2_IOPG,
	APB2_ADC1,
	APB2_ADC2,
	APB2_TIM1,
	APB2_SPI1,
	APB2_TIM8,
	APB2_USART1,
	APB2_ADC3,
	APB2_TIM9=19,
	APB2_TIM10,
	APB2_TIM11

};



enum APB1_Periphrals{
	APB1_TIM2,
	APB1_TIM3,
	APB1_TIM4,
	APB1_TIM5,
	APB1_TIM6,
	APB1_TIM7,
	APB1_TIM12,
	APB1_TIM13,
	APB1_TIM14,
	APB1_WWDG=11,
	APB1_SPI2=14,
	APB1_SPI3,
	APB1_USART2=17,
	APB1_USART3,
	APB1_UART4,
	APB1_UART5,
	APB1_I2C1,
	APB1_I2C2,
	APB1_USB,
	APB1_CAN=25,
	APB1_BKP=27,
	APB1_PWR,
	APB1_DAC
};


#endif /* MCAL_RCC_INC_RCC_PRIVATE_H_ */
