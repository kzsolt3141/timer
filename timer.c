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
	SREG |= 1 << SREG_I;   // enable interrupt
	TCNT0 = TIMER0_PRELOAD;
	TCCR0 |= ((1 << CS02) | 
	          (0 << CS01) |
			  (1 << CS00)); // set prescaler to 1024
	TIMSK |= (1 << TOIE0);  // overflow interrupt enable
	sei();
}



