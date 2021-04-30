
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

/* Timer Handler */
TIM_HandleTypeDef htim1;

/* External Variables */

/* Internal Variables */
int8_t int8_state = 3;		// Initiating State to 3 (Init State)
int16_t int16_initCount = 0;	// Initiating Start-Up counter to 0


/* Start Code here */
void pfx_stateInterruptFunction()
	{
		pfx_getMeasurement();	// Get measurements
		pfx_MotorPos();			// Update motor position

		switch(int8_state)
				{
					case 0 : // Standby Mode
					 	{
					 		pfx_PWM_Stop();	// PWM STOP
					 		if (pfx_error() != 0) 			// System error activated
					 		 	{
					 		 		int8_state = 2;				// Set to error state
					 		 	}
					 		else if (pfx_brake() != 0)		// System brake activated
					 			{
					 				int8_state = 0;				// Set to standby state
					 			}
					 		else if (pfx_throttle() > 100) 	// TODO: Find correct value // Throttle activated
					 			{
					 				int8_state = 1;				// Set to manual state
					 			}
						}

					break;

					case 1 : // Manual Mode
						{
							if (pfx_error() != 0)			// System error activated
					 		 	{
					 		 		int8_state = 2;				// Set to error state
					 		 	}
							else if (pfx_brake() !=0)		// System brake activated
								{
									int8_state = 0;				// Set to standby state
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
									int8_state = 0;		// Set to standby state
								}
						}

					break;

					case 3 : // Initiation State
						{
							if (pfx_error() != 0) 			// System error activated
								{
									int8_state = 2;			// Set to error state
								}
							else if(int16_initCount == 0)		// Setting up charge up of Boot Capacitor
								{
									TIM1->CCER &= 0xFEEE; 	// Turn off High Channels
									TIM1->CCER |= 0x444;	// Turn on Low Channels
									pfx_PWM(1, 1);			// Full signal on CH1N
									pfx_PWM(1, 2);			// Full signal on CH2N
									pfx_PWM(1, 3);			// Full signal on CH3N
								}
							else if(int16_initCount == 2000)			// Enter Standby Mode after 2000 counts (0.15 seconds)
								{
									int8_state = 0;
								}
							else
								{
									int16_initCount++;
								}
						}


					break;

					default :
						{
							int8_state = 2;				// default setting is error state
						}

				}
	}
