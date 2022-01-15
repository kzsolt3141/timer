/*
 * timer0.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 

#ifndef TIMER0_H_
#define TIMER0_H_

#include <stdint.h>

enum TIMER0_clock_source {
    TIMER0_PS_DISABLE_CLK   = 0,
    TIMER0_PS_PRESCALE_1,
    TIMER0_PS_PRESCALE_8,
    TIMER0_PS_PRESCALE_64,
    TIMER0_PS_PRESCALE_256,
    TIMER0_PS_PRESCALE_1024,
    TIMER0_PS_SOURCE_T1_FALLING,
    TIMER0_PS_SOURCE_T1_RISING
};

/**
 * Timer 0 interrupt callback type
 * @param[inout] ctx user data for interrupt callback
 * When ISR occurs TIMER0_isr_cb will be called with ctx as parameter
 */
typedef void (*TIMER0_isr_cb)(void* ctx);

/**
 * Register callback and context for Timer 0 interrupt
 * @param[in] cb   callback for isr; must not be NULL
 * @param[in] ctx  user defined callback context; must not be NULL
 * 
 */
void regiter_TIMER0_isr_cb(TIMER0_isr_cb cb, void* ctx);

/**
 * Initialize Timer 0
 * ISR callback must be registered before init is called
 * @param[in] tmr_init_val  initialize timer counter register,
 *                          from this value will count up to 0xFF then will generate interurpt
 * @param[in] clk_src       select clock prescaler, see TIMER0_clock_source
 */
void TIMER0_init(uint8_t tmr_init_val, enum TIMER0_clock_source clk_src);

/**
 * Restart Timer 0, set counter to 0
 */
void Timer0_restart ();

#endif /* TIMER0_H_ */
