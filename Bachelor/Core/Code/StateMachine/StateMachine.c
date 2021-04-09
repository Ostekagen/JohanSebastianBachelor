
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
extern struct ST_MOTORPOS motorpos; // initiating external struct

/* Internal Variables */
int8_t State = 0;

/* Start Code here */
void pfx_stateInterruptFunction()
	{
		pfx_getMeasurement();
		pfx_MotorPos();

		switch(State)
				{
					case 0 : // Standby Mode
					 	{
					 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 1);
					 		pfx_PWM_Stop();	// PWM STOP
					 		if (pfx_error() != 0)
					 		 	{
					 		 		State = 2;
					 		 	}
					 		else if (pfx_brake() != 0)
					 			{
					 				State = 0;
					 			}
					 		else if (pfx_throttle() > 100) // TODO: Find correct value
					 			{
					 				State = 1;
					 			}
					 		else
					 			{

					 			}
					 	}

					break;

					case 1 : // Manual Mode
						{
							if (pfx_error() != 0)
					 		 	{
					 		 		State = 2;
					 		 	}
							else if (pfx_brake() !=0)
								{
									State = 0;
								}
							else
								{
									pfx_BLDC();
									HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 1);
								}
						}

					break;

					case 2 : // Error Mode
						{
							TIM1->CCER &= 0xFAAA;	// Sluk alle MOSFET
							pfx_PWM_Stop();			// Stop The PWM
							HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
							if (pfx_error() == 0)
								{
									State = 0;
								}
						}

					break;

					default :
						{
							State = 2;
						}

				}
	}




