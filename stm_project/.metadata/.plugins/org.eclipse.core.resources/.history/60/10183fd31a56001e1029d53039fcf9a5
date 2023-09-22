/*
 *@file		:	GPIO_INTERFACE.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main functions for GPIO peripheral
 */


#ifndef MCAL_GPIO_INC_GPIO_INTERFACE_H_
#define MCAL_GPIO_INC_GPIO_INTERFACE_H_

#include "GPIO_Private.h"
#include "../../LIBRARY/STM32F103xx.h"


typedef enum {
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
}Port_t;

typedef enum {
	PIN0=0,
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
}Pin_t;

typedef enum {
	INPUT=0,OUTPUT_MSPEED,OUTPUT_LSPEED,OUTPUT_HSPEED
}Mode_t;

typedef enum {
	ANALOG_INPUT=0,FLOATING_INPUT,PULLUPDOWN_INPUT
}InputType_t;

typedef enum {
	GP_PUSH_PULL=0,GP_OPEN_DRAIN,AF_PUSHPULL,AF_OPEN_DRAIN
}OutputType_t;


typedef enum {
	PULLDOWN,PULLUP
}PullUp_PullDown_t;

/*typedef enum {
	AF0=0,
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
	AF15
}AlternateFunction_t;
*/
typedef enum
{
	LOW_V=0,HIGH_V
}PinVal_t;
typedef struct {
	Port_t Port_Num;
	Pin_t Pin_Num;
	Mode_t Mode;
	OutputType_t Output_Type;
	InputType_t Input_Type;
	PullUp_PullDown_t PullType;
	//AlternateFunction_t AltFunc;
}PinConfig_t;

/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : GPIO_u8PinInit()
 *     FUNCTIONALITY : Initialize the selected pin
 *     ARGUMENT 	 : Pointer to structure PinConfig_t * Pin_Config
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t GPIO_u8PinInit(PinConfig_t * Pin_Config);



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : GPIO_u8SetPinStatus()
 *     FUNCTIONALITY : Set the selected PIN state
 *     ARGUMENT 	 : PORT - PIN - Value
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t GPIO_u8SetPinStatus(Port_t Port,Pin_t Pin,PinVal_t State );


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : GPIO_u8ReadPinStatus()
 *     FUNCTIONALITY : READ the selected PIN state
 *     ARGUMENT 	 : Port - PIN - Variable address to save the state
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t GPIO_u8ReadPinStatus(Port_t Port,Pin_t Pin, PinVal_t * State );


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : GPIO_u8TogglePinStatus()
 *     FUNCTIONALITY : Toggle the selected PIN state
 *     ARGUMENT 	 : Port - PIN
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t GPIO_u8TogglePinStatus(Port_t Port,Pin_t Pin);




#endif /* MCAL_GPIO_INC_GPIO_INTERFACE_H_ */
