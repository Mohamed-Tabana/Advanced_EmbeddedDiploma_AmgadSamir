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


/******************************* AHB  peripheral Base Addresses 	*******************************/
#define RCC_BASE_ADDRESS 		0x40021000UL 


/******************************* APB1 peripheral Base Addresses	 	*******************************/



/******************************* APB2 peripheral Base Addresses 	*******************************/
#define GPIOA_BASE_ADDRESS 	0x40010800UL 
#define GPIOB_BASE_ADDRESS 	0x40010C00UL 
#define GPIOC_BASE_ADDRESS 	0x40011000UL 
#define GPIOD_BASE_ADDRESS 	0x40011400UL 
#define GPIOE_BASE_ADDRESS 	0x40011800UL 
#define GPIOF_BASE_ADDRESS 	0x40011C00UL 
#define GPIOG_BASE_ADDRESS 	0x40012000UL 


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

/******************************* GPIO Peripheral Definitions 		 *******************************/

 #define GPIOA       	   ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
 #define GPIOB             ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
 #define GPIOC             ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
 #define GPIOD             ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
 #define GPIOE             ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
 #define GPIOF             ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
 #define GPIOG             ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)



/******************************* RCC Peripheral Definitions 		 *******************************/

 #define RCC       	   ((RCC_RegDef_t*)RCC_BASE_ADDRESS)
 /******************************* STK Peripheral Definitions 		 *******************************/

 #define STK  		   ((MSTK_RegDef_t*)SysTick_BASE_ADDRESS)






#endif
