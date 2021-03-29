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
#include "main.h"
#include "SystemMeasurements.h"


/* External Variables */
extern struct SYSMEAS systemmeasurements;
extern volatile uint32_t ADC_DMA_array[]; // Initiating DMA array for reading of ADC values

/* Internal Variables */
uint8_t uint8_errorStatus;
uint16_t uint16_throttleSignal;
int16_t int16_systemCurrent;
/* Start Code Here */

uint8_t pfx_error()
	{
		uint16_throttleSignal = ADC_DMA_array[0]; 	// Getting throttle signal
		int16_systemCurrent = systemmeasurements.int16_hallValue;		// Getting system current

		if((HAL_GPIO_ReadPin(GPIOB, H1_GPIO_Pin) == 1 && HAL_GPIO_ReadPin(GPIOB, H2_GPIO_Pin) == 0 && HAL_GPIO_ReadPin(GPIOB, H3_GPIO_Pin) == 1) || (HAL_GPIO_ReadPin(GPIOB, H1_GPIO_Pin) == 0 && HAL_GPIO_ReadPin(GPIOB, H2_GPIO_Pin) == 1 && HAL_GPIO_ReadPin(GPIOB, H3_GPIO_Pin) == 0))
			{
				uint8_errorStatus = 1;
			}
		if(int16_systemCurrent > 4000) // Current Status - Check: current > error threshold
			{
				uint8_errorStatus = 1;	// Current Status - Set error if current too high
			}
		if(uint16_throttleSignal < 600) // throttle status - check throttle signal < error threshold
			{
				uint8_errorStatus = 1;	// Throttle Status - Set error if throttle is missing
			}
		else
			{
				uint8_errorStatus = 0;
			}
		return uint8_errorStatus;
	}


