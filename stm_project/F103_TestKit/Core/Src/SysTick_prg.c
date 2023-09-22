#include "SysTick_int.h"
#include "Utils.h"

STK_Callback_t Global_SysTickCallback;
Interval_t Global_Interval;

void SysTick_Handler(void)
{
	if (Global_Interval == Interval_Single)
	{
		//disable counter
		CLEAR_BIT(STK->STK_CTRL,sys_ENABLE);
	}
	if (Global_SysTickCallback != 0)
	{
		Global_SysTickCallback();
	}
}

void STK_vInit()
{
	/*1. CLK SRC*/
	CLEAR_BIT(STK->STK_CTRL,CLKSOURCE); // AHB/8 = 2 MHz

	/*2. interrupt sys_ENABLE  */
	SET_BIT(STK->STK_CTRL,TICKINT); // sys_ENABLE INT


}

void STK_vStartTimer(uint32_t copy_u32Ticks)
{
	// reset timer value to clear count flag
	STK->STK_VAL = 0 ;
	// load timer
	STK->STK_LOAD=copy_u32Ticks;
	//sys_ENABLE timer
	SET_BIT(STK->STK_CTRL,sys_ENABLE);
}
void STK_vStopTimer()
{
	// reset timer value to clear count flag
	STK->STK_VAL = 0 ;

	//disable counter
	CLEAR_BIT(STK->STK_CTRL,sys_ENABLE);
}


void STK_vSetBusyWait(uint32_t copy_u32Ticks)
{
	// reset timer value to clear count flag
	STK->STK_VAL = 0 ;
	// load timer
	STK->STK_LOAD=copy_u32Ticks;
	//sys_ENABLE timer
	SET_BIT(STK->STK_CTRL,sys_ENABLE);
	//Busy wait
	while(READ_BIT(STK->STK_CTRL,COUNTFLAG) != 1);
	// stop timer
	SET_BIT(STK->STK_CTRL,sys_ENABLE);

}
void STK_vSetIntervalSingle(uint32_t copy_u32Ticks,STK_Callback_t copy_pSTK_Callback)
{
	// callback
	Global_Interval=Interval_Single;
	Global_SysTickCallback=copy_pSTK_Callback;

	// reset timer value to clear count flag
	STK->STK_VAL = 0 ;

	// load timer
	STK->STK_LOAD=copy_u32Ticks;
	//sys_ENABLE timer
	SET_BIT(STK->STK_CTRL,sys_ENABLE);
}
void STK_vSetIntervalPeriodic(uint32_t copy_u32Ticks,STK_Callback_t copy_pSTK_Callback)
{

	// callback
	Global_Interval=Interval_Periodic;
	Global_SysTickCallback=copy_pSTK_Callback;

	// reset timer value to clear count flag
	STK->STK_VAL = 0 ;

	// load timer
	STK->STK_LOAD=copy_u32Ticks;
	//sys_ENABLE timer
	SET_BIT(STK->STK_CTRL,sys_ENABLE);

}

uint32_t STK_vGetElapsedTime()
{
	return ( STK->STK_LOAD - STK->STK_VAL) ;
}
uint32_t STK_vGetRemainingTime()
{
	return STK->STK_VAL ;
}
