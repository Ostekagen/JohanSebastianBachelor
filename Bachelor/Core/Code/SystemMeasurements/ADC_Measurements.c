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
#include "ADC_Measurements.h"


ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

/* data arrays position*/

struct SYSMEAS{int16_t int16_batteryVol;int16_t int16_hallValue;int16_t motorVolValue;}SystemMeasurements;

/* ADC DMA Triple regular simultaneous mode samples memory*/
volatile uint32_t ADC_DMA_array[6];

/* Start ADC*/
void setupMeasurement()
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

/* read ADC values and converts to voltage and current values in float */
void getMeasurement()
{

	SystemMeasurements.int16_hallValue = ADC_DMA_array[1];		// TODO: find offset og træk det fra
	SystemMeasurements.motorVolValue = ADC_DMA_array[2];
	SystemMeasurements.int16_batteryVol = ADC_DMA_array[3];
}


