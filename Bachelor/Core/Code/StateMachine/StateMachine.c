
/*
 * StateMachine.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "MotorPos.h"
#include "Throttle.h"
#include "Error.h"
#include "Brake.h"
#include "SystemMeasurements.h"
#include "BLDC.h"
#include "PWM.h"

TIM_HandleTypeDef htim1;
TIM_OC_InitTypeDef sConfigOC;

/* External Variables */
extern struct ST_MOTORPOS motorpos; // Initiating external struct

/* Internal Variables */
int8_t State = 3;		// Initiating State to 3 (Init State)
int8_t InitCount = 0;	// Initiating Start-Up counter to 0


/* Start Code here */
void pfx_stateInterruptFunction()
	{
		pfx_getMeasurement();	// Get measurements
		pfx_MotorPos();			// Update motor position

		switch(State)
				{
					case 0 : // Standby Mode
					 	{
					 		pfx_PWM_Stop();	// PWM STOP
					 		if (pfx_error() != 0) 			// System error activated
					 		 	{
					 		 		State = 2;				// Set to error state
					 		 	}
					 		else if (pfx_brake() != 0)		// System brake activated
					 			{
					 				State = 0;				// Set to standby state
					 			}
					 		else if (pfx_throttle() > 100) 	// TODO: Find correct value // Throttle activated
					 			{
					 				State = 1;				// Set to manual state
					 			}
						}

					break;

					case 1 : // Manual Mode
						{
							if (pfx_error() != 0)			// System error activated
					 		 	{
					 		 		State = 2;				// Set to error state
					 		 	}
							else if (pfx_brake() !=0)		// System brake activated
								{
									State = 0;				// Set to standby state
								}
							else
								{
									pfx_BLDC();				// Commutate with BLDC function
								}
						}

					break;

					case 2 : // Error Mode
						{
							TIM1->CCER &= 0xFAAA;	// Sluk alle MOSFET
							pfx_PWM_Stop();			// Stop The PWM
							if (pfx_error() == 0)	// System error reset
								{
									State = 0;		// Set to standby state
								}
						}

					break;

					case 3 : // Initiation State
						{
							if(InitCount == 0)				// Setting up charge up of Boot Capacitor
								{
									TIM1->CCER &= 0xFEEE; 	// Turn off High Channels
									TIM1->CCER |= 0x444;	// Turn on Low Channels
									pfx_PWM(1, 1);			// Full signal on CH1N
									pfx_PWM(1, 2);			// Full signal on CH2N
									pfx_PWM(1, 3);			// Full signal on CH3N
								}
							if(InitCount == 2000)			// Enter Standby Mode after 2000 counts (0.15 seconds)
								{
									State = 0;
								}
							InitCount++;
						}

					break;

					default :
						{
							State = 2;				// default setting is error state
						}

				}
	}
