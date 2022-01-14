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

// Example for initial counter value calcualtion:
// max number of interrupts per second F_CPU/prescaler = 8000000/1024 = 7812.5Hz
// possible interrupts per second: 30.51 ... 7812.5
// for 50 interrupts per second: 7812.5 / 50 = 156.25
// conut to: 256 - 156 = 100 -> set register to 0x64
void TIMER0_init(uint8_t tmr0_init_val, enum TIMER0_clock_source clk_src)
{
    cli();

    TCNT0 = tmr0_init_val;
    TCCR0 = clk_src;

    if (TIMER0_cb_) {
        TIMSK |= (1 << TOIE0);  // overflow interrupt enable
    }

    sei();
}

void regiter_TIMER0_isr_cb(TIMER0_isr_cb cb, void* ctx) {
    TIMER0_cb_ = cb;
    TIMER0_cb_ctx_ = ctx;
}

ISR(TIMER0_OVF_vect){
    TIMER0_cb_(TIMER0_cb_ctx_);
}
