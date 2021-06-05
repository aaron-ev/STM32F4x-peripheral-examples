/*
 * main.c
 *
 *  Created on: Jun 1, 2021
 *      Author: Aarón Escoboza Villegas
 */

#include "main.h"
#include "math.h"
TIM_HandleTypeDef tim2IC = {0};

uint8_t flagDone = FALSE;
uint32_t CCR_values[2] = {0,0};
float inputSingalFreq;

int main(void)
{
	HAL_Init();
	GPIO_Init();
	LSE_Init();
	TIM2_Init();

	HAL_TIM_IC_Init(&tim2IC);
	HAL_TIM_IC_Start_IT(&tim2IC,TIM_CHANNEL_1);

	float PCLK1Period;
	PCLK1Period = 1/(float)(HAL_RCC_GetPCLK1Freq());
	while(1)
	{
		if (flagDone == TRUE)
		{

			inputSingalFreq = 1 / (PCLK1Period * (float)abs(CCR_values[1] - CCR_values[0]));
		}
	}

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

void LSE_Init(void)
{
	RCC_OscInitTypeDef lseOsc = {0};

	lseOsc.OscillatorType = RCC_OSCILLATORTYPE_LSE;
	lseOsc.LSEState = RCC_LSE_ON;

	if(HAL_RCC_OscConfig(&lseOsc) != HAL_OK)
	{

		Error_Handler();
	}
	HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_LSE,RCC_MCODIV_1);
}
void TIM2_Init(void)
{
	TIM_IC_InitTypeDef tim2Channel = {0};

	// Time base unit settings
	tim2IC.Instance = TIM2;
	tim2IC.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim2IC.Init.Period = 0xFFFFFFFF;
	tim2IC.Init.Prescaler = 0;

	if(HAL_TIM_IC_Init(&tim2IC) != HAL_OK)
	{
		Error_Handler();
	}

	//  Channel settings
	tim2Channel.ICFilter = 0;
	tim2Channel.ICPolarity = TIM_ICPOLARITY_RISING;
	tim2Channel.ICPrescaler = TIM_ICPSC_DIV1;
	tim2Channel.ICSelection = TIM_ICSELECTION_DIRECTTI;

	if(HAL_TIM_IC_ConfigChannel(&tim2IC,&tim2Channel,TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
}
void Error_Handler(void)
{
	while(1);
}

 void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	 static uint8_t edgeCounter = 0;
	 if(flagDone == FALSE)
	 {
		 CCR_values[edgeCounter] = htim->Instance->CCR1;
		 edgeCounter++;
		 if(edgeCounter > 1)
			 flagDone = TRUE;
	 }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
}
