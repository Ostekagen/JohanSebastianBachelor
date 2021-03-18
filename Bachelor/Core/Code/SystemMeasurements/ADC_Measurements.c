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
float ACCur_1[500] = {0};
float ACCur_2[500] = {0};
float ACCur_3[500] = {0};
float ACVol_1[500] = {0};
float ACVol_2[500] = {0};
float ACVol_3[500] = {0};
float DCVol_1[500] = {0};

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
	/* Set array position */
	if (arrayPos >= 499 )
		{
			arrayPos = 0;
		}
	else
		{
			arrayPos++;
		}
	/* Calculate Value */
	ACVol_1[arrayPos] = ((float)ADC_DMA_array[0]*ACVol_1_multi)-ACVol_1_Offset;  	// channel 0 PIN PA0 dma 0
	ACVol_2[arrayPos] = ((float)ADC_DMA_array[3]*ACVol_2_multi)-ACVol_2_Offset;		// channel 1 PIN PA1 dma 3
	ACVol_3[arrayPos] = ((float)ADC_DMA_array[6]*ACVol_3_multi)-ACVol_3_Offset;		// channel 4 PIN PA4 dma 6
	ACCur_1[arrayPos] = ((float)ADC_DMA_array[1]*ACCur_1_multi)-ACCur_1_Offset;		// channel 8 PIN PB0 dma 1
	ACCur_2[arrayPos] = ((float)ADC_DMA_array[4]*ACCur_2_multi)-ACCur_2_Offset;		// channel 10 PIN PC0 dma 4
	ACCur_3[arrayPos] = ((float)ADC_DMA_array[7]*ACCur_3_multi)-ACCur_3_Offset;		// channel 11 PIN PC1 dma 7
	DCVol_1[arrayPos] = ((float)ADC_DMA_array[2]-DCVol_1_Offset)*DCVol_1_multi;		// channel 12 PIN PC12 dma 2
}
