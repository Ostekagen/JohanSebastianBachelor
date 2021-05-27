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
extern int8_t int8_stateCounter; //
/* Internal Variables */
float f_dutyCap; // Setting internal variable for duty cycle - TODO: Remove value after test

/* Start Code Here */
void pfx_BLDC(int8_t int8_state,uint8_t uint8_pos) // Main function for commutation
{
	if(int8_state == 1)	// Check for Drive Mode
		{
			f_dutyCap = pfx_ramp(); // Manual Mode Duty Cycle
		}
	if(int8_state == 4)	// Check for Drive Mode
		{
//			f_dutyCap = pfx_currentControl(int8_stateCounter); // Auto Pilot Duty Cycle
		}

	switch(uint8_pos)
		{
			case 1 : // 30-90 degrees
				{
					pfx_PWM(0, 3);				// Channel 3 off
					TIM1->CCER &= 0xFBEB; 		// Turn off Q4 & Q3 & Q2
					TIM1->CCER |= 0x141;		// Turn on Q1 & Q6 & Q5
					pfx_PWM(f_dutyCap, 1);		// CH1 - Q1 - PWM
					pfx_PWM(1, 2);				// CH2N - Q6 - Full On
				}
			break;
			case 2 : // 90-150 degrees
				{
					pfx_PWM(0, 2);				// Channel 2 off
					TIM1->CCER &= 0xFEBB; 		// Turn off Q4 & Q6 & Q5
					TIM1->CCER |= 0x411;		// Turn on Q1 & Q2 & Q3
					pfx_PWM(f_dutyCap, 1);		// CH1 - Q1 - PWM
					pfx_PWM(1, 3); 				// CH3N - Q2 - Full On
				}
			break;
			case 3 : // 150-210 degrees
				{
					pfx_PWM(0, 1);				// Channel 1 off
					TIM1->CCER &= 0xFEBB;	 	// Turn off Q4 & Q6 & Q5
					TIM1->CCER |= 0x411;		// Turn on Q3 & Q2 & Q1
					pfx_PWM(f_dutyCap, 2);		// CH2 - Q3 - PWM
					pfx_PWM(1, 3);				// CH3N - Q2 - Full on
				}
			break;
			case 4 : // 210-270 degrees
				{
					pfx_PWM(0, 3);				// Channel 3 off
					TIM1->CCER &= 0xFBBE; 		// Turn off Q1 & Q6 & Q2
					TIM1->CCER |= 0x114;		// Turn on Q4 & Q3 & Q5
					pfx_PWM(1, 1);				// CH1N - Q4 - Full On
					pfx_PWM(f_dutyCap, 2);		// CH2 - Q3 - PWM
				}
			break;
			case 5 : // 270-330 degrees
				{
					pfx_PWM(0, 2);				// Channel 2 off
					TIM1->CCER &= 0xFBBE;	 	// Turn off Q1 & Q6 & Q2
					TIM1->CCER |= 0x114;		// Turn on Q4 & Q5 & Q3
					pfx_PWM(1, 1);				// CH1N - Q4 - Full On
					pfx_PWM(f_dutyCap, 3);		// CH3 - Q5 - PWM
				}
			break;
			case 6 : // 330-30 degrees
				{
					pfx_PWM(0, 1);				// Channel 1 off
					TIM1->CCER &= 0xFBEB; 		// Turn off Q4 & Q3 & Q2
					TIM1->CCER |= 0x141;		// Turn on Q6 & Q5 & Q1
					pfx_PWM(1, 2);				// CH2N - Q6 - Full On
					pfx_PWM(f_dutyCap, 3);		// CH3 - Q5 - PWM
				}
			break;
			case 7 : // PWM Stop
				{
					TIM1->CCER &= 0xFBBB; 		// Turn off Q2 & Q4 & Q6
					TIM1->CCER |= 0x111;		// Turn on Q1 & Q3 & Q5
					pfx_PWM_Stop();				// Stop all PWM
				}
			break;
			default :
				{
					TIM1->CCER &= 0xFBBB; 		// Turn off Q2 & Q4 & Q6
					TIM1->CCER |= 0x111;		// Turn on Q1 & Q3 & Q5
					pfx_PWM_Stop();				// Stop all PWM
				}
		}
}
