/*
 * it.c
 *
 *  Created on: May 30, 2021
 *      Author: aaron
 */

#include "main.h"
extern TIM_HandleTypeDef tim2IC;
void SysTick_Handler(void)
{
	HAL_IncTick();
}

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim2IC);
}
