/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 1/5/2023					  	  **************/
/********* FILE NAME : STM32F103xx.h				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/


#ifndef INC_STM32F103XX_H_
#define INC_STM32F103XX_H_

/************************	  	BASE MEMORY ADDRESSES		    	************************/
#define FLASH_BASE_ADDRESS      			0x08000000UL
#define SRAM_BASE_ADDRESS   	   			0x20000000UL
#define PERIPHERAL_BASE_ADDRESS 	     	0x40000000UL


/************************     	 CORE PERIPHERALS BASE ADDRESSES	************************/
#define SYSTICK_BASE_ADDRESS				0xE000E010UL
#define NVIC_BASE_ADDRESS         			0xE000E100UL

/************************     	AHB  BASE PERIPHERALS ADDRESSES		************************/
#define EXTI_BASE_ADDRESS        			0x40010400UL
#define AFIO_BASE_ADDRESS        			0x40010000UL
#define RCC_BASE_ADDRESS					0x40021000UL

/************************     	APB 1 BASE PERIPHERALS ADDRESSES	************************/
#define SPI2_BASE_ADDRESS					0x40003800UL

/************************     	APB 2 BASE PERIPHERALS ADDRESSES	************************/

#define GPIOA_BASE_ADDRESS			        0x40010800UL
#define GPIOB_BASE_ADDRESS                  0x40010C00UL
#define GPIOC_BASE_ADDRESS                  0x40011000UL
#define GPIOD_BASE_ADDRESS                  0x40011400UL
#define GPIOE_BASE_ADDRESS                  0x40011800UL
#define GPIOF_BASE_ADDRESS                  0x40011C00UL
#define GPIOG_BASE_ADDRESS                  0x40012000UL

#define SPI1_BASE_ADDRESS					0x40013000UL
/************************     	GPIO REGISTERS DEFINITION			************************/
typedef struct{
	uint32_t CR[2];
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSSR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_REG_t;

/************************     	GPIO PERIPHERAL DEFINITION			************************/
#define GPIOA					((GPIO_REG_t *)(GPIOA_BASE_ADDRESS))
#define GPIOB					((GPIO_REG_t *)(GPIOB_BASE_ADDRESS))
#define GPIOC                   ((GPIO_REG_t *)(GPIOC_BASE_ADDRESS))
#define GPIOD                   ((GPIO_REG_t *)(GPIOD_BASE_ADDRESS))
#define GPIOE                   ((GPIO_REG_t *)(GPIOE_BASE_ADDRESS))
#define GPIOF                   ((GPIO_REG_t *)(GPIOF_BASE_ADDRESS))
#define GPIOG                   ((GPIO_REG_t *)(GPIOG_BASE_ADDRESS))


/************************     	AFIO REGISTERS DEFINITION			************************/
typedef struct
{
	volatile uint32_t EVCR ;        /* Event control register                          */
	volatile uint32_t MAPR ;        /* SYSCFG memory remap register                    */
	volatile uint32_t EXTICR[4] ;   /*SYSCFG external interrupt configuration register */
	uint32_t Reserved1;             /* offset                                          */
	volatile uint32_t MAPR2 ;       /* AF remap and debug I/O configuration register2  */

}AFIO_RegDef_t;

#define 	AFIO            	    ((AFIO_RegDef_t * )(AFIO_BASE_ADDRESS))

/************************     	AFIO PERIPHERAL DEFINITION			************************/

/************************     	SYSTICK REGISTERS DEFINITION		************************/

typedef struct{

	volatile uint32_t	CTRL;						/*SysTick control and status register*/
	volatile uint32_t	LOAD;						/*SysTick Reload value register*/
	volatile uint32_t	VAL;						/*SysTick Current value register*/

}SYSTICK_REG_t;

#define SYSTICK 					((SYSTICK_REG_t *)(SYSTICK_BASE_ADDRESS))

/************************     	  SPI REGISTERS DEFINITION			************************/
typedef struct {

	volatile uint32_t 	SPI_CR1;		/*SPI Control Register 1*/
	volatile uint32_t 	SPI_CR2;		/*SPI Control Register 2*/
	volatile uint32_t 	SPI_SR;			/*SPI Status Register */
	volatile uint32_t 	SPI_DR;			/*SPI Data Register*/
	volatile uint32_t 	SPI_CRCPR;		/*SPI CRC Polynomial Register*/
	volatile uint32_t 	SPI_RXCRCR;		/*SPI RX CRC Register*/
	volatile uint32_t 	SPI_TXCRCR;		/*SPI TX CRC Register*/
	volatile uint32_t 	SPI_I2SCFGR;	/*SPI_I2C Configuration Register*/
	volatile uint32_t 	SPI_I2SPR;		/*SPI_I2C Prescaler Register*/

}SPI_REG_t;

#define SPI_1					((SPI_REG_t	*)(SPI1_BASE_ADDRESS))
#define SPI_2            		((SPI_REG_t	*)(SPI2_BASE_ADDRESS))

/********************    EXTI REGISTER DEFINITION STRUCTURE        ********************************/

typedef struct
{
	volatile uint32_t IMR ;       /* Interrupt mask register            */
	volatile uint32_t EMR ;       /* Event mask register                */
	volatile uint32_t RTSR ;      /* Rising trigger selection register  */
	volatile uint32_t FTSR ;      /* Falling trigger selection register */
	volatile uint32_t SWIER ;     /* Software interrupt event register  */
	volatile uint32_t PR ;        /* Pending register                   */

}EXTI_RegDef_t;

#define EXTI                      ( (EXTI_RegDef_t*)EXTI_BASE_ADDRESS )

/********************    NVIC REGISTER DEFINITION STRUCTURE        ********************************/

typedef struct
{
	volatile uint32_t ISER[3];		/* Interrupt set-enable register */
	uint32_t Reserved2[30];			/* Offset */
	volatile uint32_t ICER[3]; 		/* Interrupt clear-enable register */
	uint32_t Reserved3[30];			/* Offset */
	volatile uint32_t ISPR[3];		/* Interrupt set-pending register */
	uint32_t Reserved4[30];			/* Offset */
	volatile uint32_t ICPR[3];		/* Interrupt clear-pending register */
	uint32_t Reserved5[30];			/* Offset */
	volatile uint32_t IABR[3];		/* Interrupt active bit register */
	uint32_t Reserved6[62];			/* Offset */
	volatile uint8_t IPR[33];		/* Interrupt Priority Registers */

} NVIC_RegDef_t;

#define NVIC                     ( (NVIC_RegDef_t*) NVIC_BASE_ADDRESS )

/********************    RCC REGISTER DEFINITION STRUCTURE        ********************************/

typedef struct
{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
}RCC_REG_t;

#define RCC 				((RCC_REG_t*)(RCC_BASE_ADDRESS))
/************************     	PERIPHERAL REGISTER BITS DEFINITION	************************/

/************************     	ISR DEFINITIONS 					************************/




#endif /* INC_STM32F103XX_H_ */
