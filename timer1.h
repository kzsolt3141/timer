/*
 * timer1.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 

#ifndef TIMER1_H_
#define TIMER1_H_

#include <stdint.h>

/**
 * Initialize Timer 1 for ovwerflow interrupt
 * @param[in] tmr0_init_val initialize timer counter register,
 * from this value will count up to 0xFFFF then will generate interurpt
 */
void TIMER1Init(uint16_t tmr1_init_val);

/**
 * Initialize Timer 1 for CTC on OC1A
 */
void TIMER1CompareInit(uint16_t tmr1_cmpa_val);

/**
 * Initialize Timer 1 for fast PWM 8 bit
 */
void TIMER1PWMInit();

extern uint16_t TIMER1_interrupt_cnt;
#endif /* TIMER1_H_ */
