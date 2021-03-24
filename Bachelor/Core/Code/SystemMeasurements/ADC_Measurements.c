/**
 * ADC_Measurements.c
 *
 *  Created on: Oct 22, 2019
 *      Author: Jan Michael Sønderby
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
int arrayPos = 0;


/* ADC data arrays */
float H1 = 0;
float H3 = 0;
float H2 = 0;
float BatteryVol;
float MDCVol = 0;
float SysCur = 0;
float Throttle = 0;

/* ADC data offset */
float ACCur_1_Offset = 0.0f;
float ACCur_2_Offset = 0.0f;
float ACCur_3_Offset = 0.0f;
float ACVol_1_Offset = 0.0f;
float ACVol_2_Offset = 0.0f;
float ACVol_3_Offset = 0.0f;
float DCVol_1_Offset = 0.0f;

/* ADC data multiplier */
float ACCur_1_multi = 0.0008f;    //Slope value of the trendline found through testing
float ACCur_2_multi = 0.0008f;
float ACCur_3_multi = 0.0008f;
float ACVol_1_multi = 0.0008f;
float ACVol_2_multi = 0.0008f;
float ACVol_3_multi = 0.0008f;
float DCVol_1_multi = 0.0008f;

/* ADC DMA Triple regular simultaneous mode samples memory*/
volatile uint32_t ADC_DMA_array[9];

/* Start ADC*/
void setupMeasurement()
{
	/* ADC in Triple regular simultaneous mode */
	if (HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t *)ADC_DMA_array, 9) != HAL_OK)
		{
		 	/* Start Error */
			Error_Handler();
		}

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
}
/* get new Offset */
void getOffset(float OffV1,float OffV2,float OffV3,float OffC1,float OffC2,float OffC3)
{
	ACCur_1_Offset = OffC1;
	ACCur_2_Offset = OffC2;
	ACCur_3_Offset = OffC3;
	ACVol_1_Offset = OffV1;
	ACVol_2_Offset = OffV2;
	ACVol_3_Offset = OffV3;
}
/* read ADC values and converts to voltage and current values in float */
void getMeasurement()
{
	/* Calculate Value */
	BatteryVol = (float)ADC_DMA_array[0];  	// Battery Voltage
	MDCVol = (float)ADC_DMA_array[3];		// MDC Voltage
	SysCur = (float)ADC_DMA_array[6];		// system Current
	H1 = (float)ADC_DMA_array[1];		// H1
	H3 = (float)ADC_DMA_array[4];		// H3
	H2 = (float)ADC_DMA_array[5];		// H2
	Throttle = (float)ADC_DMA_array[2];		// Throttle

}
