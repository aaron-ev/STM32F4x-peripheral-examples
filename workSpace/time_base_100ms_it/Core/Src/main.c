/*
 * main.c
 *
 *  Created on: May 31, 2021
 *      Author: Aar?n Escoboza Villegas
 */

#include "main.h"
TIM_HandleTypeDef tim100ms = {0};

int main(void)
{
	HAL_Init();
	GPIO_Init();
	TIM6_Init();

	HAL_TIM_Base_Start_IT(&tim100ms);

	while(1);

	return 0;
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
}
void GPIO_Init()
{
	GPIO_InitTypeDef ledBoard = {0};

	ledBoard.Mode = GPIO_MODE_OUTPUT_PP;
	ledBoard.Pull = GPIO_PULLUP;
	ledBoard.Pin = GPIO_PIN_5;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA,&ledBoard);
}

void TIM6_Init(void)
{
	__HAL_RCC_TIM6_CLK_ENABLE();
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	tim100ms.Instance = TIM6;
	tim100ms.Init.Prescaler = 16000;
	tim100ms.Init.Period = 100 - 1; // Update event 100 ms

	if(HAL_TIM_Base_Init(&tim100ms) != HAL_OK)
	{
		Error_Handler();
	}
}
void Error_Handler(void)
{
	while(1);
}
