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
#include "main.h"
#include "SystemMeasurements.h"

/* External Variables */
extern volatile uint32_t ADC_DMA_array[]; // Initiating DMA array for reading of ADC values [6]

/* Internal Variables */
int16_t int16_throttleInput; 	//
int16_t int16_throttleOffset = 1100; 	//
int16_t int16_throttleMax= 2485; 	//
uint8_t uint8_throttleOutput; //

/* Start Code here */
int pfx_throttle() // Main function for commutation
{
	/* Collecting ADC value from throttle*/
	int16_throttleInput = ADC_DMA_array[0]; // Getting Throttle input from DMA array
	/* Calculating output value */
	uint8_throttleOutput = (int16_throttleInput - int16_throttleOffset)/((int16_throttleMax - int16_throttleOffset)/(1000));
	/* Returning output value between 0-1000 */
	if (uint8_throttleOutput > 1000)
		{
			uint8_throttleOutput = 1000;
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
