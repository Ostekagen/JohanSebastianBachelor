/*
 * Throttle.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

/* Includes */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "SystemMeasurements.h"

/* External Variables */
extern volatile uint32_t ADC_DMA_array[]; // Initiating DMA array for reading of ADC values [6]

/* Internal Variables */
int16_t int16_throttleInput; 			// Throttle input variable
int16_t int16_throttleOffset = 1050; 	// Throttle offset variable
int16_t int16_throttleMax= 3180; 		// Throttle max variable
int16_t int16_throttleCalc; 			// Throttle output variable
int16_t int16_throttleOutput; 			// Throttle output variable

/* Start Code here */
int16_t pfx_throttle() // Main function for commutation
{
	/* Collecting ADC value from throttle*/
	int16_throttleInput = ADC_DMA_array[0]; // Getting Throttle input from DMA array
	/* Calculating output value */
	int16_throttleCalc = (int16_throttleInput - int16_throttleOffset)*1000/(int16_throttleMax - int16_throttleOffset); // Calculating a throttle value
	/* Returning output value between 0-1000 */
	if (int16_throttleCalc > 1000)	// Limiting the output value to 1000
		{
			int16_throttleOutput = 1000;
			return int16_throttleOutput;	// Returning output value
		}
	else if (int16_throttleCalc < 0)	// Limiting the output value to 0
		{
			int16_throttleOutput = 0;
			return int16_throttleOutput;	// Returning output value
		}
	else								// Returning if values is between 0-1000
		{
			int16_throttleOutput = int16_throttleCalc;
			return int16_throttleOutput;	// Returning output value
		}
}
