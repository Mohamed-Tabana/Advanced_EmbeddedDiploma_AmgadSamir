/**
 ******************************************************************************
 * @file           GPIO_prg.c
 * @author         Mohamed TABANA
 * @brief          the GPIO main source file, including functions definitions
 ******************************************************************************
 */
#include <stdint.h>
#include "STM32f446xx.h"
#include "ErrType.h"
#include "Utils.h"
#include "stdio.h"

#include "GPIO_int.h"
#include "GPIO_prv.h"

static GPIO_RegDef_t* GPIO_PORT [GPIO_PERIPHERAL_NUM] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG, GPIOH} ;

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
			/* Select GPIO Mode: INPUT - OUTPUT - ANALOG - AF */
			GPIO_PORT[copy_ePinConfig->PIN_Port]->MODER &= ~(MODER_MASK				     << (copy_ePinConfig->PIN_Number * MODER_PIN_ACCESS)); // clear mode bits
			GPIO_PORT[copy_ePinConfig->PIN_Port]->MODER |=  ((copy_ePinConfig->PIN_Type) << (copy_ePinConfig->PIN_Number * MODER_PIN_ACCESS));
			/* Select GPIO pull state: PULLUP - PULLDOWN - NOPULL */
			GPIO_PORT[copy_ePinConfig->PIN_Port]->PUPDR &= ~(PUPDR_MASK				    	    << (copy_ePinConfig->PIN_Number * PUPDR_PIN_ACCESS)); // clear mode bits
			GPIO_PORT[copy_ePinConfig->PIN_Port]->PUPDR |=  ((copy_ePinConfig->PIN_PullUpDown)  << (copy_ePinConfig->PIN_Number * PUPDR_PIN_ACCESS));
			/* Select output type and speed in case of OUTPUT / AF  */
			if ((copy_ePinConfig->PIN_Type == OUTPUT) || (copy_ePinConfig->PIN_Type == ALTERNATE))
			{
				/* select output type PUSHPULL - OPEN DRAIN */
				GPIO_PORT[copy_ePinConfig->PIN_Port]->OTYPER &= ~(OTYPER_MASK				 << (copy_ePinConfig->PIN_Number)); // clear mode bits
				GPIO_PORT[copy_ePinConfig->PIN_Port]->OTYPER |=  (copy_ePinConfig->PIN_OType << (copy_ePinConfig->PIN_Number));
				/* select speed type LOW_SPEED - MEDIUM_SPEED - FAST_SPEED - HIGH_SPEED */
				GPIO_PORT[copy_ePinConfig->PIN_Port]->OSPEEDR &= ~(OSPEEDR_MASK				   << (copy_ePinConfig->PIN_Number * OSPEEDR_PIN_ACCESS)); // clear mode bits
				GPIO_PORT[copy_ePinConfig->PIN_Port]->OSPEEDR |=  (copy_ePinConfig->PIN_OSpeed << (copy_ePinConfig->PIN_Number * OSPEEDR_PIN_ACCESS));
				/* o/p value */
				GPIO_vSetOutputPinValue(copy_ePinConfig->PIN_Port,copy_ePinConfig->PIN_Number,copy_ePinConfig->PIN_OValue);

				/* select AF PIN */
				if ((copy_ePinConfig->PIN_Type == ALTERNATE))
				{
					uint8_t Local_u8RegNum = copy_ePinConfig->PIN_Number / 8U;
					uint8_t Local_u8BitNum = copy_ePinConfig->PIN_Number % 8U;

					GPIO_PORT[copy_ePinConfig->PIN_Port]->AFR[Local_u8RegNum] &= ~(AFR_MASK			  << ( Local_u8BitNum*AFR_PIN_ACCESS)); // clear mode bits
					GPIO_PORT[copy_ePinConfig->PIN_Port]->AFR[Local_u8RegNum] |=  (copy_ePinConfig->PIN_AF  << ( Local_u8BitNum*AFR_PIN_ACCESS));
				}
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

uint8_t GPIO_vSetOutputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t copy_GPIO_ODR)
{
	uint8_t Local_u8ErrorState = OK ;
	if ((copy_eGPIO_Port < INVALID) && (copy_eGPIO_Pin <= PIN15))
	{
		if (copy_GPIO_ODR == OUTPUT_LOW || copy_GPIO_ODR == OUTPUT_HIGH)
		{
			GPIO_PORT[copy_eGPIO_Port]->ODR &= ~(ODR_MASK			 << (copy_eGPIO_Pin)); // clear mode bits
			GPIO_PORT[copy_eGPIO_Port]->ODR |=  (copy_GPIO_ODR 	 	 << (copy_eGPIO_Pin));
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
uint8_t MGPIO_vReadInputPinValue(GPIO_Port_t copy_eGPIO_Port,GPIO_Pin_t copy_eGPIO_Pin,GPIO_ODR_t* copy_GPIO_ODR )
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

