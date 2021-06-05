/*
 * main.c
 *
 *  Created on: May 25, 2021
 *      Author: aaron
 */


#include "stm32F4xx_hal.h"
#include "main.h"

void SystemClockConfig(void);
void UART2_init(void);

UART_HandleTypeDef uart2;

int main(void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_init();
	while(1);
	return 0;
}

void SystemClockConfig(void)
{
	RCC_OscInitTypeDef oscInit = {0};
	RCC_ClkInitTypeDef clkInit = {0};
	uint32_t sysClk = 0;
	uint32_t AHBClk = 0;

	oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscInit.HSEState = RCC_HSE_BYPASS;

	if (HAL_RCC_OscConfig(&oscInit) != HAL_OK)
	{
		// Error handler
	}

	clkInit.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_SYSCLK;
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV2;
	clkInit.APB1CLKDivider = RCC_SYSCLK_DIV2;

	if(HAL_RCC_ClockConfig(&clkInit,FLASH_ACR_LATENCY_0WS) != HAL_OK)
	{
		// Error handler
	}
	__HAL_RCC_HSI_DISABLE();

	sysClk = HAL_RCC_GetSysClockFreq();
	AHBClk = HAL_RCC_GetHCLKFreq();

}

void UART2_init(void)
{
	uart2.Instance = USART2;
	uart2.Init.BaudRate = 115200;
	uart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart2.Init.Mode = UART_MODE_TX_RX;
	uart2.Init.Parity = UART_PARITY_NONE;
	uart2.Init.StopBits = UART_STOPBITS_1;
	uart2.Init.WordLength = UART_WORDLENGTH_8B;

	if(HAL_UART_Init(&uart2) != HAL_OK)
	{
		//Error handler
	}
}

 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	 GPIO_InitTypeDef uart2_tx_rx;
	 // 1. Enable clock for USART2 peripheral
	 __HAL_RCC_USART2_CLK_ENABLE();
	 // 2. Do the pin muxing configurations

	 /*
	 uart2_tx_rx.Mode = GPIO_MODE_AF_PP;
	 uart2_tx_rx.Pin = GPIO_PIN_2;
	 uart2_tx_rx.Pull = GPIO_PULLUP;
	 uart2_tx_rx.Speed = GPIO_SPEED_FREQ_LOW;
	 HAL_GPIO_Init(GPIO_TypeDef  GPIOA, &uart2_tx_rx);

	 uart2_tx_rx.Pin = GPIO_PIN_3;
	 HAL_GPIO_Init(GPIOA,&uart2_tx_rx);
	 */
	 // 3. Enable IRQ and set up the priority (NVIC settings)
	 HAL_NVIC_EnableIRQ(USART2_IRQn);
	 HAL_NVIC_SetPriority(USART2_IRQn,15,0);
}

