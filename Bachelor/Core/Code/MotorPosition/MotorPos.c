/*
 * MotorPos.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Jens Peter Nebsbjerg
 *
 */

/* Includes */
#include "main.h"
#include "PWM.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal_tim.h"

TIM_HandleTypeDef htim6;
TIM_OC_InitTypeDef sConfigOC;

 /* External Variables */
extern volatile uint32_t ADC_DMA_array[]; // Initiating DMA array for reading of ADC values //midlertidig til test

/* Variables */
struct ST_MOTORPOS{uint8_t uint8_position;uint8_t uint8_scheme;}motorpos={0, 0};

uint8_t hal1 = 0;
uint8_t hal2 = 0;
uint8_t hal3 = 0;

uint8_t hal1b = 0;
uint8_t hal2b = 0;
uint8_t hal3b = 0;

uint8_t uint8_positionOld = 0;
uint16_t commutationTime = 0; // OVERFLOW PROTECTION? Ikke nødvendigt for bruges kun i hurtig-mode?

uint16_t schemeValue1 = 2500; // TBD
uint16_t schemeValue2 = 2000; // TBD

uint16_t maxValue = 65535;// timer 6 is a 16-bit counter
uint16_t timerValue = 0;
uint16_t timerValueOld = 0;
uint16_t sinceLastRun = 0;
uint16_t sinceLastComm = 0;

<<<<<<< HEAD
struct ST_MOTORPOS{uint8_t uint8_position;uint8_t uint8_scheme;}motorpos={0, 0};

/*function*/

=======
/* Start Code Here */
>>>>>>> branch 'main' of https://github.com/Ostekagen/JohanSebastianBachelor.git
struct ST_MOTORPOS pfx_MotorPos() // main function
{


hal1 = HAL_GPIO_ReadPin(GPIOC, H1_GPIO_Pin); // read value from gpio-pin (5v tolerant)
hal2 = HAL_GPIO_ReadPin(GPIOC, H2_GPIO_Pin);
hal3 = HAL_GPIO_ReadPin(GPIOC, H3_GPIO_Pin);



if(hal1 == 1 && hal2 == 1 && hal3 == 1 && motorpos.uint8_position != 2 ) // see truth table
	{
	uint8_positionOld = motorpos.uint8_position; // save old
	motorpos.uint8_position = 1; // write new
	}
else if(hal1 == 0 && hal2 == 1 && hal3 == 1 && motorpos.uint8_position != 4)
	{
	uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 3;
	}
else if(hal1 == 0 && hal2 == 0 && hal3 == 1 && motorpos.uint8_position != 6)
	{
	uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 5;
	}
else if(hal1 == 0 && hal2 == 0 && hal3 == 0 && motorpos.uint8_position != 8)
	{
	uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 7;
	}
else if(hal1 == 1 && hal2 == 0 && hal3 == 0 && motorpos.uint8_position != 10)
	{
	uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 9;
	}
else if(hal1 == 1 && hal2 == 1 && hal3 == 0 && motorpos.uint8_position != 12)
	{
	uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 11;
	}
else
	{
	pfx_PWM_Stop();				// Turn off all PWM by applying compare value larger than counter
	}

/*30 degrees commutation*/

timerValueOld = timerValue; // save old timer value
timerValue = __HAL_TIM_GetCounter(&htim6);  // save new timer value


if(timerValue < timerValueOld) // in case of overflow
{
	sinceLastRun += maxValue - timerValueOld + timerValue;
}
else
{
	sinceLastRun +=  timerValue - timerValueOld; // Count ups until saved in sinceLastComm
}


if(uint8_positionOld != motorpos.uint8_position) // If commutation happened since last
{
	if(timerValue < timerValueOld) // in case of overflow
	{
	sinceLastComm = maxValue - timerValueOld  + timerValue;
	}
	else
	{
	sinceLastComm =  timerValue - timerValueOld;
	}
	sinceLastRun = 0; // reset
}

if( motorpos.uint8_position % 2 != 0) // if motorposition is odd incrementation is allowed
{
	if (sinceLastRun + sinceLastRun >= sinceLastComm) // half the time of last commutation
	{
		motorpos.uint8_position = ++motorpos.uint8_position; // Increment
	}
}

/*Scheme*/

if(motorpos.uint8_scheme == 2  && commutationTime <= schemeValue1) // Change to slow-scheme due to velocity
{
	motorpos.uint8_scheme = 1;
}
if(commutationTime >= schemeValue2) // Change to fast-scheme due to velocity /remember hysteresis
{
	motorpos.uint8_scheme = 2;
}
else
{
	/*do nothing*/
}

return motorpos;
}


