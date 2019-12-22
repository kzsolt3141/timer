/*
 * timer.c
 *
 * Created: 4/15/2017 8:57:43 PM
 *  Author: Zsolt
 */ 

#include "timer1.h"

#include "avr/io.h"
#include "avr/interrupt.h"

static uint16_t TMR1_INIT_VAL;

// Example for initial counter value calcualtion:
// max number of interrupts per second F_CPU/prescaler = 8000000/1024 = 7812.5
// possible interrupts per second: 0.1192 ... 7812.5
// for 1 interrupt per second: 7812.5 / 1 = 7812
// conut to: 65536 - 7812 = 57724 -> set register to 0xE17C
void TIMER1Init(uint16_t tmr1_init_val)
{
    cli();
    TMR1_INIT_VAL = tmr1_init_val;
    TCNT1 = TMR1_INIT_VAL;
    TCCR1B |= ((1 << CS12) | 
               (0 << CS11) |
               (1 << CS10)); // set prescaler to 1024
    TIMSK |= (1 << TOIE1);  // overflow interrupt enable
    TIMER1_interrupt_cnt = 0;
    sei();
}

void TIMER1CompareInit(uint16_t tmr1_init_val){
    TMR1_INIT_VAL = tmr1_init_val;
    DDRB |= 1<<PB1; // set OC1A as output
        TCNT1 = 0;
        OCR1A = 30000;
    TCCR1A |= (0 << COM1A1) | 
              (1 << COM1A0) | // toggle OC1A when match
              (1 << WGM12)|
              (0 << CS12) |
              (1 << CS11) |
              (1 << CS10); // set prescaler to 1024
}

ISR(TIMER1_OVF_vect){
    TCNT1 = TMR1_INIT_VAL;
    TIMER1_interrupt_cnt++;
}    


