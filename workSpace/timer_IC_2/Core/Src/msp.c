/*
 * msp.c
 *
 *  Created on: Jun 2, 2021
 *      Author: Aar?n Escoboza Villegas
 */

#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
	 HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
}

 void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
 {
	 GPIO_InitTypeDef tim2CH1_gpio = {0};

	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	tim2CH1_gpio.Pin = GPIO_PIN_0;
	tim2CH1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2CH1_gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA,&tim2CH1_gpio);

	HAL_NVIC_SetPriority(TIM2_IRQn,15,0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
 }
 void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
 {
	 __HAL_RCC_TIM6_CLK_ENABLE();
	 HAL_NVIC_SetPriority(TIM6_DAC_IRQn,15,0);
	 HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
 }
