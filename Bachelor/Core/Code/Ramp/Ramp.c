/*
 * Ramp.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
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
uint8_t uint8_throttleOutput;

/* Internal Variables */
int counter;
float f_lastOutput;
float f_gain1 = 0.00033f;
float f_gain2 = 0.001;

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
		return f_dutyCap;
	}
