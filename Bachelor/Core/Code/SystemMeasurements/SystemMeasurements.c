/**
 * ADC_Measurements.c
 *
 *  Created on: Mar 26, 2021
 *      Author: Rasmus Bank Mikkelsen
 */

/* Includes */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

/* External Variables */

/* Variables */
struct ST_SYSMEAS{int16_t int16_batteryVol;int16_t int16_hallValue;int16_t motorVolValue;}systemmeasurements;	// Struct for returning measurements
volatile uint32_t ADC_DMA_array[6]; 	// ADC DMA Triple regular simultaneous mode samples memory

/* Start Code Here */
void pfx_setupMeasurement() // Start ADC
{
	/* ADC in Triple regular simultaneous mode */
	if (HAL_ADC_Start(&hadc2) != HAL_OK)
		{
		 	/* Start Error */
		 	Error_Handler();
		}
	if (HAL_ADC_Start(&hadc3) != HAL_OK)
		{
			/* Start Error */
			Error_Handler();
		}

	if (HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t *)ADC_DMA_array, 6) != HAL_OK)
		{
		 	/* Start Error */
			Error_Handler();
		}

}

void pfx_getMeasurement() // Read ADC values and converts to voltage and current values in float
{
	systemmeasurements.int16_hallValue = ADC_DMA_array[1];		// TODO: find offset og træk det fra
	systemmeasurements.motorVolValue = ADC_DMA_array[2];
	systemmeasurements.int16_batteryVol = ADC_DMA_array[3];
}


