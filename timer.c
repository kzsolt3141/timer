/*
 * timer.c
 *
 * Created: 4/15/2017 8:57:43 PM
 *  Author: Zsolt
 */ 

#include "timer.h"

#include "avr/io.h"
#include "avr/interrupt.h"

// Example for prescaler calcualtion:
// max number of interrupts per second F_CPU/prescaler = 8000000/1024 = 7812.5
// possible interrupts per second: 30.51 ... 7812.5
// for 50 interrupts per second: 7812 / 50 = 156.25
// conut to: 256 - 156 = 100 -> set register to 0x64
static uint8_t TMR0_INIT_VAL;

void TIMERInit(uint8_t tmr0_init_val)
{
    cli();
    TMR0_INIT_VAL = tmr0_init_val;
    TCNT0 = TMR0_INIT_VAL;
    TCCR0 |= ((1 << CS02) | 
              (0 << CS01) |
              (1 << CS00)); // set prescaler to 1024
    TIMSK |= (1 << TOIE0);  // overflow interrupt enable
    TIMER0_interrupt_cnt = 0;
    sei();
}

ISR(TIMER0_OVF_vect){
    TCNT0 = TMR0_INIT_VAL;
    TIMER0_interrupt_cnt++;
}    


