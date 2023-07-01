/*
 * RCC_prg.c
 *
 *  Created on: Apr 17, 2023
 *      Author: ALTAWKEL
 */
#include "RCC_Interface.h"
void RCC_SetCLKSTS(CLKtype_t copy_tCLKtype, CLKStatus_t copy_tCLKStatus)
{
	switch(copy_tCLKtype)
	{
	case HSI_clock :
		if (copy_tCLKStatus==CLK_OFF)
		{
			CLEAR_BIT(RCC->CR,HSION);
		}
		else if (copy_tCLKStatus==CLK_ON)
		{
			SET_BIT(RCC->CR,HSION);
			while(READ_BIT(RCC->CR,HSIRDY));
		}
		break;
	case HSE_clock:
		if (copy_tCLKStatus==CLK_OFF)
		{
			CLEAR_BIT(RCC->CR,HSEON);
		}
		else if (copy_tCLKStatus==CLK_ON)
		{
			SET_BIT(RCC->CR,HSEON);
			while(READ_BIT(RCC->CR,HSERDY));
		}
		break;
	case PLL_clock:
		if (copy_tCLKStatus==CLK_OFF)
		{
			CLEAR_BIT(RCC->CR,PLLON);
		}
		else if (copy_tCLKStatus==CLK_ON)
		{
			SET_BIT(RCC->CR,PLLON);
			while(READ_BIT(RCC->CR,PLLRDY));
		}
		break;
	}
}

void RCC_SetSYSCLK(CLKtype_t copy_tCLKtype)
{
	RCC->CFGR &= ~(0b11<<SW0);
	RCC->CFGR |= (copy_tCLKtype<<SW0);
}

void RCC_HSECONFIG(HSEDIV_t copy_tHSEDIV)
{
	switch(copy_tHSEDIV)
	{
	case HSE_clock_not_divided:
		CLEAR_BIT(RCC->CFGR,PLLXTPRE);
		break;
	case HSE_clock_divided_by_2:
		SET_BIT(RCC->CFGR,PLLXTPRE);
		break;
	}
}
void RCC_PLLCONFIG(PLLMUL_t copy_tPLLMUX,CLKtype_t copy_tCLKtype)
{
	RCC->CFGR &= ~(0b1111<<PLLMUL0);
	RCC->CFGR |= (copy_tCLKtype<<PLLMUL0);
	switch(copy_tCLKtype)
	{
	case HSI_clock:
		CLEAR_BIT(RCC->CFGR,PLLSRC);
		break;
	case HSE_clock:
		SET_BIT(RCC->CFGR,PLLSRC);
		break;
	}
}
void RCC_HSEBYP(bypassedsSTS_t copy_ebypassedsSTS)
{
	RCC->CR&= ~(1<<HSEBYP);
	RCC->CR|=(copy_ebypassedsSTS<<HSEBYP);
}
void RCC_CSSCFG(Clock_Detector_t copy_eClock_detector)
{
	RCC->CR&= ~(1<<CSSON);
	RCC->CR|=(copy_eClock_detector<<CSSON);
}

void RCC_AHBEnableCLK(PeripheralAHB_t peripheral)
{
	SET_BIT(RCC->RCC_AHBENR,peripheral);
}
void RCC_AHBDisableCLK(PeripheralAHB_t peripheral)
{
	CLEAR_BIT(RCC->RCC_AHBENR,peripheral);

}

void RCC_APB1EnableCLK(PeripheralAPB1_t peripheral)
{
	SET_BIT(RCC->RCC_APB1ENR,peripheral);

}
void RCC_APB1DisableCLK(PeripheralAPB1_t peripheral)
{
	CLEAR_BIT(RCC->RCC_APB1ENR,peripheral);

}

void RCC_APB2EnableCLK(PeripheralAPB2_t peripheral)
{
	SET_BIT(RCC->RCC_APB2ENR,peripheral);

}
void RCC_APB2DisableCLK(PeripheralAPB2_t peripheral)
{
	CLEAR_BIT(RCC->RCC_APB2ENR,peripheral);

}



