
#include "STM32F446xx.h"
#include "EXTI_prv.h"
#include "EXTI_int.h"
#include "Utils.h"
#include "ErrType.h"


IntCallBack_t Globalarr_EXTICallBack [22];

void EXTI0_IRQHandler()
{
	if (Globalarr_EXTICallBack[0] != NULL)
	{
		Globalarr_EXTICallBack[0]();
	}
	EXTI_ClearPendingFlag(EXTI_INT0);
}
void EXTI1_IRQHandler()
{
	if (Globalarr_EXTICallBack[0] != NULL)
	{
		Globalarr_EXTICallBack[0]();
	}
	EXTI_ClearPendingFlag(EXTI_INT1);

}
void EXTI2_IRQHandler()
{
	if (Globalarr_EXTICallBack[0] != NULL)
	{
		Globalarr_EXTICallBack[0]();
	}
	EXTI_ClearPendingFlag(EXTI_INT2);

}
void EXTI3_IRQHandler()
{
	if (Globalarr_EXTICallBack[0] != NULL)
	{
		Globalarr_EXTICallBack[0]();
	}
}


void EXTI_Init(EXTI_EXTIConfig_t* copy_pfEXTI_EXTIConfig)
{
	uint8_t Local_u8ErrorState=OK;
	/* 1- CFG Rising - falling */
	switch(copy_pfEXTI_EXTIConfig->IntTriggerEdge)
	{
	case EXTI_Rising_edge:
		EXTI_SetRisingEdge(copy_pfEXTI_EXTIConfig->IntNumber);
		break;
	case EXTI_Falling_edge:
		EXTI_SetFallingEdge(copy_pfEXTI_EXTIConfig->IntNumber);
		break;
	case EXTI_Rising_Falling_edge:
		EXTI_SetRisingFallingEdge(copy_pfEXTI_EXTIConfig->IntNumber);
		break;
	default:
		Local_u8ErrorState=NOK;
		break;



	}
	/*set the interrupt port on line */
	EXTI_vSetEXTI_LineOnPort(copy_pfEXTI_EXTIConfig->IntNumber,copy_pfEXTI_EXTIConfig->IntPortLine);

	/* Interrupt State */
	switch(copy_pfEXTI_EXTIConfig->InterruptState)
	{
	case EXTI_Disabled:
		EXTI_DisableInterrupt(copy_pfEXTI_EXTIConfig->IntNumber);
		break;
	case EXTI_Enabled:
		EXTI_EnableInterrupt(copy_pfEXTI_EXTIConfig->IntNumber);
		break;
	}
	/* 2- Set callBack */
	EXTI_SetCallBack(copy_pfEXTI_EXTIConfig->IntNumber,copy_pfEXTI_EXTIConfig->IntCallBack);

	/* 3- Enable Interrupt */
	EXTI_EnableInterrupt(copy_pfEXTI_EXTIConfig->IntNumber);

}
void EXTI_EnableInterrupt(EXTI_Int_Type copy_eEXTI_Int)
{
	EXTI->EXTI_IMR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_IMR |=  (0b1<<copy_eEXTI_Int);

}
void EXTI_DisableInterrupt(EXTI_Int_Type copy_eEXTI_Int)
{
	EXTI->EXTI_IMR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_IMR |=  (0b0<<copy_eEXTI_Int);

}
void EXTI_SetRisingEdge(EXTI_Int_Type copy_eEXTI_Int)
{
	// set rising
	EXTI->EXTI_RTSR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_RTSR |=  (0b1<<copy_eEXTI_Int);
	// clear falling
	EXTI->EXTI_FTSR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_FTSR |=  (0b0<<copy_eEXTI_Int);
}
void EXTI_SetFallingEdge(EXTI_Int_Type copy_eEXTI_Int)
{
	// set falling
	EXTI->EXTI_FTSR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_FTSR |=  (0b1<<copy_eEXTI_Int);
	// clear rising
	EXTI->EXTI_RTSR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_RTSR |=  (0b0<<copy_eEXTI_Int);
}
void EXTI_SetRisingFallingEdge(EXTI_Int_Type copy_eEXTI_Int)
{
	// set falling
	EXTI->EXTI_FTSR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_FTSR |=  (0b1<<copy_eEXTI_Int);
	// set  rising
	EXTI->EXTI_RTSR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_RTSR |=  (0b1<<copy_eEXTI_Int);
}

void EXTI_SetSWPendingFlag(EXTI_Int_Type copy_eEXTI_Int)
{
	EXTI->EXTI_SWIER &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_SWIER |=  (0b1<<copy_eEXTI_Int);

}
void EXTI_ClearPendingFlag(EXTI_Int_Type copy_eEXTI_Int)
{
	EXTI->EXTI_PR &= ~(0b1<<copy_eEXTI_Int);
	EXTI->EXTI_PR |=  (0b1<<copy_eEXTI_Int);

}
void EXTI_ReadPendingFlag(EXTI_Int_Type copy_eEXTI_Int, uint8_t* copy_pu8Data)
{
	*copy_pu8Data=READ_BIT(EXTI->EXTI_PR,copy_eEXTI_Int);
}

void EXTI_SetCallBack(EXTI_Int_Type copy_eEXTI_Int,IntCallBack_t copy_pfCallBack)
{
	Globalarr_EXTICallBack[copy_eEXTI_Int]=copy_pfCallBack;
}
void EXTI_vSetEXTI_LineOnPort(EXTI_Int_Type copy_EXTI_Int,EXTI_EXTIPortCFG_t copy_eEXTI_EXTIPortCFG)
{
	SYSCFG->SYSCFG_EXTICR[copy_EXTI_Int/4] &= ~(0b1111 << ((copy_EXTI_Int % 4)*4));
	SYSCFG->SYSCFG_EXTICR[copy_EXTI_Int/4] &= ~(copy_eEXTI_EXTIPortCFG << ((copy_EXTI_Int % 4)*4));

}


