#include "RCC_int.h"
#include <stdint.h>
#include "STM32f446xx.h"
#include "ErrType.h"
#include "Utils.h"
#include "stdio.h"

void RCC_AHB1EnableCLK(PeripheralAHB1_t peripheral)
{
	SET_BIT(RCC->AHB1ENR,peripheral);
}
void RCC_AHB1DisableCLK(PeripheralAHB1_t peripheral)
{
	CLEAR_BIT(RCC->AHB1ENR,peripheral);

}

void RCC_APB1EnableCLK(PeripheralAPB1_t peripheral)
{
	SET_BIT(RCC->APB1ENR,peripheral);

}
void RCC_APB1DisableCLK(PeripheralAPB1_t peripheral)
{
	CLEAR_BIT(RCC->APB1ENR,peripheral);

}

void RCC_APB2EnableCLK(PeripheralAPB2_t peripheral)
{
	SET_BIT(RCC->APB2ENR,peripheral);

}
void APB2DisableCLK(PeripheralAPB2_t peripheral)
{
	CLEAR_BIT(RCC->APB2ENR,peripheral);

}
