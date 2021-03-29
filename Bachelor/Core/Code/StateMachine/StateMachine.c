
/*
 * StateMachine.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

/* Includes */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "MotorPos.h"
#include "Throttle.h"
#include "Error.h"
#include "Brake.h"
#include "SystemMeasurements.h"

/* External Variables */
extern struct ST_MOTORPOS motorpos; // calling external struct

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
					 		// PWM STOP
					 		if (pfx_error() != 0)
					 		 	{
					 		 		State = 2;
					 		 	}
					 		else if (pfx_brake() != 0)
					 			{
					 				State = 0;
					 			}
					 		else if (pfx_throttle() > 1200) // 1200 er en ca værdi for hvornår throttle er aktiveret. Den skal præciseres
					 			{
					 				State = 1;
					 			}
					 	}

					break;

					case 1 : // Manual Mode
						{
							if (pfx_error() != 0)
					 		 	{
					 		 		State = 2;
					 		 	}
							if (pfx_brake() !=0)
								{
									State = 0;
								}
					 		pfx_BLDC();
						}

					break;

					case 2 : // Error Mode
						{
							// Sluk alle MOSFET
							//PWM STOP
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




