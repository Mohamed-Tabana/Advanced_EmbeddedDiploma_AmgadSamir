#ifndef STM32F103_H
#define STM32F103_H
#include "Utils.h"
#include "stdio.h"
/******************************* Various Memories Base Addresses 	*******************************/
#define FLASH_BASE_ADDRESS	0x0UL 
#define SRAM_BASE_ADDRESS 	0x0UL 
#define ROM_BASE_ADDRESS 	0x0UL 

/******************************* Core peripheral Base Addresses 	*******************************/
#define SysTick_BASE_ADDRESS 	0xE000E010UL
#define NVIC_BASE_ADDRESS 	    0xE000E100UL
#define SCB_BASE_ADDRESS 	    0xE000ED00UL


/******************************* AHB  peripheral Base Addresses 	*******************************/
#define RCC_BASE_ADDRESS 		0x40021000UL 


/******************************* APB1 peripheral Base Addresses	 	*******************************/
#define SPI2_BASE_ADDRESS 		0x40003800UL
#define SPI3_BASE_ADDRESS 		0x40003C00UL



/******************************* APB2 peripheral Base Addresses 	*******************************/
#define GPIOA_BASE_ADDRESS 	0x40010800UL 
#define GPIOB_BASE_ADDRESS 	0x40010C00UL 
#define GPIOC_BASE_ADDRESS 	0x40011000UL 
#define GPIOD_BASE_ADDRESS 	0x40011400UL 
#define GPIOE_BASE_ADDRESS 	0x40011800UL 
#define GPIOF_BASE_ADDRESS 	0x40011C00UL 
#define GPIOG_BASE_ADDRESS 	0x40012000UL 

#define EXTI_BASE_ADDRESS 	0x40010400UL
#define AFIO_BASE_ADDRESS 	0x40010000UL

#define SPI1_BASE_ADDRESS 	0x40013000UL


/******************************* GPIO Register Definition Structure *******************************/
typedef struct 
{

	volatile uint32_t CR[2];    // Control register
	volatile uint32_t IDR;      // Input type register
	volatile uint32_t ODR;      // Output data register
	volatile uint32_t BSRR;     // Bit set/reset register
	volatile uint32_t BRR;      //
	volatile uint32_t LCKR;     // Configuration lock register
	volatile uint32_t AFR[2];   // Alternate function register

}GPIO_RegDef_t;


/******************************* RCC Register Definition Structure *******************************/


typedef struct {
	volatile uint32_t CR;         // Clock control register
	volatile uint32_t CFGR;       // PLL configuration register
	volatile uint32_t CIR;        // Clock interrupt register
	volatile uint32_t APB2RSTR;   // APB2 peripheral reset register
	volatile uint32_t APB1RSTR;   // APB1 peripheral reset register
	volatile uint32_t AHBENR;     // AHB peripheral clock enable register
	volatile uint32_t APB2ENR;    // APB2 peripheral clock enable register
	volatile uint32_t APB1ENR;    // APB1 peripheral clock enable register
	volatile uint32_t BDCR;       // Backup domain control register
	volatile uint32_t CSR;        // Clock control & status register

} RCC_RegDef_t;
/******************************* STK Register Definition Structure *******************************/

typedef struct{
	volatile uint32_t STK_CTRL;
	volatile uint32_t STK_LOAD;
	volatile uint32_t STK_VAL;
	volatile uint32_t STK_CALIB;

}MSTK_RegDef_t;
/******************************* NVIC Register Definition Structure *******************************/

typedef struct{
	volatile uint32_t NVIC_ISER[3];
	volatile uint32_t Reserved0[30];
	volatile uint32_t NVIC_ICER[3];
	volatile uint32_t Reserved1[30];
	volatile uint32_t NVIC_ISPR[3];
	volatile uint32_t Reserved2[30];
	volatile uint32_t NVIC_ICPR[3];
	volatile uint32_t Reserved3[30];
	volatile uint32_t NVIC_IABR[3];
	volatile uint32_t Reserved4[30];
	volatile uint8_t NVIC_IPR [84];
	volatile uint32_t Reserved5[695];
	volatile uint32_t NVIC_STIR;

}NVIC_RegDef_t;
/******************************* SCB Register Definition Structure *******************************/

typedef struct{
	volatile uint32_t SCB_ACTLR ;
	volatile uint32_t SCB_CPUID ;
	volatile uint32_t SCB_ICSR ;
	volatile uint32_t SCB_VTOR ;
	volatile uint32_t SCB_AIRCR ;
	volatile uint32_t SCB_SCR ;
	volatile uint32_t SCB_CCR ;
	volatile uint8_t  SCB_SHPR[12] ;
	volatile uint32_t SCB_SHCRS ;
	volatile uint32_t SCB_CFSR ;
	volatile uint32_t SCB_HFSR ;
	volatile uint32_t SCB_MMAR ;
	volatile uint32_t SCB_BFAR ;

}SCB_RegDef_t;
/******************************* EXTI Register Definition Structure *******************************/

typedef struct{
	volatile uint32_t EXTI_IMR ;
	volatile uint32_t EXTI_EMR ;
	volatile uint32_t EXTI_RTSR ;
	volatile uint32_t EXTI_FTSR ;
	volatile uint32_t EXTI_SWIER ;
	volatile uint32_t EXTI_PR ;

}EXTI_RegDef_t;
/******************************* AFIO Register Definition Structure *******************************/

typedef struct{
	volatile uint32_t AFIO_EVCR ;
	volatile uint32_t AFIO_MAPR_low_medium_high;
	volatile uint32_t AFIO_MAPR_connectivity_line_devices ;
	volatile uint32_t AFIO_EXTICR[4] ;

}AFIO_RegDef_t;

typedef struct{
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
}SPI_RegDef_t;
/******************************* GPIO Peripheral Definitions 		 *******************************/

#define GPIOA       	   ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB             ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC             ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD             ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE             ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF             ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG             ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)



/******************************* RCC Peripheral Definitions 		 *******************************/
#define  RCC       	   ((RCC_RegDef_t*)RCC_BASE_ADDRESS)
/******************************* STK Peripheral Definitions 		 *******************************/
#define  STK  		   ((MSTK_RegDef_t*)SysTick_BASE_ADDRESS)
/******************************* NVIC Peripheral Definitions 		 *******************************/
#define  NVIC  		   ((NVIC_RegDef_t*)NVIC_BASE_ADDRESS)
/******************************* NVIC Peripheral Definitions 		 *******************************/
#define  SCB  		   ((SCB_RegDef_t*)SCB_BASE_ADDRESS)
/******************************* EXTI Peripheral Definitions 		 *******************************/
#define  EXTI  		   ((EXTI_RegDef_t*)EXTI_BASE_ADDRESS)
/******************************* EXTI Peripheral Definitions 		 *******************************/
#define  AFIO  		   ((AFIO_RegDef_t*)AFIO_BASE_ADDRESS)
/******************************* SPI1 Peripheral Definitions 		 *******************************/
#define  SPI1 	       ((SPI_RegDef_t*)SPI1_BASE_ADDRESS)
/******************************* SPI2 Peripheral Definitions 		 *******************************/
#define  SPI2 	       ((SPI_RegDef_t*)SPI2_BASE_ADDRESS)
/******************************* SPI3 Peripheral Definitions 		 *******************************/
#define  SPI3 	       ((SPI_RegDef_t*)SPI3_BASE_ADDRESS)






#endif
