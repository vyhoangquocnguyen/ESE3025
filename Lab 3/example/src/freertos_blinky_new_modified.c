/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

int red=0;
int green=1;
int blue=2;

static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	/* Initial LED0 state is off */
	Board_LED_Set(red, false);
	Board_LED_Set(green, false);
	Board_LED_Set(blue, false);
}
/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters)
{
	//bool LedState = false;
	while (1)
	{
		Board_LED_Set(red, true); //turn on LED
		vTaskDelay(configTICK_RATE_HZ);
		Board_LED_Set(red, false);//turn off LED
		vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ/2);//delay for 0.5s
	}
}
static void vLEDTask2(void *pvParameters)
{
	vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ/2);

	while (1)
	{
		Board_LED_Set(green, true);//on
		vTaskDelay(configTICK_RATE_HZ);
		Board_LED_Set(green, false);//off
		vTaskDelay( 3 * configTICK_RATE_HZ + configTICK_RATE_HZ/2 );
	}
}
static void vLEDTask3(void *pvParameters)
{
	vTaskDelay(3 * configTICK_RATE_HZ);
	while (1)
	{

		Board_LED_Set(blue, true);//on
		vTaskDelay(configTICK_RATE_HZ);
		Board_LED_Set(blue, false);//off
		vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ/2);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	prvSetupHardware();

	/* LED1 toggle thread */
	xTaskCreate(vLEDTask1, (signed char* ) "vTaskLed1",
			configMINIMAL_STACK_SIZE,NULL, (tskIDLE_PRIORITY+3UL),//changed priority
			(xTaskHandle *) NULL);

	/* LED2 toggle thread */
	xTaskCreate(vLEDTask2, (signed char* ) "vTaskLed2",
			configMINIMAL_STACK_SIZE,NULL, (tskIDLE_PRIORITY+2UL ),// changed priority
			(xTaskHandle *) NULL);

	xTaskCreate(vLEDTask3, (signed char* ) "vTaskLed3",
			configMINIMAL_STACK_SIZE,NULL, (tskIDLE_PRIORITY+1UL),//changed priority
			(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
