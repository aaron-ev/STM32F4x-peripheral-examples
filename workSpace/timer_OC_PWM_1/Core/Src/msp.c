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

 void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
 {
	 GPIO_InitTypeDef tim2CH1_gpio = {0};

	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();


	/*
	 * PA0 -> CH1
	 * PA1 -> CH2
	 * PB10 -> CH3
	 * PB2 -> CH4
	 */

	tim2CH1_gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	tim2CH1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2CH1_gpio.Pull = GPIO_NOPULL;
	tim2CH1_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	tim2CH1_gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA,&tim2CH1_gpio);

	tim2CH1_gpio.Pin = GPIO_PIN_2 | GPIO_PIN_10;
	tim2CH1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2CH1_gpio.Pull = GPIO_NOPULL;
	tim2CH1_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	tim2CH1_gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOB,&tim2CH1_gpio);

	//HAL_NVIC_SetPriority(TIM2_IRQn,15,0);
	//HAL_NVIC_EnableIRQ(TIM2_IRQn);
 }
