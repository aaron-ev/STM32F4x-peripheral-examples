/*
 * msp.c
 *
 *  Created on: May 25, 2021
 *      Author: aaron
 */

#include "stm32f4xx_hal.h"

 void HAL_MspInit(void)
{
	// Low level processor specific inits.

	// 1. Set up the priority grouping of ARM Cortex mx processor
	 HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	// 2. Enable the required system exceptions of the arm Cortex mx processor

	// 3. Configure the priority for the system exceptions
}
