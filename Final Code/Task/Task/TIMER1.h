/*
 * TIMER1.h
 *
 * Created: 23/07/2020 15:00:33
 *  Author: ADHM
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_
#include "Gpio.h"
//MODES
#define MODE10 0
#define MODE11 1
//PRESCALE
#define PRE_1     0
#define PRE_8     1
#define PRE_64    2
#define PRE_256   3
#define PRE_1024  4
//OUTPUT MODE 
#define NON_INVERTED 0
#define INVERTED 1
#define GET_FREQUENCY(SCALE,Frequency)  ICR1=(((F_CPU)/Frequency))/(2*SCALE)
#define GET_TICKS(TIME_US,prescale) ((TIME_US)/(pow(10,6)/(F_CPU/prescale)))
#define GET_SYNC_VAL      (ICR1-OCR1A)
#define SYNC_B(VAL)       OCR1B=ICR1-VAL

void DEAD_TIME1(uint16_t TIME_US,uint8_t prescale);
void TIMER_INIT(uint8_t PRESCALE,uint8_t mode,uint16_t frequency);
void TIMERA_SET(uint8_t OUTPUT_MODE);
void TIMERB_SET(uint8_t OUTPUT_MODE);

//Controlling wave duty Cycle
void GENERATE_WAVEA(uint8_t DUTY_CYLCE,uint8_t OUTPUT_MODE);
void GENERATE_WAVEB(uint8_t DUTY_CYLCE,uint8_t OUTPUT_MODE);
 void INTERRUPT_INI();

#endif /* TIMER1_H_ */