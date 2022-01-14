/*
 * timer.c
 *
 * Created: 4/15/2017 8:57:43 PM
 *  Author: Zsolt
 */ 

#include "timer1.h"

#include <stddef.h>

#include <avr/io.h>
#include <avr/interrupt.h>

static TIMER1_isr_cb  TIMER1_cb_     = NULL;
static void          *TIMER1_cb_ctx_ = NULL;

// Example for initial counter value calcualtion:
// max number of interrupts per second F_CPU/prescaler = 8000000/1024 = 7812.5
// possible interrupts per second: 0.1192 ... 7812.5
// for 1 interrupt per second: 7812.5 / 1 = 7812
// conut to: 65536 - 7812 = 57724 -> set register to 0xE17C
void TIMER1_init(uint16_t tmr1_init_val, enum TIMER1_clock_source clk_src) {
    cli();

    TCNT1  = tmr1_init_val;     // counter intialization
    TCCR1B = clk_src;

    if (TIMER1_cb_) {
        TIMSK |= (1 << TOIE1);  // overflow interrupt enable
    }

    sei();
}

// Example for initial counter value calcualtion for CTC mode:
// max number of interrupts per second F_CPU/prescaler = 8000000/1024 = 7812.5
// for 2 interrupts per second: 7812.5 * 2 = 15625
// In CTC mode, when TCNT1 reaches 15625 interrupt is generated and counter is cleared.
void TIMER1_compare_init(uint16_t tmr1_cmpa_val, enum TIMER1_clock_source clk_src) {
    cli();

    TCNT1  = 0;                 // counter intialization
    OCR1A  = tmr1_cmpa_val;     // compare value for CTC mode
    TCCR1A = (0 << COM1A1) | 
             (1 << COM1A0);   // toggle OC1A when match
    DDRB  |= 1 << PB1;          // set OC1A as output (on port PB1)
    TCCR1B = (1 << WGM12)|   // CTC mode (match, then reset counter)
              clk_src;

    if (TIMER1_cb_) {
        TIMSK |= (1 << OCIE1A);    // match with OCR1A interrupt enable
    }

    sei();
}

void TIMER1_PWM_init(uint16_t tmr1_cmpa_val, enum TIMER1_clock_source clk_src) {
    cli();

    TCCR1A = (1 << COM1A1) | 
             (0 << COM1A0) |   // toggle OC1A when match
             (0 << WGM11)  |
             (1 << WGM10);     // 8 bit fast PWM
    TCCR1B = (1 << WGM12) |     // CTC mode (match, then reset counter)
             (0 << WGM13) |
             clk_src;
    DDRB |= 1 << PB1;          // set OC1A as output (on port PB1)
    OCR1A = tmr1_cmpa_val;

    if (TIMER1_cb_) {
        TIMSK |= (1 << TOIE1);    // overflow interrupt enable
    }

    sei();
}

void regiter_TIMER1_isr_cb(TIMER1_isr_cb cb, void* ctx) {
    TIMER1_cb_ = cb;
    TIMER1_cb_ctx_ = ctx;
}

ISR(TIMER1_OVF_vect) {
    TIMER1_cb_(TIMER1_cb_ctx_);
}

ISR(TIMER1_COMPA_vect) {  // if it is in CTC mode (WGM12 is set), TCNT1 is reset by default
    TIMER1_cb_(TIMER1_cb_ctx_);
}
