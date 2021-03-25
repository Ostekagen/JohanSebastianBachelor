/*
 * MotorPos.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Jens Peter Nebsbjerg
 *
 */

/* includes */

#include <stdio.h>
#include <stdint.h>


 /*Define*/
struct ST_MOTORPOS
{
uint8_t uint8_position = 0;
uint8_t uint8_scheme = 0;
uint8_t uint8_positionOld = 0;
}

uint8_t Hal1 = 0;
uint8_t Hal2 = 0;
uint8_t Hal3 = 0;
uint32_t commutationTime = 0; // OVERFLOW PROTECTION? Ikke nødvendigt for bruges kun i hurtig-mode!

/*function*/

pfx_MotorPos() // main function
{

Hal1 = // read value from gpio-pin
Hal2 = // read value from gpio-pin
Hal3 = // read value from gpio-pin


if(Hal1 == 1 && Hal2 == 1 && Hal3 == 1)
	{
	ST_MOTORPOS.uint8_positionOld = ST_MOTORPOS.uint8_position;
	ST_MOTORPOS.uint8_position = 1;
	}
else if(Hal1 == 1 && Hal2 == 1 && Hal3 == 1)
	{
	ST_MOTORPOS.uint8_positionOld = ST_MOTORPOS.uint8_position;
	ST_MOTORPOS.uint8_position = 3;
	}
else if(Hal1 == 1 && Hal2 == 1 && Hal3 == 1)
	{
	ST_MOTORPOS.uint8_positionOld = ST_MOTORPOS.uint8_position;
	ST_MOTORPOS.uint8_position = 5;
	}
else if(Hal1 == 1 && Hal2 == 1 && Hal3 == 1)
	{
	ST_MOTORPOS.uint8_positionOld = ST_MOTORPOS.uint8_position;
	ST_MOTORPOS.uint8_position = 7;
	}
else if(Hal1 == 1 && Hal2 == 1 && Hal3 == 1)
	{
	ST_MOTORPOS.uint8_positionOld = ST_MOTORPOS.uint8_position;
	ST_MOTORPOS.uint8_position = 9;
	}
else if(Hal1 == 1 && Hal2 == 1 && Hal3 == 1)
	{
	ST_MOTORPOS.uint8_positionOld = ST_MOTORPOS.uint8_position;
	ST_MOTORPOS.uint8_position = 11;
	}
else
	{
	ST_MOTORPOS.uint8_positionOld = ST_MOTORPOS.uint8_position;
	ST_MOTORPOS.uint8_position = 0;
	}


if(ST_MOTORPOS.uint8_positionOld != ST_MOTORPOS.uint8_position)
	{
	commutationTime = ;	// timer værdi overføres

 					// stop timer
 					// (gen)start timer
					// 2 gange commutationtid overfor timer! = incrementeres ST_MOTORPOS.position hvis 1,3,5,7,9,11 else intet
	}
}



if(ST_MOTORPOS.uint8_scheme == 2  && commutationTime <= xxx) // scheme er 2 *husk hysterese*
{
	ST_MOTORPOS.uint8_scheme = 1;
}
else if(commutationTime >= xxx) // scheme er 0 eller 1 *husk hystere*
{
	ST_MOTORPOS.uint8_scheme = 2;
}
else
{
	//Error
}

