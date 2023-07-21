#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#include "EXTI_prv.h"
#include "stdint.h"
#include "STM32F446xx.h"

void EXTI_Init(EXTI_EXTIConfig_t* copy_pfEXTI_EXTIConfig);
void EXTI_EnableInterrupt(EXTI_Int_Type copy_eEXTI_Int);
void EXTI_DisableInterrupt(EXTI_Int_Type copy_eEXTI_Int);
void EXTI_SetSWPendingFlag(EXTI_Int_Type copy_eEXTI_Int);
void EXTI_ClearPendingFlag(EXTI_Int_Type copy_eEXTI_Int);
void EXTI_ReadPendingFlag(EXTI_Int_Type copy_eEXTI_Int, uint8_t* copy_pu8Data);
void EXTI_SetRisingEdge(EXTI_Int_Type copy_eEXTI_Int);
void EXTI_SetFallingEdge(EXTI_Int_Type copy_eEXTI_Int);
void EXTI_SetRisingFallingEdge(EXTI_Int_Type copy_eEXTI_Int);
void EXTI_SetCallBack(EXTI_Int_Type copy_eEXTI_Int,IntCallBack_t copy_pfCallBack);
void EXTI_vSetEXTI_LineOnPort(EXTI_Int_Type copy_EXTI_Int,EXTI_EXTIPortCFG_t copy_eEXTI_EXTIPortCFG);






#endif
