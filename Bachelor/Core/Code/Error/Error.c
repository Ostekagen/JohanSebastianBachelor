/*
 * Error.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

/* Includes */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "Brake.h"
#include "main.h"

/* External Variables */
uint8_t uint8_errorStatus;
extern volatile uint32_t ADC_DMA_array[]; // Initiating DMA array for reading of ADC values
/* Internal Variables */
uint16_t uint16_throttleSignal;
int16_t int16_systemCurrent;
/* Start Code Here */

uint8_t pfx_error()
	{
		uint16_throttleSignal = ADC_DMA_array[2]; 	// Getting throttle signal
		/*int16_systemCurrent = ADC_DMA_array[x];*/		// Getting system current

		if((HAL_GPIO_ReadPin(GPIOB, H1_GPIO_Pin) == 1 && HAL_GPIO_ReadPin(GPIOB, H2_GPIO_Pin) == 0 && HAL_GPIO_ReadPin(GPIOB, H3_GPIO_Pin) == 1) || (HAL_GPIO_ReadPin(GPIOB, H1_GPIO_Pin) == 0 && HAL_GPIO_ReadPin(GPIOB, H2_GPIO_Pin) == 1 && HAL_GPIO_ReadPin(GPIOB, H3_GPIO_Pin) == 0))
			{
				uint8_errorStatus = 1;
			}
		/*if(int16_systemCurrent > #VALUE#) // Current Status - Check: current > error threshold
			{
				uint8_errorStatus = 1;	// Current Status - Set error if current too high
			}*/
		/*if(uint16_throttleSignal < #VALUE#) // throttle status - check throttle signal < error threshold
			{
				uint8_errorStatus = 1;	// Throttle Status - Set error if throttle is missing
			}*/
		else
			{
				uint8_errorStatus = 0;
			}
		return uint8_errorStatus;
	}


