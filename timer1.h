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
 * from this value will count up to 0xFFFF then will generate interurpt in normal mode
 */
void TIMER1_init(uint16_t tmr1_init_val);

/**
 * Initialize Timer 1 for CTC on OC1A
 * @param[in] tmr1_cmpa_val initialize timer comparator register,
 * when timer reaches this value, it will generate TIMER1_COMPA interrupt
 */
void TIMER1_compare_init(uint16_t tmr1_cmpa_val);

/**
 * Initialize Timer 1 for fast PWM 8 bit
 */
void TIMER1_PWM_init();

/**
 * Timer 1 interrupt callback type
 * @param[inout] ctx user data for interrupt callback
 * When ISR occurs TIMER1_isr_cb will be called with ctx as parameter
 */
typedef void (*TIMER1_isr_cb)(void* ctx);

/**
 * Register callback and context for Timer 1 interrupt
 * @param[in] cb callback for isr; must not be NULL
 * @param[in] ctx user defined callback context; must not be NULL
 * 
 * @return 0 for success
 *         other in case of fail
 */
uint8_t regiter_TIMER1_isr_cb(TIMER1_isr_cb cb, void* ctx);
#endif /* TIMER1_H_ */
