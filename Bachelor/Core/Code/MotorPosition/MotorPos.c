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

/* Variables */
struct ST_MOTORPOS{uint8_t uint8_position;uint8_t uint8_scheme;}motorpos={0, 1};

uint8_t uint8_hallBLDC1 = 0;
uint8_t uint8_hallBLDC2 = 0;
uint8_t uint8_hallBLDC3 = 0;

uint8_t uint8_positionOld = 0;

int int16_hallUpperLimit = 100000; // TBD
int int16_hallLowerLimit = 75000; // TBD

int maxValue = 65535;// timer 6 is a 16-bit counter
int timerValue = 0;
int timerValueOld = 0;
int sinceLastRun = 0;
int sinceLastComm = 0;
int iAliveMotor;
int iAliveMotor2;

/* Start Code Here */

struct ST_MOTORPOS pfx_MotorPos() // main function
{

uint8_hallBLDC1 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10); // read value from gpio-pin (5v tolerant)
uint8_hallBLDC2 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);
uint8_hallBLDC3 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);

/*60 degrees commutation*/
uint8_positionOld = motorpos.uint8_position; // save old

if(uint8_hallBLDC1 == 0 && uint8_hallBLDC2 == 0 && uint8_hallBLDC3 == 1 && motorpos.uint8_position != 2 ) // see truth table
	{
	motorpos.uint8_position = 1; // write new
	}
else if(uint8_hallBLDC1 == 1 && uint8_hallBLDC2 == 0 && uint8_hallBLDC3 == 1 && motorpos.uint8_position != 4)
	{
	motorpos.uint8_position = 3;
	}
else if(uint8_hallBLDC1 == 1 && uint8_hallBLDC2 == 0 && uint8_hallBLDC3 == 0 && motorpos.uint8_position != 6)
	{
	motorpos.uint8_position = 5;
	}
else if(uint8_hallBLDC1 == 1 && uint8_hallBLDC2 == 1 && uint8_hallBLDC3 == 0 && motorpos.uint8_position != 8)
	{
	motorpos.uint8_position = 7;
	}
else if(uint8_hallBLDC1 == 0 && uint8_hallBLDC2 == 1 && uint8_hallBLDC3 == 0 && motorpos.uint8_position != 10)
	{
	motorpos.uint8_position = 9;
	}
else if(uint8_hallBLDC1 == 0 && uint8_hallBLDC2 == 1 && uint8_hallBLDC3 == 1 && motorpos.uint8_position != 12)
	{
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
	sinceLastComm = sinceLastRun;
	sinceLastRun = 0;
	iAliveMotor2 = iAliveMotor2 + 1;
}

if( motorpos.uint8_position % 2 != 0) // if motorposition is odd incrementation is allowed
{
	if (sinceLastRun + sinceLastRun >= sinceLastComm) // half the time of last commutation
	{
		motorpos.uint8_position = motorpos.uint8_position + 1; // Increment
	}
}

if (sinceLastRun < iAliveMotor )
{
	iAliveMotor2 = iAliveMotor2 + 1;
}
iAliveMotor = sinceLastRun;
/*Scheme selector*/

if(motorpos.uint8_scheme == 2  && sinceLastComm <= int16_hallUpperLimit) // Change to slow-scheme due to velocity
{
	motorpos.uint8_scheme = 1;

}
if(sinceLastComm >= int16_hallLowerLimit) // Change to fast-scheme due to velocity /remember hysteresis
{
	motorpos.uint8_scheme = 2;

}
else
{
	/*do nothing*/
}

return motorpos;
}


