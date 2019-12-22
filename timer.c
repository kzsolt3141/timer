/*
 * timer.c
 *
 * Created: 4/15/2017 8:57:43 PM
 *  Author: Zsolt
 */ 

#include "timer.h"

#include "avr/io.h"
#include "avr/interrupt.h"

void TIMERInit()
{
    cli();
    TCNT0 = 0x00;
    TCCR0 |= ((1 << CS02) | 
              (0 << CS01) |
              (1 << CS00)); // set prescaler to 1024
    TIMSK |= (1 << TOIE0);  // overflow interrupt enable
    TIMER0_interrupt_cnt = 0;
    sei();
}

ISR(TIMER0_OVF_vect){
    TIMER0_interrupt_cnt++;
}    


