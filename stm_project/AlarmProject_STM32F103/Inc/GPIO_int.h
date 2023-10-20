#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "GPIO_prv.h"
#include "stdio.h"

typedef enum {
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
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
	Analog_mode = 0,     
	Floating_input ,        
	Input_with_pull_up_pull_down,     
	Reserved,        
}GPIO_InputPinType_t;

typedef enum {
	General_purpose_output_push_pull = 0,     
	General_purpose_output_Open_drain ,        
	Alternate_function_output_Push_pull,     
	Alternate_function_output_Open_drain,        
}GPIO_OutputPinType_t;

typedef enum {
	INPUT = 0,     // Input mode
	Output_mode_max_speed_10_MHz,    
	Output_mode_max_speed_2_MHz,     
	Output_mode_max_speed_50_MHz,    
}GPIO_PinMode_t;

typedef enum {
	INPUT_LOW = 0, // Input low
	INPUT_HIGH,    // Input high
} GPIO_IDR_t;
/*
 * @GPIO_ODR_t ENUM
 */
typedef enum {
	OUTPUT_LOW = 0, // Output low
	OUTPUT_HIGH,    // Output high
} GPIO_ODR_t;

typedef enum {
	RESET,
	SET ,        // Set bit
	// Reset bit
} GPIO_BS_t;

typedef enum {
	UNLOCKED = 0,   // GPIO port can be modified
	LOCKED,         // GPIO port is locked until next reset
} GPIO_LCK_t;







typedef enum {
	AF0 = 0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15,
} GPIO_AF_t;




typedef struct
{
	GPIO_Port_t PIN_Port;
	GPIO_Pin_t PIN_Number;
	GPIO_PinMode_t PIN_Mode;
	GPIO_InputPinType_t PIN_InputType;
	GPIO_OutputPinType_t PIN_OutputType;
	GPIO_ODR_t PIN_OValue;
	GPIO_LCK_t PIN_LCKSTS;

} PinConfig_t;

uint8_t GPIO_u8PinInit(const PinConfig_t* copy_ePinConfig);
uint8_t GPIO_vSetPinMode(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_PinMode_t copy_eGPIO_PinMode);
uint8_t GPIO_vSetOutputPinType(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_OutputPinType_t copy_GPIO_OutputPinType);
uint8_t GPIO_vSetInputPinType(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_InputPinType_t copy_GPIO_InputPinType);
uint8_t GPIO_vSetOutputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t copy_GPIO_ODR);
uint8_t GPIO_vSetOutputPinValueBSR(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_BS_t copy_GPIO_BS);
uint8_t GPIO_vToggleOutputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin);
uint8_t GPIO_vReadInputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t* copy_GPIO_ODR );


#endif 
