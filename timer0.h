/*
 * timer0.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 

#ifndef TIMER0_H_
#define TIMER0_H_

#include <stdint.h>

/**
 * Initialize Timer 0
 * @param[in] tmr0_init_val initialize timer counter register,
 * from this value will count up to 0xFF the will generate interurpt
 */
void TIMER0Init(uint8_t tmr0_init_val);

/**
 * Count interrupts
 */
extern uint16_t TIMER0_interrupt_cnt;
#endif /* TIMER0_H_ */
