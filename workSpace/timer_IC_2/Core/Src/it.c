/*
 * it.c
 *
 *  Created on: May 30, 2021
 *      Author: Aar?n Escoboza Villegas
 */

#include "main.h"
extern TIM_HandleTypeDef tim2IC;
extern TIM_HandleTypeDef tim6;
void SysTick_Handler(void)
{
	HAL_IncTick();
}

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim2IC);
}

void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim6);
}
