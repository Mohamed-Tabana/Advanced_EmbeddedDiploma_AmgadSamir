#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

#include "stdint.h"
#include "SysTick_prv.h"
#include "STM32F103.h"

/*
*Interval_t ENUM
*/
typedef enum
{
	Interval_Single,
	Interval_Periodic
}Interval_t;

typedef void (*STK_Callback_t)(void);


void STK_vInit();
void STK_vStartTimer(uint32_t copy_u32Ticks);
void STK_vStopTimer();
void STK_vSetBusyWait(uint32_t copy_u32Ticks);
void STK_vSetIntervalSingle(uint32_t copy_u32Ticks,STK_Callback_t copy_pSTK_Callback);
void STK_vSetIntervalPeriodic(uint32_t copy_u32Ticks,STK_Callback_t copy_pSTK_Callback);
void STK_vSetCallBack(STK_Callback_t copy_pSTK_Callback);
uint32_t STK_vGetElapsedTime();
uint32_t STK_vGetRemainingTime();
void STK_Delay_ms(uint32_t copy_u32timeMS);
void STK_Delay_s(uint32_t copy_u32timeS);


#endif
