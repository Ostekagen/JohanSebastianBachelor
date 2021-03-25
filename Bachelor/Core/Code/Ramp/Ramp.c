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
#include "MotorPos.h"
#include "main.h"

/* External Variables */
float f_dutyCap;
uint8_t uint8_throttleOutput;

/* Internal Variables */
float f_lastOutput;
int16_t int16_gain1;
int16_t int16_gain2;

/* Start Code Here */

float pfx_ramp(int8_t int8_scheme)
	{


		return f_dutyCap;
	}
