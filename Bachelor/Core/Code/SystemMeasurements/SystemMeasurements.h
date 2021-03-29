/*
 * ADC_Measurements.h
 *
 *  Created on: 26/03 2021
 *      Author: Rasmus Bank Mikkelsen
 */

#ifndef ADC_MEASUREMENTS_H_
#define ADC_MEASUREMENTS_H_

extern int arrayPos;

void pfx_getMeasurement();
void pfx_setupMeasurement();
struct SYSMEAS{int16_t int16_batteryVol;int16_t int16_hallValue;int16_t motorVolValue;}systemmeasurements;
#endif /* ADC_MEASUREMENTS_H_ */
