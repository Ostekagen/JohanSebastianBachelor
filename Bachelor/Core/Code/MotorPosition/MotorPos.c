/*
 * MotorPos.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Jens Peter Nebsbjerg
 *
 */

/* includes */

#include "main.h"
#include <stdio.h>
#include <stdint.h>
//#include "stm32f4xx_hal_tim.h"


 /*Define*/

uint8_t Hal1 = 0;
uint8_t Hal2 = 0;
uint8_t Hal3 = 0;
uint32_t commutationTime = 0; // OVERFLOW PROTECTION? Ikke nødvendigt for bruges kun i hurtig-mode?

uint32_t SchemeValue1 = 2500; // TBD
uint32_t SchemeValue2 = 2000; // TBD

uint16_t maxValue = 65535;// timer 6 is a 16-bit counter
uint16_t timerValue = 0;
uint16_t timerValueOld = 0;
uint16_t sinceLastRun = 0;
uint16_t sinceLastComm = 0;

struct ST_MOTORPOS{uint8_t uint8_position;uint8_t uint8_scheme;uint8_t uint8_positionOld;}motorpos={0, 0, 0};


/*function*/

struct ST_MOTORPOS pfx_MotorPos() // main function
{

Hal1 = HAL_GPIO_ReadPin(GPIOB, H1_GPIO_Pin); // read value from gpio-pin
Hal2 = HAL_GPIO_ReadPin(GPIOB, H2_GPIO_Pin);
Hal3 = HAL_GPIO_ReadPin(GPIOB, H3_GPIO_Pin);


if(Hal1 == 1 && Hal2 == 1 && Hal3 == 1) // see truth table
	{
	motorpos.uint8_positionOld = motorpos.uint8_position; // save old
	motorpos.uint8_position = 1; // write new
	}
else if(Hal1 == 0 && Hal2 == 1 && Hal3 == 1)
	{
	motorpos.uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 3;
	}
else if(Hal1 == 0 && Hal2 == 0 && Hal3 == 1)
	{
	motorpos.uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 5;
	}
else if(Hal1 == 0 && Hal2 == 0 && Hal3 == 0)
	{
	motorpos.uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 7;
	}
else if(Hal1 == 1 && Hal2 == 0 && Hal3 == 0)
	{
	motorpos.uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 9;
	}
else if(Hal1 == 1 && Hal2 == 1 && Hal3 == 0)
	{
	motorpos.uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 11;
	}
else
	{
	TIM1->CCR1 = 5000;					// Duty cycle of zero to all three PWMs
	TIM1->CCR2 = 5000;					//
	TIM1->CCR3 = 5000;					//
	}

/*30 degrees commutation*/

timerValueOld = timerValue; // save old
timerValue = TIM6->CNT; // write new

if(timerValue < timerValueOld) // in case of overflow
{
	sinceLastRun += maxValue - timerValueOld + timerValue;
}
else
{
	sinceLastRun +=  timerValue - timerValueOld; // Count ups until saved in sinceLastComm
}


if(motorpos.uint8_positionOld != motorpos.uint8_position) // If commutation happened since last
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
		motorpos.uint8_position = motorpos.uint8_position + 1; // WRITE WITH INCREMENTATION INSTEAD!
	}
}

/*Scheme*/

if(motorpos.uint8_scheme == 2  && commutationTime <= SchemeValue1) // Change to slow-scheme due to velocity
{
	motorpos.uint8_scheme = 1;
}
if(commutationTime >= SchemeValue2) // Change to fast-scheme due to velocity /remember hysteresis
{
	motorpos.uint8_scheme = 2;
}
else
{
	/*do nothing*/
}

return motorpos;
}


