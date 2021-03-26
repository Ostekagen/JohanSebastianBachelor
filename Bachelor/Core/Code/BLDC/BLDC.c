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
//#include "stm32f4xx_hal_tim.h"	//Laver fejl i drivers
#include "BLDC.h"
#include "Ramp.h"
#include "MotorPos.h"
#include "main.h"

/* External Variables */
extern struct ST_MOTORPOS motorpos; // initiating external struct

/* Internal Variables */
float f_dutyCap; // Setting internal variable for dute cycle

/* Start Code Here */
void pfx_BLDC() // Main function for commutation
{
	f_dutyCap = pfx_Ramp(motorpos.uint8_scheme);

	if(motorpos.uint8_scheme == 1) // 6 Commutation Strategy (Outgoing PWM)
		{
			switch(motorpos.uint8_position)
				{
					case 1 : // 30-60 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Full On
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - PWM
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 2 : // 60-90 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Full On
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - PWM
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 3 : // 90-120 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - PWM
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Full On
					 	}
					break;

					case 4 : // 120-150 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - PWM
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Full On
					 	}
					break;

					case 5 : // 150-180 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Full On
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - PWM
					 	}
					break;

					case 6 : // 180-210 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Full On
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - PWM
					 	}
					break;

					case 7 : // 210-240 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Full On
					 		//Timer1Ch2 signal 	- Q3 - PWM
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 8 : // 240-270 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Full On
					 		//Timer1Ch2 signal 	- Q3 - PWM
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 9 : // 270-300 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - PWM
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Full On
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 10 : // 300-330 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - PWM
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Full On
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 11 : // 330-360 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Full On
					 		//Timer1Ch3 signal 	- Q5 - PWM
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 12 : // 0-30 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Full On
					 		//Timer1Ch3 signal 	- Q5 - PWM
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					default :
					{
						//Timer1Ch1 	= 5000;	(Turned off)
						//Timer1Ch1N 	= 5000; (Turned off)
						//Timer1Ch2 	= 5000; (Turned off)
						//Timer1Ch2N 	= 5000; (Turned off)
						//Timer1Ch3 	= 5000; (Turned off)
						//Timer1Ch3N 	= 5000; (Turned off)
					}

				}
		}
	else if(motorpos.uint8_scheme ==2) // 12 Commutation Strategy
		{
			switch(motorpos.uint8_position)
				{
					case 1 : // 30-60 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - PWM
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Full on
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 2 : // 60-90 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Full On
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - PWM
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 3 : // 90-120 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Full On
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - PWM
					 	}
					break;

					case 4 : // 120-150 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - PWM
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Full On
					 	}
					break;

					case 5 : // 150-180 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - PWM
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Full On
					 	}
					break;

					case 6 : // 180-210 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Full On
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - PWM
					 	}
					break;

					case 7 : // 210-240 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - PWM
					 		//Timer1Ch2 signal 	- Q3 - Full On
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 8 : // 240-270 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Full On
					 		//Timer1Ch2 signal 	- Q3 - PWM
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Turned Off
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 9 : // 270-300 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Full On
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - PWM
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 10 : // 300-330 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - PWM
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Turned Off
					 		//Timer1Ch3 signal 	- Q5 - Full On
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 11 : // 330-360 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - PWM
					 		//Timer1Ch3 signal 	- Q5 - Full On
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					case 12 : // 0-30 degrees
					 	{
					 		//Timer1Ch1 signal 	- Q1 - Turned Off
					 		//Timer1Ch1N signal - Q4 - Turned Off
					 		//Timer1Ch2 signal 	- Q3 - Turned Off
					 		//Timer1Ch2N signal - Q6 - Full On
					 		//Timer1Ch3 signal 	- Q5 - PWM
					 		//Timer1Ch3N signal - Q2 - Turned Off
					 	}
					break;

					default :
						{
							//Timer1Ch1 	= 5000; (Turned off)
							//Timer1Ch1N 	= 5000; (Turned off)
							//Timer1Ch2 	= 5000; (Turned off)
							//Timer1Ch2N 	= 5000; (Turned off)
							//Timer1Ch3 	= 5000; (Turned off)
							//Timer1Ch3N 	= 5000; (Turned off)
						}
				}
		}
}

