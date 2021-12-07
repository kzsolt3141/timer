/*
 * timer1.h
 *
 * Created: 4/15/2017 8:57:29 PM
 *  Author: Zsolt
 */ 

#ifndef TIMER1_H_
#define TIMER1_H_

#include <stdint.h>

enum TIMER1_clock_source {
    TIMER1_PS_DISABLE_CLK   = 0,
    TIMER1_PS_PRESCALE_1,
    TIMER1_PS_PRESCALE_8,
    TIMER1_PS_PRESCALE_64,
    TIMER1_PS_PRESCALE_256,
    TIMER1_PS_PRESCALE_1024,
    TIMER1_PS_SOURCE_T1_FALLING,
    TIMER1_PS_SOURCE_T1_RISING
};

/**
 * Timer 1 interrupt callback type
 * @param[inout] ctx user data for interrupt callback
 * When ISR occurs TIMER1_isr_cb will be called with ctx as parameter
 */
typedef void (*TIMER1_isr_cb)(void* ctx);

/**
 * Register callback and context for Timer 1 interrupt
 * @param[in] cb   callback for isr; must not be NULL
 * @param[in] ctx  user defined callback context; must not be NULL
 */
void regiter_TIMER1_isr_cb(TIMER1_isr_cb cb, void* ctx);

/**
 * Initialize Timer 1
 * @param[in] tmr_init_val  initialize timer counter register,
 *                          from this value will count up to 0xFFFF then will generate interurpt
 * @param[in] clk_src       select clock prescaler, see TIMER1_clock_source,
 * @param[in] isr_en        enable ISR,
 *                          ISR callback must be registered before init is called
 * @return 0 for success
 *         other in case of fail
 */
uint8_t TIMER1_init(uint16_t tmr_init_val, enum TIMER1_clock_source clk_src, uint8_t isr_en);

/**
 * Initialize Timer 1 for CTC on OC1A
 * @param[in] tmr_cmp_val  initialize timer compare register,
 *                         when timer reaches this value, it will generate TIMER1_COMPA interrupt
 * @param[in] clk_src      select clock prescaler, see TIMER1_clock_source,
 * @param[in] isr_en       enable ISR,
 *                         ISR callback must be registered before init is called
 * @return 0 for success
 *         other in case of fail
 */
uint8_t TIMER1_compare_init(uint16_t tmr_cmpa_val, enum TIMER1_clock_source clk_src, uint8_t isr_en);

/**
 * Initialize Timer 1 for fast PWM 8 bit
 * @param[in] tmr_cmp_val  initialize timer compare register,
 *                         when timer reaches this value, it will generate TIMER1_COMPA interrupt
 * @param[in] clk_src      select clock prescaler, see TIMER1_clock_source,
 * @param[in] isr_en       enable ISR,
 *                         ISR callback must be registered before init is called
 * @return 0 for success
 *         other in case of fail
 */
uint8_t TIMER1_PWM_init(uint16_t tmr_cmpa_val, enum TIMER1_clock_source clk_src, uint8_t isr_en);
#endif /* TIMER1_H_ */
