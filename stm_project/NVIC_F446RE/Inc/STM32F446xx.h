#ifndef STM32f446xx_H
#define STM32f446xx_H
#include "stdio.h"
/******************************* Various Memories Base Addresses 	*******************************/
#define FLASH_BASE_ADDRESS	0x08000000UL 
#define SRAM_BASE_ADDRESS 	0x20000000UL 
#define ROM_BASE_ADDRESS 	0x1FFF0000UL 

/******************************* Core peripheral Base Addresses 	*******************************/
#define SysTick_BASE_ADDRESS 	0xE000E010UL
#define NVIC_BASE_ADDRESS 	    0xE000E100UL
#define SCB_BASE_ADDRESS 	    0xE000E008UL

/******************************* AHB1 peripheral Base Addresses 	*******************************/
#define GPIOA_BASE_ADDRESS 	0x40020000UL 
#define GPIOB_BASE_ADDRESS 	0x40020400UL 
#define GPIOC_BASE_ADDRESS 	0x40020800UL 
#define GPIOD_BASE_ADDRESS 	0x40020C00UL 
#define GPIOE_BASE_ADDRESS 	0x40021000UL 
#define GPIOF_BASE_ADDRESS 	0x40021400UL 
#define GPIOG_BASE_ADDRESS 	0x40021800UL 
#define GPIOH_BASE_ADDRESS 	0x40021C00UL 

#define RCC_BASE_ADDRESS 		0x40023800UL 



/******************************* AHB2 peripheral Base Addresses 	*******************************/



/******************************* AHB3 peripheral Base Addresses		*******************************/



/******************************* APB1 peripheral Base Addresses	 	*******************************/



/******************************* APB2 peripheral Base Addresses 	*******************************/



/******************************* GPIO Register Definition Structure *******************************/
typedef struct 
{

  volatile uint32_t MODER;    // Mode register
  volatile uint32_t OTYPER;   // Output type register
  volatile uint32_t OSPEEDR;  // Output speed register
  volatile uint32_t PUPDR;    // Pull-up/pull-down register
  volatile uint32_t IDR;      // Input data register
  volatile uint32_t ODR;      // Output data register
  volatile uint32_t BSRR;     // Bit set/reset register
  volatile uint32_t LCKR;     // Configuration lock register
  volatile uint32_t AFR[2];   // Alternate function register

}GPIO_RegDef_t;


/******************************* RCC Register Definition Structure *******************************/


typedef struct {
  volatile uint32_t CR;         // Clock control register
  volatile uint32_t PLLCFGR;    // PLL configuration register
  volatile uint32_t CFGR;       // Clock configuration register
  volatile uint32_t CIR;        // Clock interrupt register
  volatile uint32_t AHB1RSTR;   // AHB1 peripheral reset register
  volatile uint32_t AHB2RSTR;   // AHB2 peripheral reset register
  volatile uint32_t AHB3RSTR;   // AHB3 peripheral reset register
  uint32_t RESERVED0;           // Reserved
  volatile uint32_t APB1RSTR;   // APB1 peripheral reset register
  volatile uint32_t APB2RSTR;   // APB2 peripheral reset register
  uint32_t RESERVED1[2];        // Reserved
  volatile uint32_t AHB1ENR;    // AHB1 peripheral clock enable register
  volatile uint32_t AHB2ENR;    // AHB2 peripheral clock enable register
  volatile uint32_t AHB3ENR;    // AHB3 peripheral clock enable register
  uint32_t RESERVED2;           // Reserved
  volatile uint32_t APB1ENR;    // APB1 peripheral clock enable register
  volatile uint32_t APB2ENR;    // APB2 peripheral clock enable register
  uint32_t RESERVED3[2];        // Reserved
  volatile uint32_t AHB1LPENR;  // AHB1 peripheral clock enable in low power mode register
  volatile uint32_t AHB2LPENR;  // AHB2 peripheral clock enable in low power mode register
  volatile uint32_t AHB3LPENR;  // AHB3 peripheral clock enable in low power mode register
  uint32_t RESERVED4;           // Reserved
  volatile uint32_t APB1LPENR;  // APB1 peripheral clock enable in low power mode register
  volatile uint32_t APB2LPENR;  // APB2 peripheral clock enable in low power mode register
  uint32_t RESERVED5[2];        // Reserved
  volatile uint32_t BDCR;       // Backup domain control register
  volatile uint32_t CSR;        // Clock control & status register
  uint32_t RESERVED6[2];        // Reserved
  volatile uint32_t SSCGR;      // Spread spectrum clock generation register
  volatile uint32_t PLLI2SCFGR; // PLLI2S configuration register
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
	volatile uint32_t NVIC_ISER[8];
	volatile uint32_t Reserved1[24];
	volatile uint32_t NVIC_ICER[8];
	volatile uint32_t Reserved2[24];
	volatile uint32_t NVIC_ISPR[8];
	volatile uint32_t Reserved3[24];
	volatile uint32_t NVIC_ICPR[8];
	volatile uint32_t Reserved4[24];
	volatile uint32_t NVIC_IABR[8];
	volatile uint32_t Reserved5[24];
	volatile uint8_t  NVIC_IPR [240];
	volatile uint32_t Reserved6[644];
	volatile uint32_t NVIC_STIR;

}NVIC_RegDef_t;
/******************************* SCB Register Definition Structure *******************************/
typedef struct{
	uint32_t ACTLR;
	uint32_t CPUID;
	uint32_t ICSR;
	uint32_t VTOR;
	uint32_t AIRCR;
	uint32_t SCR;
	uint32_t CCR;
	uint8_t  SHP[12U];
	uint32_t SHCSR;
}SCB_RegDef_t;
/******************************* GPIO Peripheral Definitions 		 *******************************/
 #define GPIOA       	   ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
 #define GPIOB             ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
 #define GPIOC             ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
 #define GPIOD             ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
 #define GPIOE             ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
 #define GPIOF             ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
 #define GPIOG             ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
 #define GPIOH             ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)


/******************************* RCC Peripheral Definitions 		 *******************************/
 #define RCC       	   ((RCC_RegDef_t*)RCC_BASE_ADDRESS)
 /******************************* STK Peripheral Definitions 		 *******************************/
 #define STK  		   ((MSTK_RegDef_t*)SysTick_BASE_ADDRESS)
 /******************************* NVIC Peripheral Definitions 		 *******************************/
 #define NVIC  		   ((NVIC_RegDef_t*)NVIC_BASE_ADDRESS)
/******************************* SCB Peripheral Definitions 		 *******************************/
#define  SCB  		   ((SCB_RegDef_t*)SCB_BASE_ADDRESS)






#endif
