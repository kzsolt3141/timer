/*
 * timer.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include <stdint.h>

void TIMERInit(uint8_t tmr0_init_val);

uint16_t TIMER0_interrupt_cnt;
#endif /* TIMERS_H_ */