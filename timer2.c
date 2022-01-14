/*
 * timer.c
 *
 * Created: 4/15/2017 8:57:43 PM
 *  Author: Zsolt
 */ 

#include "timer2.h"

#include <stddef.h>

#include <avr/io.h>
#include <avr/interrupt.h>

static TIMER2_isr_cb  TIMER2_cb_     = NULL;
static void          *TIMER2_cb_ctx_ = NULL;

// Example for initial counter value calcualtion:
// max number of interrupts per second F_CPU/prescaler = 8000000/1024 = 7812.5
// possible interrupts per second: 0.1192 ... 7812.5
// for 1 interrupt per second: 7812.5 / 1 = 7812
// conut to: 65536 - 7812 = 57724 -> set register to 0xE17C
void TIMER2_init(uint8_t tmr2_init_val, enum TIMER2_clock_source clk_src) {
    cli();
    TCNT2  = tmr2_init_val;    // counter intialization
    TCCR2 = clk_src;

    if (TIMER2_cb_) {
        TIMSK |= (1 << TOIE2);    // overflow interrupt enable
    }

    sei();
}

// Example for initial counter value calcualtion for CTC mode:
// max number of interrupts per second F_CPU/prescaler = 8000000/1024 = 7812.5
// for 2 interrupts per second: 7812.5 * 2 = 15625
// In CTC mode, when TCNT1 reaches 15625 interrupt is generated and counter is cleared.
void TIMER2_compare_init(uint8_t tmr1_cmpa_val, enum TIMER2_clock_source clk_src) {
    cli();

    TCNT2 = 0;                // counter intialization
    OCR2 = tmr1_cmpa_val;     // compare value for CTC mode
    TCCR2 = (0 << COM21)| 
            (1 << COM20)|     // toggle OC2 when match
            (1 << WGM21) |    // CTC mode (match, then reset counter)
             clk_src;
    DDRB |= 1 << PB3;         // set OC1A as output (on port PB3)

    if (TIMER2_cb_) {
        TIMSK |= (1 << OCIE2);    // match with OCR2 interrupt enable
    }

    sei();
}

void TIMER2_PWM_init(uint8_t tmr2_cmpa_val, enum TIMER2_clock_source clk_src) {
    cli();

    TCCR2 =  (1 << COM21) | 
             (0 << COM20) |   // toggle OC2 when match
             (1 << WGM21) |
             (1 << WGM20) |   // 8 bit fast PWM
             clk_src;
    OCR2 = tmr2_cmpa_val;
    DDRB |= 1 << PB3;          // set OC2 as output (on port PB3)

    if (TIMER2_cb_) {
        TIMSK |= (1 << TOIE2);     // overflow interrupt enable
    }

    sei();
}

void regiter_TIMER2_isr_cb(TIMER2_isr_cb cb, void* ctx) {
    TIMER2_cb_ = cb;
    TIMER2_cb_ctx_ = ctx;
}

ISR(TIMER2_OVF_vect) {
    TIMER2_cb_(TIMER2_cb_ctx_);
}

ISR(TIMER2_COMP_vect) {  // if it is in CTC mode, TCNT2 is reset by default
    TIMER2_cb_(TIMER2_cb_ctx_);
}
