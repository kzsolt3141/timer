/*
 * timer.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include <stdint.h>

void TIMER0Init(uint8_t tmr0_init_val);

uint16_t TIMER0_interrupt_cnt;
#endif /* TIMER0_H_ */