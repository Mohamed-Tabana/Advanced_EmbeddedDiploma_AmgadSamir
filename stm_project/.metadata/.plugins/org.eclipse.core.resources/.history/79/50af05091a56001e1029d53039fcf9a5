/*
 *@file		:	SYSTICK_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program for SysTick peripheral
 */

#include <stdint.h>
#include "../Inc/SYSTICK_Interface.h"
#include "../../LIBRARY/ErrTypes.h"
#include "../../LIBRARY/STM32F103xx.h"

/***********************************
 * @function 		:	SYSTICK_u8SetConfigs
 * @brief			:	Initialization for system tick
 * @parameter[in]	:	SysTick_Config
 * @retval			:	Error State
 */

uint8_t SYSTICK_u8SetConfigs( SYSTICK_Configs_t* SysTick_Config)
{
	uint8_t Local_u8ErrorState = OK;

	if(SysTick_Config != NULL)
	{
		/*Set SYSTICK State*/
		SYSTICK ->CTRL	&=	~	(ENABLE_MASK)<<(ENABLE_BIT_ACCESS)	;
		SYSTICK ->CTRL	|=		((SysTick_Config->SYSTICK_State)<<(ENABLE_BIT_ACCESS));

		if((SysTick_Config->SYSTICK_State)==SYSTICK_ENABLED)
		{
			/*Set Interrupt Request State*/
			SYSTICK ->CTRL	&=	~	((INTERRUPT_MASK)<<(INTERRUPT_BIT_ACCESS))	;
			SYSTICK ->CTRL	|=		((SysTick_Config->INT_State)<<(INTERRUPT_BIT_ACCESS));
			/*Set System tick Clock Source*/
			SYSTICK ->CTRL	&=	~	((CLKSRC_MASK)<<(CLKSRC_BIT_ACCESS))	;
			SYSTICK ->CTRL	|=		((SysTick_Config->SYSTICK_Clock)<<(CLKSRC_BIT_ACCESS));
		}
	}
	else {
		Local_u8ErrorState = Null_Pointer;
	}

	return Local_u8ErrorState;
}



/***********************************
 * @function 		:	SYSTICK_u8Delay_ms
 * @brief			:	Delay Function in milliseconds
 * @parameter[in]	:	Time in milliseconds
 * @retval			:	Error State
 * @attention		:	the SysTick	Frequency must be 16 MHz
 * 						to make sure this function work properly
 */
void	SYSTICK_u8Delay_ms	(uint32_t	Time_ms)
{
	uint32_t	RELOAD_VALUE	=0;
	/*Calculate Reload Value*/

	RELOAD_VALUE	=	(Time_ms*1000)/TICK_TIME;
	/*Set reload value in the Reload Value Register*/
	SYSTICK->CTRL |= (1<<2);

	SYSTICK->LOAD	=	RELOAD_VALUE;

	SYSTICK->VAL = 0 ;

	SYSTICK->CTRL	|=	(1<<0);

	/*POOLING UNTIL FLOW REACHED (Delay end)*/
	while (!((SYSTICK->CTRL>>COUNTFLAG)&1))
	{
		//if( !( SYSTICK->CTRL&1 ) )
		//{
		//	SYSTICK->CTRL	|=	(1<<0);

		//}
	}

	SYSTICK->CTRL	&=	~(1<<0);

}




/***********************************
 * @function 		:	SYSTICK_u8Delay_us
 * @brief			:	Delay Function in microseconds
 * @parameter[in]	:	Time in microseconds
 * @retval			:	Error State
 * @attention		:	the SysTick	Frequency must be 16 MHz
 * 						to make sure this function work properly
 */
void	SYSTICK_u8Delay_us	(uint32_t	Time_us)
{
	uint32_t	RELOAD_VALUE	=	0	;
	/*Calculate Reload Value*/
	RELOAD_VALUE	=	(Time_us)/TICK_TIME;
	/*Set reload value in the Reload Value Register*/
	SYSTICK->LOAD	=	RELOAD_VALUE;
	/*POOLING UNTIL FLOW REACHED (Delay end)*/
	while (!((SYSTICK->CTRL>>COUNTFLAG)&1));
}
