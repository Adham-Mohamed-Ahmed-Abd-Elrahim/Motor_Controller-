/*
 * Gpio.c
 *
 * Created: 23/07/2020 15:01:33
 *  Author: ADHM
 */ 
#include "Gpio.h"
void HARDWARE_INIT()
{
		SET_BIT(DDRB,OC1A);	SET_BIT(DDRB,OC1B);
}