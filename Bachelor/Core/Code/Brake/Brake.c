/*
 * Brake.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

/* Includes */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "main.h"
int iAlive;
int PinInput;
/* External Variables */

/* Internal Variables */
int8_t int8_brakeOutput;

/* Start Code Here */
int8_t pfx_brake() // Brake Check Function
	{
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) != 0) 		// Read Brake Input GPIO PIN
			{
				int8_brakeOutput = 1;						// Brake Activated
			}
		else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == 0)	// Read Brake Input GPIO PIN
			{
				int8_brakeOutput = 0;						// Brake Inactive
			}
		return int8_brakeOutput;							// Return Brake Info
	}
