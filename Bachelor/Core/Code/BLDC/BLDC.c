/*
 * BLDC.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */


/* Includes */
#include <math.h>
#include <math.h>
#include "stdio.h"
#include <stdint.h>
#include "stm32f4xx_hal_tim.h"
#include "BLDC.h"
#include "Ramp.h"
#include "MotorPos.h"
#include "main.h"

/* External Variables */
extern struct ST_MOTORPOS motorpos; // initiating external struct

/* Internal Variables */
float f_dutyCap; // Setting internal variable for dute cycle

/* Start Code here */
void pfx_BLDC() // Main function for commutation
{
	f_dutyCap = pfx_Ramp(motorpos.uint8_scheme);

	if(motorpos.uint8_scheme == 1) // 6 Commutation Strategy
		{
			switch(motorpos.uint8_position)
				{
					case 1 : // 30-60 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 2 : // 60-90 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 3 : // 90-120 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 4 : // 120-150 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 5 : // 150-180 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 6 : // 180-210 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 7 : // 210-240 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 8 : // 240-270 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 9 : // 270-300 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 10 : // 300-330 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 11 : // 330-360 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 12 : // 0-30 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					default :
							//Timer1Ch1 = 5000; (Turned off)
							//Timer1Ch1N = 5000; (Turned off)
							//Timer1Ch2 = 5000; (Turned off)
							//Timer1Ch2N = 5000; (Turned off)
							//Timer1Ch3 = 5000; (Turned off)
							//Timer1Ch3N = 5000; (Turned off)
				}
		}
	else if(motorpos.uint8_scheme ==2) // 12 Commutation Strategy
		{
			switch(motorpos.uint8_position)
				{
					case 1 : // 30-60 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 2 : // 60-90 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 3 : // 90-120 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 4 : // 120-150 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 5 : // 150-180 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 6 : // 180-210 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 7 : // 210-240 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 8 : // 240-270 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 9 : // 270-300 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 10 : // 300-330 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 11 : // 330-360 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					case 12 : // 0-30 degrees
					 	{
					 		//Timer1Ch1 signal -
					 		//Timer1Ch1N signal -
					 		//Timer1Ch2 signal -
					 		//Timer1Ch2N signal -
					 		//Timer1Ch3 signal -
					 		//Timer1Ch3N signal -
					 	}
					break;

					default :
							//Timer1Ch1 = 5000; (Turned off)
							//Timer1Ch1N = 5000; (Turned off)
							//Timer1Ch2 = 5000; (Turned off)
							//Timer1Ch2N = 5000; (Turned off)
							//Timer1Ch3 = 5000; (Turned off)
							//Timer1Ch3N = 5000; (Turned off)
				}
		}
}
