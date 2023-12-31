#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/*
 * @GPIO_Port_t ENUM
 */
typedef enum {
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH,
	INVALID

}GPIO_Port_t;
/*
 *  @GPIO_Pin_t ENUM
 */
typedef enum {
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
}GPIO_Pin_t;

typedef enum {
	INPUT = 0,     // Input mode
	OUTPUT,        // General purpose output mode
	ALTERNATE,     // Alternate function mode
	ANALOG,        // Analog mode
}GPIO_PinType_t;

typedef enum {
	LOW_SPEED = 0,  // Low speed
	MEDIUM_SPEED,   // Medium speed
	FAST_SPEED,     // High speed
	HIGH_SPEED,// Very high speed
} GPIO_OSpeed_t;

typedef enum {
	PUSH_PULL = 0,  // Output push-pull
	OPEN_DRAIN,     // Output open-drain
} GPIO_OType_t;

typedef enum {
	AF0 = 0, // (system)
	AF1,	 //(TIM1/TIM2)
	AF2,     //(TIM3..5)
	AF3,     //(TIM8..11, CEC)
	AF4,     //(I2C1..4, CEC)
	AF5,     //(SPI1/2/3/4)
	AF6,     //(SPI2/3/4, SAI1)
	AF7,     //(SPI2/3, USART1..3, UART5, SPDIF-IN)
	AF8,     //(SPI2/3, USART1..3, UART5, SPDIF-IN)
	AF9,     //(CAN1/2, TIM12..14, QUADSPI)
	AF10,    //(SAI2, QUADSPI, OTG_HS, OTG_FS)
	AF11,    //
	AF12,    //(FMC, SDIO, OTG_HS(1))
	AF13,    //(DCMI)
	AF14,    //
	AF15,    //(EVENTOUT)
} GPIO_AF_t;
typedef enum {
	NO_PULL = 0,    // No pull-up, no pull-down
	PULL_UP,        // Pull-up
	PULL_DOWN,      // Pull-down
} GPIO_PUPD_t;
/*
 * @GPIO_ODR_t ENUM
 */
typedef enum {
	OUTPUT_LOW = 0, // Output low
	OUTPUT_HIGH,    // Output high
} GPIO_ODR_t;
typedef enum {
	UNLOCKED = 0,   // GPIO port can be modified
	LOCKED,         // GPIO port is locked until next reset
} GPIO_LCK_t;
typedef enum {
	RESET,
	SET ,        // Set bit
	// Reset bit
} GPIO_BS_t;
typedef struct
{
	GPIO_Port_t PIN_Port;
	GPIO_Pin_t PIN_Number;
	GPIO_PinType_t PIN_Type;
	GPIO_ODR_t PIN_OValue;
	GPIO_OType_t PIN_OType;
	GPIO_OSpeed_t PIN_OSpeed;
	GPIO_PUPD_t PIN_PullUpDown;
	GPIO_LCK_t PIN_LCKSTS;
	GPIO_AF_t PIN_AF;

} PinConfig_t;

uint8_t GPIO_u8PinInit(const PinConfig_t* copy_ePinConfig);
uint8_t GPIO_vSetOutputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t copy_GPIO_ODR);
uint8_t GPIO_vToggleOutputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin);
uint8_t MGPIO_vReadInputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t* copy_GPIO_ODR );

uint8_t GPIO_vSetPinType(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_PinType_t copy_eGPIO_PinType);


uint8_t GPIO_vSetOutputPinType(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_OType_t copy_GPIO_OType);
uint8_t GPIO_vSetOutputPinSpeed(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_OSpeed_t copy_GPIO_OSpeed);
uint8_t GPIO_vSetOutputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t copy_GPIO_ODR);
uint8_t GPIO_vSetOutputPinValueBSR(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_BS_t copy_GPIO_BS);
uint8_t GPIO_vSetOutputPortValue(GPIO_Port_t copy_eGPIO_Port,uint8_t copy_u8number);



#endif 
