/*
 * Gpio.h
 *
 * Created: 23/07/2020 15:01:05
 *  Author: ADHM
 */ 


#ifndef GPIO_H_
#define GPIO_H_
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//HARDWARE
#define OC1A 1
#define OC1B 2
//MACROS FOR BIT CONTROL
#define SET_BIT(REG,INDX) ((REG)|=(1<<(INDX)))
#define CLR_BIT(REG,INDX) ((REG)&=~(1<<(INDX)))
#define READ_BIT(REG,INDX)	((REG>>INDX)&0x01)
void HARDWARE_INIT();



#endif /* GPIO_H_ */