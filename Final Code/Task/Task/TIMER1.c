/*
 * TIMER.c
 *
 * Created: 21/07/2020 06:22:48
 *  Author: ADHM
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include "TIMER1.h"
//Variable used for ICR1 calculations and also used to hold its value 
static volatile long HOLD;



void TIMER_INIT(uint8_t PRESCALE,uint8_t mode,uint16_t frequency)
{ 
	
	//MAKE OC1A OC1B AS OUTPUT
     HARDWARE_INIT();
	//enable force compare match FOR TIMER 1 A,B
	SET_BIT(TCCR1C,FOC1A);	SET_BIT(TCCR1C,FOC1B);

	
	
	//SETTING FOR PHASE CORRECT MODE MODE 11(VARIABLE FREQUENCY) OR MODE 10
	switch(mode)
	{//TOP=ICR1
	case MODE10:CLR_BIT(TCCR1A,WGM10);SET_BIT(TCCR1A,WGM11);CLR_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
	//TOP=OCR1A
	case MODE11:SET_BIT(TCCR1A,WGM10);SET_BIT(TCCR1A,WGM11);CLR_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
	//default Mode 10
	default:CLR_BIT(TCCR1A,WGM10);SET_BIT(TCCR1A,WGM11);CLR_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
	}
	//SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1A1); 

	
	switch(PRESCALE)
	{    case PRE_1:  SET_BIT(TCCR1B,CS10);CLR_BIT(TCCR1B,CS11); CLR_BIT(TCCR1B,CS12);
		 ICR1=GET_FREQUENCY(1,frequency);	HOLD=ICR1;break;
		case PRE_8: CLR_BIT(TCCR1B,CS10);SET_BIT(TCCR1B,CS11); CLR_BIT(TCCR1B,CS12); 
		ICR1=GET_FREQUENCY(8,frequency);
		 HOLD=ICR1;
		  break;
		case PRE_64:SET_BIT(TCCR1B,CS10);SET_BIT(TCCR1B,CS11); CLR_BIT(TCCR1B,CS12);  
		 ICR1=GET_FREQUENCY(64,frequency); HOLD=ICR1; break;
		case PRE_256:CLR_BIT(TCCR1B,CS10);CLR_BIT(TCCR1B,CS11); SET_BIT(TCCR1B,CS12); 
		 ICR1=GET_FREQUENCY(256,frequency); HOLD=ICR1; break;
		case PRE_1024:SET_BIT(TCCR1B,CS10);CLR_BIT(TCCR1B,CS11); SET_BIT(TCCR1B,CS12);
		 ICR1=GET_FREQUENCY(1024,frequency);HOLD=ICR1;  break;
		
		//PRESCALE OF /8
		default:CLR_BIT(TCCR1B,CS10);SET_BIT(TCCR1B,CS11); CLR_BIT(TCCR1B,CS12); ICR1=GET_FREQUENCY(8,frequency) ; HOLD=ICR1; break;
		
		
	}
	//fO R ENABLING INTERRUPTS 
		INTERRUPT_INI();
	

		
}
//Setting Timer A output mode
void TIMERA_SET(uint8_t OUTPUT_MODE)
	{
		switch (OUTPUT_MODE)
		
		{
		case NON_INVERTED:CLR_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1A1);break;
		case INVERTED:SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1A1); break;
		// INVERTED as default
		default:SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1A1); break;
			
			
		}
	}
		//Setting Timer B output mode
		void TIMERB_SET(uint8_t OUTPUT_MODE)
		{
			switch (OUTPUT_MODE)
			
			{
				case NON_INVERTED:CLR_BIT(TCCR1A,COM1B0); SET_BIT(TCCR1A,COM1B1); break;
				case INVERTED:
				SET_BIT(TCCR1A,COM1B0); SET_BIT(TCCR1A,COM1B1);break;
				// Non_INVERTED as default
				default: CLR_BIT(TCCR1A,COM1B0); SET_BIT(TCCR1A,COM1B1); break;
				
			}
		
		}
		
	

void DEAD_TIME1(uint16_t TIME_US,uint8_t prescale)
		{
			 double ticks;
			//Calculating delay
			switch(prescale)
		   {case PRE_1:   ticks=GET_TICKS(TIME_US,1);break;
			   case PRE_8:   ticks=GET_TICKS(TIME_US,8);break;
			   case PRE_64:   ticks=GET_TICKS(TIME_US,64);break;
			   case PRE_256:   ticks=GET_TICKS(TIME_US,256);break;
			   case PRE_1024:ticks=GET_TICKS(TIME_US,1024);break;
			   default:ticks=0;break;
		}
		
		ICR1=(HOLD-(int)ticks);
		}
	//Co_Functions 
	//INterrupt enable 
 void  INTERRUPT_INI()
{
	
	TIMSK1 = (1 << TOIE1) ;
	sei();
	
}

	
void GENERATE_WAVEA(uint8_t DUTY_CYLCE,uint8_t OUTPUT_MODE)
{ 
	switch (OUTPUT_MODE)
	{
		case NON_INVERTED: CLR_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1A1);
    	OCR1A=(((ICR1*DUTY_CYLCE)/100));
		break;
		
		case INVERTED:SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1A1);
			OCR1A=(ICR1-((ICR1*DUTY_CYLCE)/100));  break;
		// INVERTED as default
		default:SET_BIT(TCCR1A,COM1A0); SET_BIT(TCCR1A,COM1A1); 
			OCR1A=(ICR1-((ICR1*DUTY_CYLCE)/100));break;
		
		
	}

}
void GENERATE_WAVEB(uint8_t DUTY_CYLCE,uint8_t OUTPUT_MODE)
{
	switch (OUTPUT_MODE)
	
	{
		case NON_INVERTED:CLR_BIT(TCCR1A,COM1B0); SET_BIT(TCCR1A,COM1B1);
		OCR1B=(((ICR1*DUTY_CYLCE)/100));break;
		
		case INVERTED:SET_BIT(TCCR1A,COM1B0); SET_BIT(TCCR1A,COM1B1);
		OCR1B=(ICR1-((ICR1*DUTY_CYLCE)/100)); 
	    break;
		// NON-INVERTED as default
		default:CLR_BIT(TCCR1A,COM1B0); SET_BIT(TCCR1A,COM1B1);
		OCR1B=(ICR1-((ICR1*DUTY_CYLCE)/100));break;
		
		
	}

}
		
		
	