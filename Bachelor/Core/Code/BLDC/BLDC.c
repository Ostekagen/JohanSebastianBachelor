/*
 * BLDC.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

/* Includes */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "PWM.h"
#include "Ramp.h"
#include "MotorPos.h"
#include "main.h"

TIM_HandleTypeDef htim1;			// Timer1 Type Def
TIM_OC_InitTypeDef sConfigOC;		// Initiate Timer1

/* External Variables */
extern struct ST_MOTORPOS motorpos; // initiating external struct

/* Internal Variables */
float f_dutyCap; // Setting internal variable for duty cycle - TODO: Remove value after test

/* Start Code Here */
void pfx_BLDC() // Main function for commutation
{
	f_dutyCap = pfx_ramp(motorpos.uint8_scheme);

	if(motorpos.uint8_scheme == 1) // 6 Commutation Strategy (Outgoing PWM)
		{
			switch(motorpos.uint8_position)
				{
					case 1 : // 30-60 degrees
					 	{
					 		TIM1->CCER &= 0xFBEB; 			// Turn off Q4 & Q3 & Q2
					 		TIM1->CCER |= 0x11;				// Turn on Q1 & Q6 & Q5
					 		pfx_PWM(1, 1);					// CH1 - Q1 - Full On
					 		pfx_PWM((1-f_dutyCap), 2);		// CH2N - Q6 - PWM
					 		pfx_PWM(0, 3);					// Channel 3 off
					 	}
					break;

					case 2 : // 60-90 degrees
						{
							TIM1->CCER &= 0xFBEB; 			// Turn off Q4 & Q3 & Q2
							TIM1->CCER |= 0x11;				// Turn on Q1 & Q6 & Q5
							pfx_PWM(1, 1);					// CH1 - Q1 - Full On
							pfx_PWM((1-f_dutyCap), 2);		// CH2N - Q6 - PWM
							pfx_PWM(0, 3);					// Channel 3 off
						}
					break;

					case 3 : // 90-120 degrees
					 	{
					 		TIM1->CCER &= 0xFEBB; 		// Turn off Q4 & Q3 & Q6 & Q5
					 		TIM1->CCER |= 0x411;		// Turn on Q1 & Q2
					 		pfx_PWM(f_dutyCap, 1);		// CH1 - Q1 - PWM
					 		pfx_PWM(1, 3); 				// CH3N - Q2 - Full On
					 		pfx_PWM(0, 2);				// Channel 2 off
					 	}
					break;

					case 4 : // 120-150 degrees
				 		{
				 			TIM1->CCER &= 0xFEBB;	 	// Turn off Q4 & Q3 & Q6 & Q5
				 			TIM1->CCER |= 0x411;		// Turn on Q1 & Q2
				 			pfx_PWM(f_dutyCap, 1);		// CH1 - Q1 - PWM
				 			pfx_PWM(1, 3); 				// CH3N - Q2 - Full On
				 			pfx_PWM(0, 2);				// Channel 2 off
				 		}
					break;

					case 5 : // 150-180 degrees
					 	{
					 		TIM1->CCER &= 0xFEBB;	 	// Turn off Q1 & Q4 & Q6 & Q5
					 		TIM1->CCER |= 0x411;		// Turn on Q3 & Q2
					 		pfx_PWM(1, 2);				// CH2 - Q3 - Full On
					 		pfx_PWM((1-f_dutyCap), 3);	// CH3N - Q2 - PWM
					 		pfx_PWM(0, 1);				// Channel 1 off
					 	}
					break;

					case 6 : // 180-210 degrees
					 	{
					 		TIM1->CCER &= 0xFEBB;	 	// Turn off Q1 & Q4 & Q6 & Q5
					 		TIM1->CCER |= 0x411;		// Turn on Q3 & Q2
					 		pfx_PWM(1, 2);				// CH2 - Q3 - Full On
					 		pfx_PWM((1-f_dutyCap), 3);	// CH3N - Q2 - PWM
					 		pfx_PWM(0, 1);				// Channel 1 off
					 	}
					break;

					case 7 : // 210-240 degrees
					 	{
					 		TIM1->CCER &= 0xFBBE; 		// Turn off Q1 & Q6 & Q5 & Q2
					 		TIM1->CCER |= 0x114;		// Turn on Q4 & Q3
					 		pfx_PWM(1, 1);				// CH1N - Q4 - Full On
					 		pfx_PWM(f_dutyCap, 2);		// CH2 - Q3 - PWM
					 		pfx_PWM(0, 3);				// Channel 3 off
					 	}
					break;

					case 8 : // 240-270 degrees
					 	{
					 		TIM1->CCER &= 0xFBBE; 		// Turn off Q1 & Q6 & Q5 & Q2
					 		TIM1->CCER |= 0x114;		// Turn on Q4 & Q3
					 		pfx_PWM(1, 1);				// CH1N - Q4 - Full On
					 		pfx_PWM(f_dutyCap, 2);		// CH2 - Q3 - PWM
					 		pfx_PWM(0, 3);				// Channel 3 off
					 	}
					break;

					case 9 : // 270-300 degrees
					 	{
					 		TIM1->CCER &= 0xFBBE;	 	// Turn off Q1 & Q3 & Q6 & Q2
					 		TIM1->CCER |= 0x114;		// Turn on Q4 & Q5
					 		pfx_PWM((1-f_dutyCap), 1);	// CH1N - Q4 - PWM
					 		pfx_PWM(1, 3);				// CH3 - Q5 - Full On
					 		pfx_PWM(0, 2);				// Channel 2 off
					 	}
					break;

					case 10 : // 300-330 degrees
					 	{
					 		TIM1->CCER &= 0xFBBE;	 	// Turn off Q1 & Q3 & Q6 & Q2
					 		TIM1->CCER |= 0x114;		// Turn on Q4 & Q5
					 		pfx_PWM((1-f_dutyCap), 1);	// CH1N - Q4 - PWM
					 		pfx_PWM(1, 3);				// CH3 - Q5 - Full On
					 		pfx_PWM(0, 2);				// Channel 2 off
					 	}
					break;

					case 11 : // 330-360 degrees
					 	{
					 		TIM1->CCER &= 0xFBEB; 		// Turn off Q1 & Q4 & Q3 & Q2
					 		TIM1->CCER |= 0x141;		// Turn on Q6 & Q5
					 		pfx_PWM(1, 2);				// CH2N - Q6 - Full On
					 		pfx_PWM(f_dutyCap, 3);		// CH3 - Q5 - PWM
					 		pfx_PWM(0, 1);				// Channel 1 off
					 	}
					break;

					case 12 : // 0-30 degrees
					 	{
					 		TIM1->CCER &= 0xFBEB; 		// Turn off Q1 & Q4 & Q3 & Q2
					 		TIM1->CCER |= 0x141;		// Turn on Q6 & Q5
					 		pfx_PWM(1, 2);				// CH2N - Q6 - Full On
					 		pfx_PWM(f_dutyCap, 3);		// CH3 - Q5 - PWM
					 		pfx_PWM(0, 1);				// Channel 1 off
					 	}
					break;

					default :
						{
							TIM1->CCER &= 0xFAAA; 		// Turn off Q1 & Q4 & Q3 & Q6 & Q5 & Q2
							pfx_PWM_Stop();				// Turn off all PWM by applying compare value larger than counter
						}

				}
		}
	else if(motorpos.uint8_scheme ==2) // 12 Commutation Strategy (PWM_On_PWM)
		{
			switch(motorpos.uint8_position)
				{
					case 1 : // 30-60 degrees
					 	{
					 		TIM1->CCER &= 0xFAEB; 	// Turn off Q4 & Q3 & Q5 & Q2
					 		TIM1->CCER |= 0x41;		// Turn on Q1 & Q6
					 		pfx_PWM(f_dutyCap, 1);	// CH1 - Q1 - PWM
					 		pfx_PWM(1, 2);			// CH2N - Q6 - Full on
					 	}
					break;

					case 2 : // 60-90 degrees
					 	{
					 		TIM1->CCER &= 0xFAEB; 	// Turn off Q4 & Q3 & Q5 & Q2
					 		TIM1->CCER |= 0x41;		// Turn on Q1 & Q6
					 		pfx_PWM(1, 1);			// CH1 - Q1 - Full On
					 		pfx_PWM(f_dutyCap, 2);	// CH2N - Q6 - PWM
					 	}
					break;

					case 3 : // 90-120 degrees
					 	{
					 		TIM1->CCER &= 0xFEAB; 	// Turn off Q4 & Q3 & Q6 & Q5
					 		TIM1->CCER |= 0x401;	// Turn on Q1 & Q2
					 		pfx_PWM(1, 1);			// CH1 - Q1 - Full On
					 		pfx_PWM(f_dutyCap, 3);	// CH3N - Q2 - PWM
					 	}
					break;

					case 4 : // 120-150 degrees
					 	{
					 		TIM1->CCER &= 0xFEAB; 	// Turn off Q4 & Q3 & Q6 & Q5
					 		TIM1->CCER |= 0x401;	// Turn on Q1 & Q2
					 		pfx_PWM(f_dutyCap, 1);	// CH1 - Q1 - PWM
					 		pfx_PWM(1, 3);			// CH3N - Q2 - Full On
					 	}
					break;

					case 5 : // 150-180 degrees
					 	{
					 		TIM1->CCER &= 0xFEBA; 	// Turn off Q1 & Q4 & Q6 & Q5
					 		TIM1->CCER |= 0x410;	// Turn on Q3 & Q2
					 		pfx_PWM(f_dutyCap, 2);	// CH2 - Q3 - PWM
					 		pfx_PWM(1, 3);			// CH3N - Q2 - Full On
					 	}
					break;

					case 6 : // 180-210 degrees
					 	{
					 		TIM1->CCER &= 0xFEBA; 	// Turn off Q1 & Q4 & Q6 & Q5
					 		TIM1->CCER |= 0x410;	// Turn on Q3 & Q2
					 		pfx_PWM(1, 2);			// CH2 - Q3 - Full On
					 		pfx_PWM(f_dutyCap, 3);	// CH3N - Q2 - PWM
					 	}
					break;

					case 7 : // 210-240 degrees
					 	{
					 		TIM1->CCER &= 0xFABE; 	// Turn off Q1 & Q6 & Q5 & Q2
					 		TIM1->CCER |= 0x14;		// Turn on Q4 & Q3
					 		pfx_PWM(f_dutyCap, 1);	// CH1N - Q4 - PWM
					 		pfx_PWM(1, 2);			// CH2 - Q3 - Full On
					 	}
					break;

					case 8 : // 240-270 degrees
					 	{
					 		TIM1->CCER &= 0xFABE; 	// Turn off Q1 & Q6 & Q5 & Q2
					 		TIM1->CCER |= 0x14;		// Turn on Q4 & Q3
					 		pfx_PWM(1, 1);			// CH1N - Q4 - Full On
					 		pfx_PWM(f_dutyCap, 2);	// CH2 - Q3 - PWM
					 	}
					break;

					case 9 : // 270-300 degrees
					 	{
					 		TIM1->CCER &= 0xFBAE; 	// Turn off Q1 & Q3 & Q6 & Q2
					 		TIM1->CCER |= 0x104;	// Turn on Q4 & Q5
					 		pfx_PWM(1, 1);			// CH1N - Q4 - Full On
					 		pfx_PWM(f_dutyCap, 3);	// CH3 - Q5 - PWM
					 	}
					break;

					case 10 : // 300-330 degrees
					 	{
					 		TIM1->CCER &= 0xFABE; 	// Turn off Q1 & Q3 & Q6 & Q2
					 		TIM1->CCER |= 0x104;	// Turn on Q4 & Q5
					 		pfx_PWM(f_dutyCap, 1);	// CH1N - Q4 - PWM
					 		pfx_PWM(1, 3);			// CH3 - Q5 - Full On
					 	}
					break;

					case 11 : // 330-360 degrees
					 	{
					 		TIM1->CCER &= 0xFBEA; 	// Turn off Q1 & Q4 & Q3 & Q2
					 		TIM1->CCER |= 0x140;	// Turn on Q6 & Q5
					 		pfx_PWM(f_dutyCap, 2);	// CH2N - Q6 - PWM
					 		pfx_PWM(1, 3);			// CH3 - Q5 - Full On
					 	}
					break;

					case 12 : // 0-30 degrees
					 	{
					 		TIM1->CCER &= 0xFBEA; 	// Turn off Q1 & Q4 & Q3 & Q2
					 		TIM1->CCER |= 0x140;	// Turn on Q6 & Q5
					 		pfx_PWM(1, 2);			// CH2N - Q6 - Full On
					 		pfx_PWM(f_dutyCap, 3);	// CH3 - Q5 - PWM
					 	}
					break;

					default : // Turn off PWM
						{
							TIM1->CCER &= 0xFAAA; 		// Turn off Q1 & Q4 & Q3 & Q6 & Q5 & Q2
							pfx_PWM_Stop();				// Turn off all PWM by applying compare value larger than counter
						}
				}
		}
}

