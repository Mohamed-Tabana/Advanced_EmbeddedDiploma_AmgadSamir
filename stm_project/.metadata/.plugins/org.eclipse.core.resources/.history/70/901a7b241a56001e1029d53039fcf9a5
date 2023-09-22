/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 10/4/2023				  	  **************/
/********* FILE NAME : RCC_Program.c				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/
#include <stdint.h>

#include "../../LIBRARY/STM32F103xx.h"
#include "../../LIBRARY/BitMath.h"
#include "../../LIBRARY/ErrTypes.h"

#include "../Inc/RCC_Interface.h"

/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetClockStatus()
 *     FUNCTIONALITY : Set the selected clock state (ON/OFF)
 *     ARGUMENT 	 : UINT8 Clock Type , UINT8 State of Clock
 *     RETURN   	 : Void
 *
 *---------------------------------------------------------------------------------*/
void RCC_SetClockStatus(uint8_t CLK_TYPE , uint8_t Status)
{
	uint32_t Counter=0;
	/*Switch Clock type*/
	switch (CLK_TYPE)
	{

	case HSE:
		if(Status == ON)
		{

			/*STEP 1 : HSE ON*/
			RCC->CR = (1<<16);

			/*STEP 2 : wait till HSE Ready Or TIME is out*/
			while (	!(GET_BIT(RCC->CR,17))	&&	(Counter<=TIME_OUT)	)
			{
				Counter++;
			}
			if (Counter == TIME_OUT)
			{
				/* Error */

				Counter=0;
			}

		}
		else if (Status==OFF)
		{
			/*STEP 1 : HSE OFF*/
			RCC->CR &= ~(1<<16);
		}

		break;
	case HSI:
		if(Status == ON)
		{
			/*STEP 1 : HSI ON*/
			RCC->CR = (1<<0);

			/*STEP 2 : wait till HSI Ready Or TIME is out*/
			while (	!(GET_BIT(RCC->CR,1))	&&	(Counter<=TIME_OUT)	)
			{
				Counter++;
			}
			if (Counter == TIME_OUT)
			{
				/* Error */

				Counter=0;
			}
		}
		else if (Status==OFF)
		{
			/*STEP 1 : HSE OFF*/
			RCC->CR &= ~(1<<0);
		}
		break;
	case PLL:
		if(Status == ON)
		{
			/*STEP 1 : PLL ON*/
			RCC->CR = (1<<24);

			/*STEP 2 : wait till PLL Ready Or TIME is out*/
			while (	!(GET_BIT(RCC->CR,25))	&&	(Counter<=TIME_OUT)	)
			{
				Counter++;
			}
			if (Counter == TIME_OUT)
			{
				/* Error */

				Counter=0;
			}
		}
		else if (Status==OFF)
		{
			/*STEP 1 : PLL OFF*/
			RCC->CR &= ~(1<<24);
		}
		break;

	}

}

/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetSystemClock()
 *     FUNCTIONALITY : Set the selected clock as System Clock
 *     ARGUMENT 	 : UINT8 Clock Type
 *     RETURN   	 : Void
 *
 *---------------------------------------------------------------------------------*/
void RCC_SetSystemClock(uint8_t CLK_TYPE)
{
	switch (CLK_TYPE)
	{
	case HSE :
		/*Switch System Clock to HSE*/
		RCC->CFGR |= 1 ;
		break;
	case HSI :
		/*Switch System Clock to HSI*/
		RCC->CFGR &= ~(1) ;
		break;
	case PLL :
		/*Switch System Clock to PLL*/
		RCC->CFGR |= 2 ;
		break;
	}
}
/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_HSE_Divider()
 *     FUNCTIONALITY : Set the selected Factor to divide HSE Clock by
 *     ARGUMENT 	 : UINT8 Factor (HSE_DivideBy2 , HSE_DivideBy1)
 *     RETURN   	 : Void
 *
 *---------------------------------------------------------------------------------*/
void RCC_SetHSE_Divider(uint8_t Factor)
{
	if (Factor == HSE_DivideBy1)
	{
		RCC->CFGR &= ~(1<<17);
	}
	else if (Factor == HSE_DivideBy2)
	{
		RCC->CFGR |= (1<<17);
	}
	else
	{
		/*ERROR*/
	}
}



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetPLL_Configs()
 *     FUNCTIONALITY : Set the PLL With chosen configurations
 *     ARGUMENT 	 : UINT8 PLL_MultiFactor (BY_2,BY_3,...,BY_16) , UINT8 Pll_Source (HSE,HSI)
 *     RETURN   	 : Void
 *	   NOTES 		 : Before using this function, PLL state Must be off
 *---------------------------------------------------------------------------------*/
void RCC_SetPLL_Configs(uint8_t PLL_MultiFactor , uint8_t Pll_Source)
{
	/*STEP 1 : Configure PLL Factor as wanted*/
	if (PLL_MultiFactor==BY_2)
	{
		/*Clearing all 4 BITS to divide by2*/
		RCC->CFGR &= ~(15<<18);
	}
	else
	{
		/*Clearing all 4 Bits to avoid old values*/
		RCC->CFGR &= ~(15<<18);
		/*Assigning new value to the PLL bits */
		RCC->CFGR |= (PLL_MultiFactor<<18);
	}

	/*STEP 2 : SET PLL_Source*/

	if(Pll_Source == HSE)
	{
		RCC->CFGR |= (1<<16);
	}
	else if (Pll_Source == HSI)
	{
		RCC->CFGR &= ~(1<<16);
	}
}
/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_AHBPeripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To AHB Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name , UINT8 Clock State
 *     RETURN   	 : Void
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
void RCC_Set_AHBPeripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State)
{
	switch (CLK_State)
	{
	case ENABLED :
		/*SET The Peripheral bit to enable it*/
		RCC->AHBENR |= (1<<Periphral_Name); 	break;

	case DISABLED :
		/*CLEAR The Peripheral bit to Disable it*/
		RCC->AHBENR &= ~(1<<Periphral_Name); 	break;
		break;

	default : /*ERROR*/ break;
	}
}



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_APB2Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To APB2 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name , UINT8 Clock State
 *     RETURN   	 : Void
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
void RCC_Set_APB2Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State)
{
	switch (CLK_State)
		{
		case ENABLED :
			/*SET The Peripheral bit to enable it*/
			RCC->APB2ENR |= (1<<Periphral_Name); 	break;

		case DISABLED :
			/*CLEAR The Peripheral bit to Disable it*/
			RCC->APB2ENR &= ~(1<<Periphral_Name); 	break;
			break;

		default : /*ERROR*/ break;
		}
}


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_APB1Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To APB1 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name , UINT8 Clock State
 *     RETURN   	 : Void
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
void RCC_Set_APB1Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State)
{
	switch (CLK_State)
		{
		case ENABLED :
			/*SET The Peripheral bit to enable it*/
			RCC->APB1ENR |= (1<<Periphral_Name); 	break;

		case DISABLED :
			/*CLEAR The Peripheral bit to Disable it*/
			RCC->APB1ENR &= ~(1<<Periphral_Name); 	break;
			break;

		default : /*ERROR*/ break;
		}
}
