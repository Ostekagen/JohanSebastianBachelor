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
#include "stm32f4xx_hal_tim.h"


 /*Define*/

uint8_t Hal1 = 0;
uint8_t Hal2 = 0;
uint8_t Hal3 = 0;
uint32_t commutationTime = 0; // OVERFLOW PROTECTION? Ikke nødvendigt for bruges kun i hurtig-mode?

uint32_t SchemeValue1 = 2500;
uint32_t SchemeValue2 = 2000;

uint16_t maxValue = 65535;// 16-bit counter
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


if(Hal1 == 1 && Hal2 == 1 && Hal3 == 1)
	{
	motorpos.uint8_positionOld = motorpos.uint8_position;
	motorpos.uint8_position = 1;
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
	// pwm-stop?
	//motorpos.uint8_position = 0;?
	}

/*30 degrees commutation*/

timerValueOld = timerValue;
timerValue = TIM6->CNT;

if(timerValue < timerValueOld) // in case of overflow
{
	sinceLastRun = maxValue - timerValueOld + timerValue;
}
else
{
	sinceLastRun +=  timerValue - timerValueOld; // Count ups until saved in sinceLastComm
}


if(motorpos.uint8_positionOld != motorpos.uint8_position) // If commutation happend since last
{
	if(timerValue < timerValueOld) // in case of overflow
	{
	sinceLastComm = maxValue - timerValueOld  + timerValue;
	}
	else
	{
	sinceLastComm =  timerValue - timerValueOld;
	}
	sinceLastRun = 0;
}

if( motorpos.uint8_position % 2 != 0) // if motorposition is ueven increment is allowed
{
	if (sinceLastRun + sinceLastRun >= sinceLastComm)
	{
		motorpos.uint8_position = motorpos.uint8_position + 1;
	}
}

/*Scheme*/

if(motorpos.uint8_scheme == 2  && commutationTime <= SchemeValue1) // Change to slow-scheme due to velocity
{
	motorpos.uint8_scheme = 1;
}
else if(commutationTime >= SchemeValue2) // Change to fast-scheme due to velocity /remember hysteresis
{
	motorpos.uint8_scheme = 2;
}
else
{
	/*do nothing*/
}

return motorpos;
}


