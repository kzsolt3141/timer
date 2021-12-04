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
 * from this value will count up to 0xFF then will generate interurpt
 */
void TIMER0_init(uint8_t tmr0_init_val);

/**
 * Timer 0 interrupt callback type
 * @param[inout] ctx user data for interrupt callback
 * When ISR occurs TIMER0_isr_cb will be called with ctx as parameter
 */
typedef void (*TIMER0_isr_cb)(void* ctx);

/**
 * Register callback and context for Timer 0 interrupt
 * @param[in] cb callback for isr; must not be NULL
 * @param[in] ctx user defined callback context; must not be NULL
 * 
 * @return 0 for success
 *         other in case of fail
 */
uint8_t regiter_TIMER0_isr_cb(TIMER0_isr_cb cb, void* ctx);
#endif /* TIMER0_H_ */
