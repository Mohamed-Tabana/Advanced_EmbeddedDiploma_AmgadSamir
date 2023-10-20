
#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#define VECTKEY 0x05FA

/* * * * * * * * * * * * * * * * * * * * * *
 * 				NVIC interrupts 		   *
 * * * * * * * * * * * * * * * * * * * * * */

typedef enum {
	NVIC_NonMaskableInt         = -14,  /*!< Non Maskable Interrupt */
	NVIC_HardFault              = -13,  /*!< Hard Fault Interrupt */
	NVIC_MemoryManagement       = -12,  /*!< Memory Management Interrupt */
	NVIC_BusFault               = -11,  /*!< Bus Fault Interrupt */
	NVIC_UsageFault             = -10,  /*!< Usage Fault Interrupt */
	NVIC_SVCall                 = -5,   /*!< SV Call Interrupt */
	NVIC_DebugMonitor           = -4,   /*!< Debug Monitor Interrupt */
	NVIC_PendSV                 = -2,   /*!< Pend SV Interrupt */
	NVIC_SysTick                = -1,   /*!< System Tick Interrupt */
	NVIC_WWDG                   = 0,    /*!< Window Watchdog Interrupt */
	NVIC_PVD                    = 1,    /*!< PVD through EXTI Line Detection Interrupt */
	NVIC_TAMP_STAMP             = 2,    /*!< Tamper and TimeStamp interrupts through the EXTI line */
	NVIC_RTC_WKUP               = 3,    /*!< RTC Wakeup interrupt through the EXTI line */
	NVIC_FLASH                  = 4,    /*!< FLASH global Interrupt */
	NVIC_NVIC_RCC                    = 5,    /*!< RCC global Interrupt */
	NVIC_EXTI0                  = 6,    /*!< EXTI Line0 Interrupt */
	NVIC_EXTI1                  = 7,    /*!< EXTI Line1 Interrupt */
	NVIC_EXTI2                  = 8,    /*!< EXTI Line2 Interrupt */
	NVIC_EXTI3                  = 9,    /*!< EXTI Line3 Interrupt */
	NVIC_EXTI4                  = 10,   /*!< EXTI Line4 Interrupt */
	NVIC_DMA1_Stream0           = 11,   /*!< DMA1 Stream 0 global Interrupt */
	NVIC_DMA1_Stream1           = 12,   /*!< DMA1 Stream 1 global Interrupt */
	NVIC_DMA1_Stream2           = 13,   /*!< DMA1 Stream 2 global Interrupt */
	NVIC_DMA1_Stream3           = 14,   /*!< DMA1 Stream 3 global Interrupt */
	NVIC_DMA1_Stream4           = 15,   /*!< DMA1 Stream 4 global Interrupt */
	NVIC_DMA1_Stream5           = 16,   /*!< DMA1 Stream 5 global Interrupt */
	NVIC_DMA1_Stream6           = 17,   /*!< DMA1 Stream 6 global Interrupt */
	NVIC_ADC                    = 18,   /*!< ADC1, ADC2 and ADC3 global Interrupts */
	NVIC_CAN1_TX                = 19,   /*!< CAN1 TX Interrupt */
	NVIC_CAN1_RX0               = 20,   /*!< CAN1 RX0 Interrupt */
	NVIC_CAN1_RX1               = 21,   /*!< CAN1 RX1 Interrupt */
	NVIC_CAN1_SCE               = 22,   /*!< CAN1 SCE Interrupt */
	NVIC_EXTI9_5                = 23,   /*!< External Line[9:5] Interrupts */
	NVIC_TIM1_BRK_TIM9          = 24,   /*!< TIM1 Break interrupt and TIM9 global interrupt */
	NVIC_TIM1_UP_TIM10          = 25,   /*!< TIM1 Update Interrupt and TIM10 global interrupt */
	NVIC_TIM1_TRG_COM_TIM11     = 26,   /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
	NVIC_TIM1_CC                = 27,   /*!< TIM1 Capture Compare Interrupt */
	NVIC_TIM2                   = 28,   /*!< TIM2 global Interrupt */
	NVIC_TIM3                   = 29,   /*!< TIM3 global Interrupt */
	NVIC_TIM4                   = 30,   /*!< TIM4 global Interrupt */
	NVIC_I2C1_EV                = 31,   /*!< I2C1 Event Interrupt */
	NVIC_I2C1_ER                = 32,   /*!< I2C1 Error Interrupt */
	NVIC_I2C2_EV                = 33,   /*!< I2C2 Event Interrupt */
	NVIC_I2C2_ER                = 34,   /*!< I2C2 Error Interrupt */
	NVIC_SPI1                   = 35,   /*!< SPI1 global Interrupt */
	NVIC_SPI2                   = 36,   /*!< SPI2 global Interrupt */
	NVIC_USART1                 = 37,   /*!< USART1 global Interrupt */
	NVIC_USART2                 = 38,   /*!< USART2 global Interrupt */
	NVIC_USART3                 = 39,   /*!< USART3 global Interrupt */
	NVIC_EXTI15_10              = 40,   /*!< External Line[15:10] Interrupts */
	NVIC_RTC_Alarm              = 41,   /*!< RTC Alarm (A and B) through EXTI Line Interrupt */
	NVIC_OTG_FS_WKUP            = 42,   /*!< USB OTG FS Wakeup through EXTI line interrupt */
	NVIC_TIM8_BRK_TIM12         = 43,   /*!< TIM8 Break Interrupt and TIM12 global interrupt */
	NVIC_TIM8_UP_TIM13          = 44,   /*!< TIM8 Update Interrupt and TIM13 global interrupt */
	NVIC_TIM8_TRG_COM_TIM14     = 45,   /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
	NVIC_TIM8_CC                = 46,   /*!< TIM8 Capture Compare Interrupt */
	NVIC_DMA1_Stream7           = 47,   /*!< DMA1 Stream7 Interrupt */
	NVIC_FMC                    = 48,   /*!< FMC global Interrupt */
	NVIC_SDIO                   = 49,   /*!< SDIO global Interrupt */
	NVIC_TIM5                   = 50,   /*!< TIM5 global Interrupt */
	NVIC_SPI3                   = 51,   /*!< SPI3 global Interrupt */
	NVIC_UART4                  = 52,   /*!< UART4 global Interrupt */
	NVIC_UART5                  = 53,   /*!< UART5 global Interrupt */
	NVIC_TIM6_DAC               = 54,   /*!< TIM6 global and DAC1&2 underrun error */
	NVIC_TIM7                   = 55,   /*!< TIM7 global interrupt */
	NVIC_DMA2_Stream0           = 56,   /*!< DMA2 Stream 0 global Interrupt */
	NVIC_DMA2_Stream1           = 57,   /*!< DMA2 Stream 1 global Interrupt */
	NVIC_DMA2_Stream2           = 58,   /*!< DMA2 Stream 2 global Interrupt */
	NVIC_DMA2_Stream3           = 59,   /*!< DMA2 Stream 3 global Interrupt */
	NVIC_DMA2_Stream4           = 60,   /*!< DMA2 Stream 4 global Interrupt */
	NVIC_ETH                    = 61,   /*!< Ethernet global Interrupt */
	NVIC_ETH_WKUP               = 62,   /*!< Ethernet Wakeup through EXTI line Interrupt */
	NVIC_CAN2_TX                = 63,   /*!< CAN2 TX Interrupt */
	NVIC_CAN2_RX0               = 64,   /*!< CAN2 RX0 Interrupt */
	NVIC_CAN2_RX1               = 65,   /*!< CAN2 RX1 Interrupt */
	NVIC_CAN2_SCE               = 66,   /*!< CAN2 SCE Interrupt */
	NVIC_OTG_FS                 = 67,   /*!< USB OTG FS global Interrupt */
	NVIC_DMA2_Stream5           = 68,   /*!< DMA2 Stream 5 global interrupt */
	NVIC_DMA2_Stream6           = 69,   /*!< DMA2 Stream 6 global interrupt */
	NVIC_DMA2_Stream7           = 70,   /*!< DMA2 Stream 7 global interrupt */
	NVIC_USART6                 = 71,   /*!< USART6 global interrupt */
	NVIC_I2C3_EV                = 72,   /*!< I2C3 event interrupt */
	NVIC_I2C3_ER                = 73,   /*!< I2C3 error interrupt */
	NVIC_FPU					= 81,
	NVIC_SPI4				    = 84
}Interrupt_t;

typedef enum {
	Four_Bit_Group_Zero_Bit_sub,
	Three_Bit_Group_One_Bit_sub=4,
	Two_Bit_Group_Two_Bit_sub,
	One_Bit_Group_Three_Bit_sub,
	Zero_Bit_Group_Four_Bit_sub,


}NVIC_GroupPriorityCfg;


#endif
