/*
 * TIMER.h
 *
 * Created: 21/07/2020 06:23:04
 *  Author: ADHM
 */ 


#ifndef TIMER_H_
#define TIMER_H_


//MODES
#define MODE10 0
#define MODE11 1
//PRESCALE
#define PRE_1 0
#define PRE_8 1
#define PRE_64 2
#define PRE_256 3
#define PRE_1024 4
//OUTPUT MODE 
#define NON_INVERTED 0
#define INVERTED 1
//HARDWARE 
#define OC1A 1
#define OC1B 2
//MACROS FOR BIT CONTROL
#define SET_BIT(REG,INDX) ((REG)|=(1<<(INDX)))
#define CLR_BIT(REG,INDX) ((REG)&=~(1<<(INDX)))
#define READ_BIT(REG,INDX)	((REG>>INDX)&0x01)
void DEAD_TIME(uint16_t TIME_US );
void TIMER_INIT(uint8_t PRESCALE,uint8_t mode,uint16_t frequency);
void TIMERA_SET(uint8_t OUTPUT_MODE);
void TIMERB_SET(uint8_t OUTPUT_MODE);





#endif /* TIMER_H_ */