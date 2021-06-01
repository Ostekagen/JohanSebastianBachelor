/*
 * Ramp.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Rasmus Bank Mikkelsen
 */

/* Includes */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "Throttle.h"
#include "main.h"

/* External Variables */
float f_dutyCapRAMP;
uint16_t uint16_throttleCalcRAMP;

/* Internal Variables */
float f_lastOutput=0.1;
float f_gain1 = 1.00033f;

/* Start Code Here */

// The Ramp function will receive the shecme as input. It will then use the output from throttle to calculate a ramp function
float pfx_ramp()
	{

		uint16_throttleCalcRAMP = pfx_throttle();	// Calling Throttle function

		// Scheme 1
		if ((f_lastOutput == 0) && (uint16_throttleCalcRAMP > 0))	// To ensure the throttle output only is zero when the throttle is not pulled
		{
			f_lastOutput = 0.1;
		}
		if (f_lastOutput < uint16_throttleCalcRAMP)	// When throttle output is higher than our last output, increase our output
		{
			f_lastOutput = f_lastOutput*f_gain1;
		}
		else if (f_lastOutput >= uint16_throttleCalcRAMP)	// When last output is less or equal to the throttle output, set output to throttle output
		{
			f_lastOutput = uint16_throttleCalcRAMP;
		}
		else
		{
			f_lastOutput = 0;
		}


		if (f_dutyCapRAMP > 0.9) // Capping the duty cycle to 0.9
		{
			f_dutyCapRAMP = 0.9;
		}

		return f_dutyCapRAMP;
	}
