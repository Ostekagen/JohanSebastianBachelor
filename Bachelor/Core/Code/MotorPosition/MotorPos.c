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


 /* External Variables */

/* Variables */
uint8_t uint8_position = 0;

uint8_t uint8_hallBLDC1 = 0;
uint8_t uint8_hallBLDC2 = 0;
uint8_t uint8_hallBLDC3 = 0;


/* Start Code Here */

uint8_t pfx_MotorPos() // main function
{
uint8_hallBLDC1 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10); // read value from gpio-pin (5v tolerant)
uint8_hallBLDC2 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);
uint8_hallBLDC3 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);


if(uint8_hallBLDC1 == 0 && uint8_hallBLDC2 == 1 && uint8_hallBLDC3 == 0 ) // see truth table
	{
	uint8_position = 1; // write new
	}
else if(uint8_hallBLDC1 == 0 && uint8_hallBLDC2 == 1 && uint8_hallBLDC3 == 1 )
	{
	uint8_position = 2;
	}
else if(uint8_hallBLDC1 == 0 && uint8_hallBLDC2 == 0 && uint8_hallBLDC3 == 1 )
	{
	uint8_position = 3;
	}
else if(uint8_hallBLDC1 == 1 && uint8_hallBLDC2 == 0 && uint8_hallBLDC3 == 1 )
	{
	uint8_position = 4;
	}
else if(uint8_hallBLDC1 == 1 && uint8_hallBLDC2 == 0 && uint8_hallBLDC3 == 0 )
	{
	uint8_position = 5;
	}
else if(uint8_hallBLDC1 == 1 && uint8_hallBLDC2 == 1 && uint8_hallBLDC3 == 0 )
	{
	uint8_position = 6;
	}
else
	{
	pfx_PWM_Stop();				// Turn off all PWM by applying compare value larger than counter
	}

return uint8_position;
}
