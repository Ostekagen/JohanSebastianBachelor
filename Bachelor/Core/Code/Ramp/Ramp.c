/*
 * Ramp.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Rasmus Bank Mikkelsen
 */

/* Includes */
#include <math.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "BLDC.h"
#include "Ramp.h"
#include "Throttle.h"
#include "MotorPos.h"
#include "main.h"

/* External Variables */
float f_dutyCap;
uint8_t int16_throttleCalc;

/* Internal Variables */
int counter;
float f_lastOutput = 0.1;
float f_gain1 = 1.00033f;
float f_gain2 = 1.001;

/* Start Code Here */

float pfx_ramp(uint8_t uint8_scheme)
	{
		/*uint8_throttleOutput = pfx_Throttle();
		if(uint8_scheme == 1 && pfx_Throttle() != 0)
			{
				if(counter == 0)
					{
						f_dutycap = (uint8_throttleOutput * f_gain1)/100.0;
						counter++;
					}
				if(counter > 0)
					{

					}
				uint8_throttleOutput
				//f_lastOutput;
			}


*/

		int16_throttleCalc = pfx_throttle();
		if(uint8_scheme == 1)
		{
			if ((f_lastOutput == 0) && (int16_throttleCalc > 0))
			{
				f_lastOutput = 0.1;
			}
			if (f_lastOutput < int16_throttleCalc)
			{
				f_lastOutput = f_lastOutput*f_gain1;
			}
			else if (f_lastOutput >= int16_throttleCalc)
			{
				f_lastOutput = int16_throttleCalc;
			}
		}
		else if (uint8_scheme == 2)
		{
			if (f_lastOutput < int16_throttleCalc)
			{
				f_lastOutput = f_lastOutput*f_gain2;	// Skal være anderledes end den anden
			}
			else if (f_lastOutput >= int16_throttleCalc)
			{
				f_lastOutput = int16_throttleCalc;
			}
		}

		f_dutyCap = f_lastOutput/1000;

		return f_dutyCap;
	}
