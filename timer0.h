/*
 * timer0.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 

#ifndef TIMER0_H_
#define TIMER0_H_

#include <stdint.h>

typedef enum TIMER0_clock_source_t {
    TIMER0_PS_DISABLE_CLK   = 0,
    TIMER0_PS_PRESCALE_1,
    TIMER0_PS_PRESCALE_8,
    TIMER0_PS_PRESCALE_64,
    TIMER0_PS_PRESCALE_256,
    TIMER0_PS_PRESCALE_1024,
    TIMER0_PS_SOURCE_T1_FALLING,
    TIMER0_PS_SOURCE_T1_RISING
} TIMER0_clock_source;

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

//TODO(Zsolt) this timer should be used for time measurements! change API


/**
 * Initialize Timer 0
 * ISR callback must be registered before init is called
 * @param[in] clk_src       select clock prescaler, see TIMER0_clock_source
 */
void TIMER0_init(TIMER0_clock_source clk_src);

/**
 * Start Timer 0
 */
void TIMER0_start ();

/**
 * Stop Timer 0 and return the current counter value
 * 
 * @return current timer value
 */
uint8_t TIMER0_stop ();

/**
 * Reset timer counter to 0
 */
void TIMER0_reset();

#endif /* TIMER0_H_ */
