/*
 * Ramp.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

/* Includes */
#include <math.h>
#include <math.h>
#include "stdio.h"
#include <stdint.h>
#include "BLDC.h"
#include "Ramp.h"
#include "throttle.h"
#include "MotorPos.h"
#include "main.h"

/* External Variables */
float f_dutyCap;
uint8_t uint8_throttleOutput;

/* Internal Variables */
float f_lastOutput;
float f_gain1 = 0.0001f;
float f_gain2 = 0.000;

/* Start Code Here */

float pfx_ramp(int8_t int8_scheme)
	{
		uint8_throttleOutput = pfx_throttle();
		if(int8_scheme = 1 && pfx_throtte != 0)
			{

			}



		return f_dutyCap;
	}
