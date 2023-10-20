
#include "STM32F103.h"
#include "NVIC_prv.h"
#include "NVIC_int.h"

#include "Utils.h"

void NVIC_vEnableInterrupt(Interrupt_t copy_eInterrupt)
{
	NVIC->NVIC_ISER[copy_eInterrupt/32]=  (0b1 <<(copy_eInterrupt % 32));
}
void NVIC_vDisableInterrupt(Interrupt_t copy_eInterrupt)
{
	NVIC->NVIC_ICER[copy_eInterrupt/32]= 0b1 << copy_eInterrupt % 32 ;
}
void NVIC_vSetPendingFlag(Interrupt_t copy_eInterrupt)
{
	NVIC->NVIC_ISPR[copy_eInterrupt/32]=  (0b1 << (copy_eInterrupt % 32)) ;
}
void NVIC_vClearPendingFlag(Interrupt_t copy_eInterrupt)
{
	NVIC->NVIC_ICPR[copy_eInterrupt/32]= 0b1 << (copy_eInterrupt % 32) ;

}
void NVIC_vGetActiveFlag(Interrupt_t copy_eInterrupt, uint8_t *copy_u8flagStatus)
{
	*copy_u8flagStatus = READ_BIT( NVIC->NVIC_IABR[copy_eInterrupt/32],  copy_eInterrupt % 32 );
}

void NVIC_vSetPriorityCfg(NVIC_GroupPriorityCfg copy_eGroupPriorityCfg)
{
	SCB->SCB_AIRCR= VECTKEY<<16 | copy_eGroupPriorityCfg << 8;
}
void NVIC_vSetInterruptPriority(Interrupt_t copy_eInterrupt,uint8_t copy_u8Priority)
{
	if (copy_eInterrupt<0)
	{
		SCB->SCB_SHPR[copy_eInterrupt+12]=copy_u8Priority<<4;
	}
	else if (copy_eInterrupt>=0)
	{
		NVIC->NVIC_IPR[copy_eInterrupt] = copy_u8Priority << 4;
	}
}
