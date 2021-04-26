/*
 * PWM.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "main.h"
#include "stm32f4xx_hal_tim.h"

TIM_HandleTypeDef htim1;
TIM_OC_InitTypeDef sConfigOC;

/* External Variables */

/* Internal Variables */

/* Start Code here */
void pfx_PWM_Stop() // Stops the PWM by applying a number larger than counter value (In PWM Mode 2)
	{
		TIM1->CCR1 = 0; //Apply 0 to counter of 3000
		TIM1->CCR2 = 0;	//Apply 0 to counter of 3000
		TIM1->CCR3 = 0;	//Apply 0 to counter of 3000
	}

void pfx_PWM(float f_dutyCycle, uint8_t uint8_timerChannel)	// Starts the appropriate PWM with the applied duty cycle
	{
		if(uint8_timerChannel == 1)					// Checks for Channel number
			{
				TIM1->CCR1 = f_dutyCycle*3000.0; 	// Applies a counter value scaled by duty cycle (between 0.0 - 1.0) to Timer 1 Channel 1
			}
		else if(uint8_timerChannel == 2)			// Checks for Channel number
			{
				TIM1->CCR2 = f_dutyCycle*3000.0; 	// Applies a counter value scaled by duty cycle (between 0.0 - 1.0) to Timer 1 Channel 2
			}
		else if(uint8_timerChannel == 3)			// Checks for Channel number
			{
				TIM1->CCR3 = f_dutyCycle*3000.0;	// Applies a counter value scaled by duty cycle (between 0.0 - 1.0) to Timer 1 Channel 3
			}
		else										// If PWM not set correct - Kill PWM
			{
				TIM1->CCR1 = 0;					// Apply 0 to counter of 3000
				TIM1->CCR2 = 0;					// Apply 0 to counter of 3000
				TIM1->CCR3 = 0;					// Apply 0 to counter of 3000
			}
	}
