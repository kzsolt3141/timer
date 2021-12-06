/*
 * timer2.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 

#ifndef TIMER2_H_
#define TIMER2_H_

#include <stdint.h>

enum TIMER2_clock_source {
    TIMER2_PS_DISABLE_CLK   = 0,
    TIMER2_PS_PRESCALE_1,
    TIMER2_PS_PRESCALE_8,
    TIMER2_PS_PRESCALE_64,
    TIMER2_PS_PRESCALE_256,
    TIMER2_PS_PRESCALE_1024,
    TIMER2_PS_SOURCE_T1_FALLING,
    TIMER2_PS_SOURCE_T1_RISING
};

/**
 * Initialize Timer 2 for ovwerflow interrupt
 * @param[in] tmr2_init_val initialize timer counter register,
 * from this value will count up to 0xFF then will generate interurpt in normal mode
 */
void TIMER2_init(uint8_t tmr2_init_val, enum TIMER2_clock_source clk_src);

/**
 * Initialize Timer 2 for CTC on OC2A
 * @param[in] tmr2_cmpa_val initialize timer comparator register,
 * when timer reaches this value, it will generate TIMER2_COMPA interrupt
 */
void TIMER2_compare_init(uint8_t tmr2_cmpa_val, enum TIMER2_clock_source clk_src);

/**
 * Initialize Timer 2 for fast PWM 8 bit
 */
void TIMER2_PWM_init(uint8_t tmr2_cmpa_val, enum TIMER2_clock_source clk_src);

/**
 * Timer 2 interrupt callback type
 * @param[inout] ctx user data for interrupt callback
 * When ISR occurs TIMER1_isr_cb will be called with ctx as parameter
 */
typedef void (*TIMER2_isr_cb)(void* ctx);

/**
 * Register callback and context for Timer 2 interrupt
 * @param[in] cb callback for isr; must not be NULL
 * @param[in] ctx user defined callback context; must not be NULL
 * 
 * @return 0 for success
 *         other in case of fail
 */
uint8_t regiter_TIMER2_isr_cb(TIMER2_isr_cb cb, void* ctx);
#endif /* TIMER2_H_ */
