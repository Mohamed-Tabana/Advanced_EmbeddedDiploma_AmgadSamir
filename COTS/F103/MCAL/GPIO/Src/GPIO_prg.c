/**
 ******************************************************************************
 * @file           GPIO_prg.c
 * @author         Mohamed TABANA
 * @brief          the GPIO main source file, including functions definitions
 ******************************************************************************
 */
#include <stdint.h>
#include "STM32F103.h"
#include "ErrType.h"
#include "Utils.h"
#include "stdio.h"

#include "GPIO_int.h"
#include "GPIO_prv.h"

static GPIO_RegDef_t* GPIO_PORT [GPIO_PERIPHERAL_NUM] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG} ;

/**********************************************************************************
 * @fn GPIO_u8PinInit
 * @brief the function initializes the GPIO pin according to the input parameters
 * @param[in] copy_ePinConfig : the initialization values of the pin
 * @retval ErrorStatus
 *
 */
uint8_t GPIO_u8PinInit(const PinConfig_t* copy_ePinConfig)
{
	uint8_t Local_u8ErrorState = OK ;
	if (copy_ePinConfig != NULL)
	{
		if ((copy_ePinConfig->PIN_Port < INVALID) && (copy_ePinConfig->PIN_Number <= PIN15))
		{
			/* Select GPIO Mode: INPUT - OUTPUT 10 MHz- OUTPUT 2 MHz - OUTPUT 50 MHz */
			GPIO_PORT[copy_ePinConfig->PIN_Port]->CR[copy_ePinConfig->PIN_Number /MODEMOD_MASK] &= ~(MODE_MASK                   << ((copy_ePinConfig->PIN_Number %MODEMOD_MASK) *MODE_PIN_ACCESS)); // clear mode bits
			GPIO_PORT[copy_ePinConfig->PIN_Port]->CR[copy_ePinConfig->PIN_Number /MODEMOD_MASK] |=  ((copy_ePinConfig->PIN_Mode) << ((copy_ePinConfig->PIN_Number %MODEMOD_MASK) *MODE_PIN_ACCESS));
			
			/* Select output type and speed in case of OUTPUT / AF  */
			if ((copy_ePinConfig->PIN_Mode == Output_mode_max_speed_10_MHz) ||
				(copy_ePinConfig->PIN_Mode == Output_mode_max_speed_2_MHz ) ||
				(copy_ePinConfig->PIN_Mode == Output_mode_max_speed_50_MHz)
				 )
			{
				/* select output type General_purpose_output_push_pull - General_purpose_output_Open_drain - Alternate_function_output_Push_pull - Alternate_function_output_Open_drain */
				GPIO_PORT[copy_ePinConfig->PIN_Port]->CR[copy_ePinConfig->PIN_Number /MODEMOD_MASK]  &= ~(CNF_MASK				          <<(((copy_ePinConfig->PIN_Number %CNFMOD_MASK) *MODE_PIN_ACCESS) +MODE_PIN_ACCESS_Addition) ); // clear mode bits
				GPIO_PORT[copy_ePinConfig->PIN_Port]->CR[copy_ePinConfig->PIN_Number /MODEMOD_MASK]  |=  (copy_ePinConfig->PIN_OutputType <<(((copy_ePinConfig->PIN_Number %CNFMOD_MASK) *MODE_PIN_ACCESS) +MODE_PIN_ACCESS_Addition) );
				
				GPIO_PORT[copy_ePinConfig->PIN_Port]->ODR  &= ~(0b1				            <<copy_ePinConfig->PIN_Number ); // clear mode bits
				GPIO_PORT[copy_ePinConfig->PIN_Port]->ODR  |=  (copy_ePinConfig->PIN_OValue	<<copy_ePinConfig->PIN_Number );

				
				
			}
				/* select input type : Analog mode - Floating input - Input with pull-up / pull-down - Reserved */

			else if (copy_ePinConfig->PIN_Mode == INPUT)
			{
				GPIO_PORT[copy_ePinConfig->PIN_Port]->CR[copy_ePinConfig->PIN_Number /MODEMOD_MASK]  &= ~(CNF_MASK				         <<(((copy_ePinConfig->PIN_Number %CNFMOD_MASK) *MODE_PIN_ACCESS) +MODE_PIN_ACCESS_Addition) ); // clear mode bits
				GPIO_PORT[copy_ePinConfig->PIN_Port]->CR[copy_ePinConfig->PIN_Number /MODEMOD_MASK]  |=  (copy_ePinConfig->PIN_InputType <<(((copy_ePinConfig->PIN_Number %CNFMOD_MASK) *MODE_PIN_ACCESS) +MODE_PIN_ACCESS_Addition) );

			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
/**********************************************************************************
 * @fn GPIO_vSetOutputPinValue
 * @brief the function outputs value on pin
 * @param[in] copy_eGPIO_Port : the port number, get options @GPIO_Port_t ENUM
 * @param[in] copy_eGPIO_Pin : the pin number, get options @GPIO_Pin_t ENUM
 * @param[in] copy_GPIO_ODR : the pin number, get options @GPIO_ODR_t ENUM
 * @retval ErrorStatus
 *
 */

uint8_t GPIO_vSetOutputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t copy_eGPIO_ODR)
{
	uint8_t Local_u8ErrorState = OK ;
	if ((copy_eGPIO_Port < INVALID) && (copy_eGPIO_Pin <= PIN15))
	{
		if (copy_eGPIO_ODR == OUTPUT_LOW || copy_eGPIO_ODR == OUTPUT_HIGH)
		{
			GPIO_PORT[copy_eGPIO_Port]->ODR &= ~(ODR_MASK			 << (copy_eGPIO_Pin)); // clear mode bits
			GPIO_PORT[copy_eGPIO_Port]->ODR |=  (copy_eGPIO_ODR 	 	 << (copy_eGPIO_Pin));
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}

/**********************************************************************************
 * @fn GPIO_vToggleOutputPinValue
 * @brief the function toggles value on pin
 * @param[in] copy_eGPIO_Port : the port number, get options @GPIO_Port_t ENUM
 * @param[in] copy_eGPIO_Pin : the pin number, get options @GPIO_Pin_t ENUM
 * @retval ErrorStatus
 *
 */

uint8_t GPIO_vToggleOutputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin)
{
	uint8_t Local_u8ErrorState = OK ;
	if ((copy_eGPIO_Port < INVALID) && (copy_eGPIO_Pin <= PIN15))
	{

		TOGGLE_BIT(GPIO_PORT[copy_eGPIO_Port]->ODR ,copy_eGPIO_Pin);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}
/**********************************************************************************
 * @fn MGPIO_vReadInputPinValue
 * @brief the function reads value from pin
 * @param[in] copy_eGPIO_Port : the port number, get options @GPIO_Port_t ENUM
 * @param[in] copy_eGPIO_Pin : the pin number, get options @GPIO_Pin_t ENUM
 * @param[out] copy_GPIO_ODR : the pin value, get options @GPIO_ODR_t ENUM
 * @retval ErrorStatus
 *
 */
uint8_t GPIO_vReadInputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t* copy_GPIO_ODR )
{
	uint8_t Local_u8ErrorState = OK ;
	if ((copy_eGPIO_Port < INVALID) && (copy_eGPIO_Pin <= PIN15))
	{
		*copy_GPIO_ODR =READ_BIT(GPIO_PORT[copy_eGPIO_Port]->ODR ,copy_eGPIO_Pin);;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}

