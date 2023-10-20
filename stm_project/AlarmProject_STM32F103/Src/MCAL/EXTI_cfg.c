
#include "EXTI_int.h"
#include "GPIO_int.h"
#include "SysTick_int.h"
extern PinConfig_t GPIO_BLUE_LED;
extern PinConfig_t GPIO_BUZZER;

void EXTI1_CallBack()
{
	GPIO_vSetOutputPinValue(GPIO_BLUE_LED.PIN_Port,GPIO_BLUE_LED.PIN_Number,OUTPUT_HIGH);
	GPIO_vSetOutputPinValue(GPIO_BUZZER.PIN_Port,GPIO_BUZZER.PIN_Number,OUTPUT_HIGH);

	//	STK_Delay_s(4);
//	GPIO_vSetOutputPinValue(GPIO_BLUE_LED.PIN_Port,GPIO_BLUE_LED.PIN_Number,OUTPUT_LOW);


}
EXTI_EXTIConfig_t ourEXTI=
{
		.IntNumber=EXTI_INT0,
		.IntPortLine=EXTI_PORTA,
		.IntTriggerEdge=EXTI_Falling_edge,
		.IntCallBack=EXTI1_CallBack,
		.InterruptState=EXTI_Enabled,

};
