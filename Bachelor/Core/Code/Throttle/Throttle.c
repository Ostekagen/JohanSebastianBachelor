/*
 * Throttle.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

#include <math.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
//#include "stm32f4xx_hal_tim.h"	// Laver fejl i drivers
#include "main.h"
#include "ADC_Measurements.h"

/* External Variables */
extern volatile uint32_t ADC_DMA_array[]; // Initiating DMA array for reading of ADC values


/* Internal Variables */
int16_t int16_throttleInput; 	//
int16_t int16_throttleOffset = 1100; 	//
int16_t int16_throttleMax= 2485; 	//
uint8_t uint8_throttleOutput; //

/* Start Code here */
int pfx_Throttle() // Main function for commutation
{
	/* Collecting ADC value from throttle*/
	int16_throttleInput = ADC_DMA_array[2];
	/* Calculating output value */
	uint8_throttleOutput = (int16_throttleInput - int16_throttleOffset)/((int16_throttleMax - int16_throttleOffset)/(100));
	/* Returning output value between 0-100 */
	if (uint8_throttleOutput > 100)
		{
			uint8_throttleOutput = 100;
			return uint8_throttleOutput;
		}
	else if (uint8_throttleOutput < 0)
		{
			uint8_throttleOutput = 0;
			return uint8_throttleOutput;
		}
	else
		{
			return uint8_throttleOutput;
		}
}
