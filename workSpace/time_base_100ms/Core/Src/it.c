/*
 * it.c
 *
 *  Created on: May 30, 2021
 *      Author: aaron
 */

#include "stm32f4xx.h"
void SysTick_Handler(void)
{
	HAL_IncTick();
}
