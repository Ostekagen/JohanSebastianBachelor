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
float f_dutyCapRAMP;
uint16_t int16_throttleCalcRAMP;

/* Internal Variables */
int counter;
float f_lastOutput=0.1;
float f_gain1 = 1.00033f;
float f_gain2 = 1.001;
uint16_t throttleTest;
float John;

/* Start Code Here */

// The Ramp function will receive the shecme as input. It will then use the output from throttle to calculate a ramp function
float pfx_ramp(uint8_t uint8_scheme)
	{

		int16_throttleCalcRAMP = pfx_throttle();	// Calling Throttle function

		// Scheme 1
		if(uint8_scheme == 1)
		{
			if ((f_lastOutput == 0) && (int16_throttleCalcRAMP > 0))	// To ensure the throttle output only is zero when the throttle is not pulled
			{
				f_lastOutput = 0.1;
			}
			if (f_lastOutput < int16_throttleCalcRAMP)	// When throttle output is higher than our last output, increase our output
			{
				f_lastOutput = f_lastOutput*f_gain1;
			}
			else if (f_lastOutput >= int16_throttleCalcRAMP)	// When last output is less or equal to the throttle output, set output to throttle output
			{
				f_lastOutput = int16_throttleCalcRAMP;
			}
			else
			{
				f_lastOutput = 0;
			}
		}

		// Scheme 2
		else if (uint8_scheme == 2)
		{
			if (f_lastOutput < int16_throttleCalcRAMP)
			{
				f_lastOutput = f_lastOutput*f_gain2;
			}
			else if (f_lastOutput >= int16_throttleCalcRAMP)
			{
				f_lastOutput = int16_throttleCalcRAMP;
			}
			else
			{
				f_lastOutput = 0;
			}
		}
		else
		{
			f_lastOutput = 0;
		}
		John = pfx_throttle();
		f_dutyCapRAMP = John/1000;	// set our output to a value between 0 and 1

		if (f_dutyCapRAMP > 0.95)
			{
				f_dutyCapRAMP = 0.9;
			}

		return f_dutyCapRAMP;
	}
