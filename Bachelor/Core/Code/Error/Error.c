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
extern struct ST_SYSMEAS systemmeasurements;	// Calling the measurements struct
extern volatile uint32_t ADC_DMA_array[]; 	// Calling DMA array for reading ADC values

/* Internal Variables */
uint8_t uint8_errorStatus = 0;	// Initializing variable
uint16_t uint16_throttleSignal;	// Initializing variable
int16_t int16_systemCurrent;	// Initializing variable

/* Start Code Here */
uint8_t pfx_error()
	{
		uint16_throttleSignal = ADC_DMA_array[0]; 					// Getting throttle signal
		int16_systemCurrent = systemmeasurements.int16_hallValue;	// Getting system current

		if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == 1 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == 1 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) == 1) || (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == 0 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == 0 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) == 0)) // Checking for two faulty Hall element combinations
			{
				uint8_errorStatus = 1;	// Hall Status- Set error if Hall faulty TODO: Find correct Hall combinations
			}
		else if(int16_systemCurrent > 4000) 	// Current Status - Check: current > error threshold TODO: Find correct value
			{
				uint8_errorStatus = 1;	// Current Status - Set error if current too high
			}
		else if(uint16_throttleSignal < 400) // throttle status - check throttle signal < error threshold -  Offset is 690, go lower for buffer
			{
				uint8_errorStatus = 1;	// Throttle Status - Set error if throttle is missing
			}
		else							// If no error
			{
				uint8_errorStatus = 0;	// Set no error
			}
		return uint8_errorStatus;		// Return error status
	}
