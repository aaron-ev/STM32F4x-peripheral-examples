/*
 * main.c
 *
 *  Created on: Jun 4, 2021
 *      Author: Aar?n Escoboza Villegas
 */

#include "main.h"
#include "math.h"

TIM_HandleTypeDef tim2PWM = {0};

uint32_t pulse25Porcent = 25;
uint32_t pulse45Porcent = 45;
uint32_t pulse75Porcent = 75;
uint32_t pulse90Porcent = 90;

uint32_t period = 1000;
int main(void)
{
	HAL_Init();
	GPIO_Init();
	TIM2_Init();
	if(HAL_TIM_PWM_Start(&tim2PWM,TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if(HAL_TIM_PWM_Start(&tim2PWM,TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	if(HAL_TIM_PWM_Start(&tim2PWM,TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	if(HAL_TIM_PWM_Start(&tim2PWM,TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
	while(1);
	return 0;
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

void TIM2_Init(void)
{
	TIM_OC_InitTypeDef tim2Channel = {0};

	// Time base unit settings
	tim2PWM.Instance = TIM2;
	tim2PWM.Init.Prescaler = 16000-1; // clk 1kHz
	tim2PWM.Init.Period = period;// 1Hz

	if(HAL_TIM_PWM_Init(&tim2PWM) != HAL_OK)
	{
		Error_Handler();
	}

	//  Channel settings
	tim2Channel.OCMode = TIM_OCMODE_PWM1;
	tim2Channel.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	tim2Channel.Pulse = pulse45Porcent*period/100;

	if(HAL_TIM_PWM_ConfigChannel(&tim2PWM,&tim2Channel,TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	tim2Channel.Pulse = pulse25Porcent*period/100;

	if(HAL_TIM_PWM_ConfigChannel(&tim2PWM,&tim2Channel,TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	tim2Channel.Pulse = pulse75Porcent*period/100;

	if(HAL_TIM_PWM_ConfigChannel(&tim2PWM,&tim2Channel,TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	tim2Channel.Pulse = pulse90Porcent*period/100;

	if(HAL_TIM_PWM_ConfigChannel(&tim2PWM,&tim2Channel,TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
}
void Error_Handler(void)
{
	while(1);
}

