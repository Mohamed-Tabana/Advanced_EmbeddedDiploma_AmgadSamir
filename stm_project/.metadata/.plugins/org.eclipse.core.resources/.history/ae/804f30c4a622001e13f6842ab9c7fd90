#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include "NVIC_prv.h"
#include "stdint.h"
#include "STM32F446xx.h"



void NVIC_vEnableInterrupt(Interrupt_t copy_eInterrupt);
void NVIC_vDisableInterrupt(Interrupt_t copy_eInterrupt);
void NVIC_vSetPendingFlag(Interrupt_t copy_eInterrupt);
void NVIC_vClearPendingFlag(Interrupt_t copy_eInterrupt);
void NVIC_vGetActiveFlag(Interrupt_t copy_eInterrupt, uint8_t *copy_u8flagStatus);

void NVIC_vSetPriorityCfg(NVIC_GroupPriorityCfg copy_eGroupPriorityCfg);
void NVIC_vSetInterruptPriority(Interrupt_t copy_eInterrupt,uint8_t copy_u8Priority);



#endif
