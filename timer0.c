/*
 * timer0.c
 *
 * Created: 4/15/2017 8:57:43 PM
 *  Author: Zsolt
 */ 

#include "timer0.h"

#include <stddef.h>

#include <avr/io.h>
#include <avr/interrupt.h>

static TIMER0_isr_cb  TIMER0_cb_     = NULL;
static void          *TIMER0_cb_ctx_ = NULL;
static TIMER0_clock_source TIMER0_clock_source_ = TIMER0_PS_DISABLE_CLK;

void TIMER0_init(TIMER0_clock_source clk_src)
{
    cli();

    TCNT0 = 0;
    TCCR0 = TIMER0_PS_DISABLE_CLK;

    TIMER0_clock_source_ = clk_src;

    if (TIMER0_cb_) {
        TIMSK |= (1 << TOIE0);  // overflow interrupt enable
    }

    sei();
}

void TIMER0_start () {
    TCCR0 = TIMER0_clock_source_;
}

uint8_t TIMER0_stop () {
    TCCR0 = TIMER0_PS_DISABLE_CLK;
    return TCNT0;
}

void TIMER0_reset () {
    TCNT0 = 0;
}

void regiter_TIMER0_isr_cb(TIMER0_isr_cb cb, void* ctx) {
    TIMER0_cb_ = cb;
    TIMER0_cb_ctx_ = ctx;
}

ISR(TIMER0_OVF_vect){
    TIMER0_cb_(TIMER0_cb_ctx_);
}
