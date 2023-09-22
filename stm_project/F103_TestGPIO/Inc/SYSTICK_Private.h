/*
 *@file		:	SYSTICK_Private.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Private Defines for SysTick peripheral
 */


#ifndef SYSTICK_INC_SYSTICK_PRIVATE_H_
#define SYSTICK_INC_SYSTICK_PRIVATE_H_

#define 	ENABLE_MASK				0b1
#define 	ENABLE_BIT_ACCESS		0

#define 	INTERRUPT_MASK			0b1
#define 	INTERRUPT_BIT_ACCESS	1u

#define		CLKSRC_MASK				0b1
#define 	CLKSRC_BIT_ACCESS		2u

#define 	TICK_TIME				0.125

#define 	COUNTFLAG				16u


#endif /* SYSTICK_INC_SYSTICK_PRIVATE_H_ */
