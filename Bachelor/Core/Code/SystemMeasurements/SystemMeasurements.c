/**
 * ADC_Measurements.c
 *
 *  Created on: Mar 26, 2021
 *      Author: Rasmus Bank Mikkelsen
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"


ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;


// Data Struct for system measurements
struct ST_SYSMEAS{int16_t int16_batteryVol;int16_t int16_hallValue;int16_t motorVolValue;}systemmeasurements;

/* ADC DMA Triple regular simultaneous mode samples memory*/
volatile uint32_t ADC_DMA_array[6];

/* ADC setup to save values in the ADC_DMA_array*/
void pfx_setupMeasurement()
{
	// Starting ADC2 and monitoring for error
	if (HAL_ADC_Start(&hadc2) != HAL_OK)
		{
		 	/* Start Error */
		 	Error_Handler();
		}
	// Starting ADC3 and monitoring for error
	if (HAL_ADC_Start(&hadc3) != HAL_OK)
		{
			/* Start Error */
			Error_Handler();
		}
	// Starting multimode and monitoring for error
	if (HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t *)ADC_DMA_array, 6) != HAL_OK)
		{
		 	/* Start Error */
			Error_Handler();
		}
}

/* Save ADC measurements into struct */
void pfx_getMeasurement()
{
	systemmeasurements.int16_hallValue = ADC_DMA_array[1];		// TODO: find offset og træk det fra
	systemmeasurements.motorVolValue = ADC_DMA_array[2];
	systemmeasurements.int16_batteryVol = ADC_DMA_array[3];
}


