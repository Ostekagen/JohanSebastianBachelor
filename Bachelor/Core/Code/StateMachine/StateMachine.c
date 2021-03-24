
/*
 * StateMachine.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Kenneth Meier Jensen
 */

#include <math.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
//#include "stm32f4xx_hal_tim.h"	//Laver fejl i drivers
#include "main.h"
#include "MotorPos.h"

/* External Variables */
extern struct ST_MOTORPOS motorpos; // initiating external struct

/* Internal Variables */
int8_t State = 0;

/* Start Code here */
void pfx_stateInterruptFunction()
	{
		pfx_MotorPos();

		if (pfx_Error() != 0)
			{
				State = 2;
			}
		if (pfx_Brake() != 0)
			{
				State = 0;
			}

		switch(State)
				{
					case 0 : // Standby Mode
					 	{
					 		if (pfx_Error() != 0)
					 		 	{
					 		 		State = 2;
					 		 	}
					 		else if (pfx_Throttle() != 0)
					 			{
					 				State = 1;
					 			}
					 	}

					break;

					case 1 : // Manual Mode
						{
							if (pfx_Error() != 0)
					 		 	{
					 		 		State = 2;
					 		 	}
					 		pfx_BLDC();
						}

					break;

					case 2 : // Error Mode
						{
							if (pfx_Error() == 0)
								{
									State = 0;
								}
						}

					break;

					default :
					State = 2;
				}
	}



>>>>>>> branch 'main' of https://github.com/Ostekagen/JohanSebastianBachelor.git
