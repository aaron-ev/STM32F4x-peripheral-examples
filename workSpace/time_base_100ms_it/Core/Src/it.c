/*
 * it.c
 *
 *  Created on: May 30, 2021
 *      Author: aaron
 */

#include "main.h"
extern TIM_HandleTypeDef tim100ms;
void SysTick_Handler(void)
{
	HAL_IncTick();
}

void TIM6_DAC_IRQHandler()
{
	HAL_TIM_IRQHandler(&tim100ms);
}
