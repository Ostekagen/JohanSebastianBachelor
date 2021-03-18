/*
 * ADC_Measurements.h
 *
 *  Created on: Nov 11, 2019
 *      Author: janms
 */

#ifndef ADC_MEASUREMENTS_H_
#define ADC_MEASUREMENTS_H_

extern int arrayPos;
extern float ACCur_1_Offset;
extern float ACCur_2_Offset;
extern float ACCur_3_Offset;
extern float ACVol_1_Offset;
extern float ACVol_2_Offset;
extern float ACVol_3_Offset;
extern float DCVol_1_Offset;

void getMeasurement();
void getOffset(float OffV1,float OffV2,float OffV3,float OffC1,float OffC2,float OffC3);
void setupMeasurement();
#endif /* ADC_MEASUREMENTS_H_ */
