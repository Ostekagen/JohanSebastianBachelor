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
int8_t int8_state = 3;			// Initiating State to 3 (Init State)
int16_t int16_initCount = 0;	// Initiating Start-Up counter to 0
int8_t int8_stateCounter;

/* Start Code here */
void pfx_stateInterruptFunction()
	{
		pfx_getMeasurement();	// Get measurements
		pfx_MotorPos();			// Update motor position
		if(pfx_error() == 0)	// Check for error
			{
				if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) != 0 ) // Check Power Switch (Power on)
					{
			 			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1); // Turn on Q7
			 			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1); // Turn on LED
					}
				if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == 0) // Check Power Switch (Power off)
					{
			 			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0); // Turn off Q7
			 			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0); // Turn off LED
					}
			}
		switch(int8_state)
				{
					case 0 : // Standby Mode
					 	{
					 		pfx_BLDC(1,7);	// Sluk Mosfets og stop PWM
					 		int8_stateCounter = 0;
					 		if (pfx_error() != 0) 			// System error activated
					 		 	{
					 		 		int8_state = 2;				// Set to error state
					 		 	}
					 		else if (pfx_brake() != 0)		// System brake activated
					 			{
					 				int8_state = 0;				// Set to standby state
					 			}
					 		else if (pfx_throttle() > 100 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) != 0)
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
							else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
								{
									int8_state = 4;
								}
							else
								{
									pfx_BLDC(int8_state,uint8_position);				// Commutate with BLDC function
									int8_stateCounter = 1;
								}
						}

					break;

					case 2 : // Error Mode
						{
							pfx_BLDC(1,7);	// Sluk Mosfets og stop PWM
							int8_stateCounter = 2;
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0); // Turn off Q7
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0); // Turn off LED
							if(pfx_error() == 0 && int16_initCount < 2250)	// System error reset (initiation error)
								{
									int16_initCount = 0;	// Reset init counter
									int8_state = 3;			// Set to initiation state
								}
							else if (pfx_error() == 0)	// System error reset
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
									int8_stateCounter = 3;
								}
							else if(int16_initCount == 2250)			// Enter Standby Mode after 2250 counts (0.15 seconds)
								{
									int8_state = 0;
								}
							int16_initCount++;
						}

					break;

					case 4 :
						{
							if (pfx_error() != 0)			// System error activated
								{
									int8_state = 2;				// Set to error state
								}
							else if (pfx_brake() !=0)		// System brake activated
								{
									int8_state = 0;				// Set to standby state
								}
							else if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 0)
								{
									int8_state = 1;
								}
							else
								{
									pfx_BLDC(int8_state,uint8_position);
									int8_stateCounter=4;
								}
						}
					break;

					default :
						{
							int8_state = 2;				// default setting is error state
						}
				}
	}
