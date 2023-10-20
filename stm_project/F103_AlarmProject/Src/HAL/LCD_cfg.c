/*
 * LCD_cfg.c
 *
 *  Created on: Sep 28, 2023
 *      Author: ALTAWKEL
 */

#include "GPIO_int.h"

PinConfig_t LCD_RS=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN11,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_InputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};
PinConfig_t LCD_EN=
{
		.PIN_Port=PORTA,
		.PIN_Number=PIN8,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_InputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};

PinConfig_t LCD_D4=
{
		.PIN_Port=PORTB,
		.PIN_Number=PIN15,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_InputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};

PinConfig_t LCD_D5=
{
		.PIN_Port=PORTB,
		.PIN_Number=PIN14,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_InputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};

PinConfig_t LCD_D6=
{
		.PIN_Port=PORTB,
		.PIN_Number=PIN13,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_InputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};

PinConfig_t LCD_D7=
{
		.PIN_Port=PORTB,
		.PIN_Number=PIN12,
		.PIN_Mode=Output_mode_max_speed_50_MHz,
		.PIN_InputType=General_purpose_output_push_pull,
		.PIN_LCKSTS=UNLOCKED,
};


