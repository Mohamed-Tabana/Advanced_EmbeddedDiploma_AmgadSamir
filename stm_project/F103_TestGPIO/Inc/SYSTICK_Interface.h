/*
 *@file		:	SYSTICK_INTERFACE.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main functions for SysTick peripheral
 */

#ifndef SYSTICK_INC_SYSTICK_INTERFACE_H_
#define SYSTICK_INC_SYSTICK_INTERFACE_H_

#include "SYSTICK_Private.h"
/*************************
 * @INT_STATE_t enum
 */
typedef enum {
	SYSTICK_INT_Disabled=0,SYSTICK_INT_Enabled
}INT_STATE_t;


/*************************
 * @SYSTICK_STATE_t enum
 */
typedef enum {
	SYSTICK_DISABLED=0,SYSTICK_ENABLED
}SYSTICK_STATE_t;


/*************************
 * @SYSTICK_CLOCK_t enum
 */
typedef enum {
	AHB_DIVIDEDBY8=0,AHB_DIRECT
}SYSTICK_CLOCK_t;

/*************************
 * @SYSTICK_Configs_t Structure
 */
typedef struct {
	INT_STATE_t		INT_State;
	SYSTICK_STATE_t	SYSTICK_State;
	SYSTICK_CLOCK_t	SYSTICK_Clock;
}SYSTICK_Configs_t;



/***********************************
 * @function 		:	SYSTICK_u8SetConfigs
 * @brief			:	Initialization for system tick
 * @parameter[in]	:	SysTick_Config
 * @retval			:	Error State
 */

uint8_t SYSTICK_u8SetConfigs( SYSTICK_Configs_t* SysTick_Config);


/***********************************
 * @function 		:	SYSTICK_u8Delay_ms
 * @brief			:	Delay Function in milliseconds
 * @parameter[in]	:	Time in milliseconds
 * @retval			:	Error State
 */

void	SYSTICK_u8Delay_ms	(uint32_t	Time_ms);

/***********************************
 * @function 		:	SYSTICK_u8Delay_us
 * @brief			:	Delay Function in microseconds
 * @parameter[in]	:	Time in microseconds
 * @retval			:	Error State
 */

void	SYSTICK_u8Delay_us	(uint32_t	Time_us);

#endif /* SYSTICK_INC_SYSTICK_INTERFACE_H_ */
