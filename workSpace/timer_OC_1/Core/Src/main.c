/*
 * main.c
 *
 *  Created on: Jun 4, 2021
 *      Author: Aar?n Escoboza Villegas
 */

#include "main.h"
#include "math.h"

TIM_HandleTypeDef tim2OC = {0};

uint32_t pulse500Hz = 16000;
uint32_t pulse1KHz = 8000;
uint32_t pulse2KHz = 4000;
uint32_t pulse4KHz = 2000;

int main(void)
{
	HAL_Init();
	GPIO_Init();
	TIM2_Init();
	if(HAL_TIM_OC_Start_IT(&tim2OC,TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_TIM_OC_Start_IT(&tim2OC,TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_TIM_OC_Start_IT(&tim2OC,TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_TIM_OC_Start_IT(&tim2OC,TIM_CHANNEL_4) != HAL_OK)
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
	tim2OC.Instance = TIM2;
	tim2OC.Init.Period = 0xFFFFFFFF;
	tim2OC.Init.Prescaler = 0;

	if(HAL_TIM_OC_Init(&tim2OC) != HAL_OK)
	{
		Error_Handler();
	}

	//  Channel settings
	tim2Channel.OCMode = TIM_OCMODE_TOGGLE;
	tim2Channel.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	tim2Channel.Pulse = pulse500Hz;

	if(HAL_TIM_OC_ConfigChannel(&tim2OC,&tim2Channel,TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	tim2Channel.Pulse = pulse1KHz;

	if(HAL_TIM_OC_ConfigChannel(&tim2OC,&tim2Channel,TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	tim2Channel.Pulse = pulse2KHz;

	if(HAL_TIM_OC_ConfigChannel(&tim2OC,&tim2Channel,TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	tim2Channel.Pulse = pulse4KHz;

	if(HAL_TIM_OC_ConfigChannel(&tim2OC,&tim2Channel,TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
}
void Error_Handler(void)
{
	while(1);
}

 void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	 //f = 500 Hz
	 if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	 {
		 __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_1,HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_1)+pulse500Hz);
	 }
	 //f = 1KHz
	 if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	 {
		 __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_2,HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_2)+pulse1KHz);
	 }
	 //f = 2KHz
	 if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
	 {
		 __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_3,HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_3)+pulse2KHz);
	 }
	 //f = 4KHz
	 if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
	 {
		 __HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_4,HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_4)+pulse4KHz);
	 }
}
