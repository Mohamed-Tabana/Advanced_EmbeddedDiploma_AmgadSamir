/*
 * RCC.c
 *
 *  Created on: Apr 14, 2023
 *      Author: ALTAWKEL
 */
#include "RCC.h"


void RCC_SetCLKSTS(CLKtype_t copy_tCLKtype, CLKStatus_t copy_tCLKStatus)
{
	switch(copy_tCLKtype)
	{
	case HSI_clock :
		if (copy_tCLKStatus==CLK_OFF)
		{
			CLEAR_BIT(RCC->CR,0);
		}
		else if (copy_tCLKStatus==CLK_ON)
		{
			SET_BIT(RCC->CR,0);
			while(READ_BIT(RCC->CR,1));
		}
		break;
	case HSE_clock:
		if (copy_tCLKStatus==CLK_OFF)
		{
			CLEAR_BIT(RCC->CR,16);
		}
		else if (copy_tCLKStatus==CLK_ON)
		{
			SET_BIT(RCC->CR,16);
			while(READ_BIT(RCC->CR,17));
		}
		break;
	case PLL_clock:
		if (copy_tCLKStatus==CLK_OFF)
		{
			CLEAR_BIT(RCC->CR,24);
		}
		else if (copy_tCLKStatus==CLK_ON)
		{
			SET_BIT(RCC->CR,24);
			while(READ_BIT(RCC->CR,25));
		}
		break;
	}
}

void RCC_SetSYSCLK(CLKtype_t copy_tCLKtype)
{
	RCC->CFGR |= (copy_tCLKtype & 0b00000011);
}

void RCC_HSECONFIG(HSEDIV_t copy_tHSEDIV)
{
	switch(copy_tHSEDIV)
	{
	case HSE_clock_not_divided:
		CLEAR_BIT(RCC->CFGR,17);
		break;
	case HSE_clock_divided_by_2:
		SET_BIT(RCC->CFGR,17);
		break;
	}
}
void RCC_PLLCONFIG(PLLMUL_t copy_tPLLMUX,CLKtype_t copy_tCLKtype)
{
	RCC->CFGR |= (copy_tPLLMUX & 0x3C0000);
	switch(copy_tCLKtype)
	{
	case HSI_clock:
		CLEAR_BIT(RCC->CFGR,16);
		break;
	case HSE_clock:
		SET_BIT(RCC->CFGR,16);
		break;
	}


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

