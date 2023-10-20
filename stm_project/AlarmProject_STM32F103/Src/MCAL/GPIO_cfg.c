/*
 * GPIO_cfg.c
 *
 *  Created on: Sep 28, 2023
 *      Author: ALTAWKEL
 */


#include "GPIO_int.h"

PinConfig_t GPIO_RED_LED=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN1,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_OutputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};
PinConfig_t GPIO_GREEN_LED=
{
		.PIN_Port=PORTC,
		.PIN_Number=PIN15,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_OutputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};
PinConfig_t GPIO_BLUE_LED=
{
		.PIN_Port=PORTC,
		.PIN_Number=PIN14,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_OutputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};
PinConfig_t GPIO_BUZZER=
{
		.PIN_Port=PORTB,
		.PIN_Number=PIN4,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_OValue=OUTPUT_LOW,
		.PIN_OutputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};

