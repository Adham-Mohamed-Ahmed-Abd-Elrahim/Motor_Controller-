/*
 * TASK.c
 *
 * Created: 21/07/2020 06:22:03
 * Author : ADHM
 */


#include <avr/io.h>
#include "TIMER1.h"
//Frequency=8 Mhz



#include <avr/interrupt.h>
//volatile uint16_t ticks=0;
ISR(TIMER1_OVF_vect)
{
	//Variable stores the value to synchronize wave TRANSMISION B with A 
volatile uint32_t val=GET_SYNC_VAL;
	//make a delay for dead time 
	DEAD_TIME1(10,PRE_8);
	//Setting B with OUTPUT MODE
	TIMERB_SET(NON_INVERTED);
	//Synchronize a with b 
     SYNC_B(val) ;
		//ticks=0;
	
	
	
}

int main(void)
{  
	TIMER_INIT(PRE_8,MODE10,5000);
	//GENERATE WAVE AT A WITH A SPECIFIC DUTY CYCLE
	GENERATE_WAVEA(50,INVERTED);
   
	

    while (1) 
    {	
		//RESet ICR1 for the aimed frequency 
GET_FREQUENCY(8,5000);
		
    }
}

