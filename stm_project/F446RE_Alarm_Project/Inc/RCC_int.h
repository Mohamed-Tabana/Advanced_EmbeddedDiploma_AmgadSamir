#ifndef RCC_INT_H
#define RCC_INT_H

typedef enum {
	RCC_AHB1ENR_GPIOAEN = (0),
	RCC_AHB1ENR_GPIOBEN = (1),
	RCC_AHB1ENR_GPIOCEN = (2),
	RCC_AHB1ENR_GPIODEN = (3),
	RCC_AHB1ENR_GPIOEEN = (4),
	RCC_AHB1ENR_GPIOFEN = (5),
	RCC_AHB1ENR_GPIOGEN = (6),
	RCC_AHB1ENR_GPIOHEN = (7),
	RCC_AHB1ENR_CRCEN = (12),
	RCC_AHB1ENR_DMA1EN = (21),
	RCC_AHB1ENR_DMA2EN = (22),
	RCC_AHB1ENR_DMA2DEN = (23),
	RCC_AHB1ENR_OTGHSEN = (29),
	RCC_AHB1ENR_OTGHSULPIEN = (30),

} PeripheralAHB1_t;


///* * * * * * * * * * * * * * * * * * * * * *
// *  @PeripheralAHB2_t ENUM   				   *
// * * * * * * * * * * * * * * * * * * * * * */
//typedef enum {
//	RCC_AHB2ENR_DCMIEN = (0),
//	RCC_AHB2ENR_OTGFSEN = (7),
//
//} PeripheralAHB2_t;

/* * * * * * * * * * * * * * * * * * * * * *
 *  @PeripheralAPB1_t ENUM		   				   
 * * * * * * * * * * * * * * * * * * * * * */
typedef enum {
	RCC_APB1ENR_TIM2EN = (0),
	RCC_APB1ENR_TIM3EN = (1),
	RCC_APB1ENR_TIM4EN = (2),
	RCC_APB1ENR_TIM5EN = (3),
	RCC_APB1ENR_TIM6EN = (4),
	RCC_APB1ENR_TIM7EN = (5),
	RCC_APB1ENR_TIM12EN = (6),
	RCC_APB1ENR_TIM13EN = (7),
	RCC_APB1ENR_TIM14EN = (8),
	RCC_APB1ENR_WWDGEN = (11),
	RCC_APB1ENR_SPI2EN = (14),
	RCC_APB1ENR_SPI3EN = (15),
	RCC_APB1ENR_USART2EN = (17),
	RCC_APB1ENR_USART3EN = (18),
	RCC_APB1ENR_UART4EN = (19),
	RCC_APB1ENR_UART5EN = (20),
	RCC_APB1ENR_I2C1EN = (21),
	RCC_APB1ENR_I2C2EN = (22),
	RCC_APB1ENR_I2C3EN = (23),
	RCC_APB1ENR_CAN1EN = (25),
	RCC_APB1ENR_CAN2EN = (26),
	RCC_APB1ENR_PWREN = (28),
	RCC_APB1ENR_DACEN = (29),
} PeripheralAPB1_t;

/* * * * * * * * * * * * * * * * * * * * * *
 *  @PeripheralAPB2_t ENUM	   				   *
 * * * * * * * * * * * * * * * * * * * * * */
typedef enum {
	RCC_APB2ENR_TIM1EN = (0),
	RCC_APB2ENR_TIM8EN = (1),
	RCC_APB2ENR_USART1EN = (4),
	RCC_APB2ENR_USART6EN = (5),
	RCC_APB2ENR_ADC1EN = (8),
	RCC_APB2ENR_ADC2EN = (9),
	RCC_APB2ENR_ADC3EN = (10),
	RCC_APB2ENR_SDIOEN = (11),
	RCC_APB2ENR_SPI1EN = (12),
	RCC_APB2ENR_SPI4EN = (13),
	RCC_APB2ENR_SYSCFGEN = (14),
	RCC_APB2ENR_TIM9EN = (16),
	RCC_APB2ENR_TIM10EN = (17),
	RCC_APB2ENR_TIM11EN = (18),

} PeripheralAPB2_t;

void RCC_AHB1EnableCLK(PeripheralAHB1_t peripheral);
void RCC_AHB1DisableCLK(PeripheralAHB1_t peripheral);

void RCC_APB1EnableCLK(PeripheralAPB1_t peripheral);
void RCC_APB1DisableCLK(PeripheralAPB1_t peripheral);

void RCC_APB2EnableCLK(PeripheralAPB2_t peripheral);
void RCC_APB2DisableCLK(PeripheralAPB2_t peripheral);


#endif
