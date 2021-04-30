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

/* Timer Handler */
TIM_HandleTypeDef htim1;			// Timer1 Type Def

/* External Variables */
extern uint8_t uint8_position; // initiating external struct

/* Internal Variables */
float f_dutyCap = 0.75; // Setting internal variable for duty cycle - TODO: Remove value after test

/* Start Code Here */
void pfx_BLDC() // Main function for commutation
{
	//f_dutyCap = pfx_ramp(motorpos.uint8_scheme);

	switch(uint8_position)
		{
			case 1 : // 30-90 degrees
				{
					TIM1->CCER &= 0xFBEB; 		// Turn off Q4 & Q3 & Q2
					TIM1->CCER |= 0x141;		// Turn on Q1 & Q6 & Q5
					pfx_PWM(1, 1);				// CH1 - Q1 - Full On
					pfx_PWM(f_dutyCap, 2);		// CH2N - Q6 - PWM
					pfx_PWM(0, 3);				// Channel 3 off
				}
			break;

			case 2 : // 90-150 degrees
				{
					TIM1->CCER &= 0xFEBB; 		// Turn off Q4 & Q3 & Q6 & Q5
					TIM1->CCER |= 0x411;		// Turn on Q1 & Q2
					pfx_PWM(f_dutyCap, 1);		// CH1 - Q1 - PWM
					pfx_PWM(1, 3); 				// CH3N - Q2 - Full On
					pfx_PWM(0, 2);				// Channel 2 off
				}
			break;

			case 3 : // 150-210 degrees
				{
					TIM1->CCER &= 0xFEBB;	 	// Turn off Q1 & Q4 & Q6 & Q5
					TIM1->CCER |= 0x411;		// Turn on Q3 & Q2
					pfx_PWM(1, 2);				// CH2 - Q3 - Full On
					pfx_PWM(f_dutyCap, 3);		// CH3N - Q2 - PWM
					pfx_PWM(0, 1);				// Channel 1 off
				}
			break;

			case 4 : // 210-270 degrees
				{
					TIM1->CCER &= 0xFBBE; 		// Turn off Q1 & Q6 & Q5 & Q2
					TIM1->CCER |= 0x114;		// Turn on Q4 & Q3
					pfx_PWM(1, 1);				// CH1N - Q4 - Full On
					pfx_PWM(f_dutyCap, 2);		// CH2 - Q3 - PWM
					pfx_PWM(0, 3);				// Channel 3 off
				}
			break;

			case 5 : // 270-330 degrees
				{
					TIM1->CCER &= 0xFBBE;	 	// Turn off Q1 & Q3 & Q6 & Q2
					TIM1->CCER |= 0x114;		// Turn on Q4 & Q5
					pfx_PWM(f_dutyCap, 1);		// CH1N - Q4 - PWM
					pfx_PWM(1, 3);				// CH3 - Q5 - Full On
					pfx_PWM(0, 2);				// Channel 2 off
				}
			break;

			case 6 : // 330-30 degrees
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

