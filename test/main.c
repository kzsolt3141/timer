/*
 * timer.c
 *
 * Created: 12/22/2019 3:00:52 PM
 * Author : Zsolt
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
#include "timer0.h"
#include "timer1.h"


int main(void)
{
    /* Replace with your application code */
    USARTInit();
    TIMER0Init(0x64);
    TIMER1Init(0xE17C);
    // TIMER1CompareInit(15625);
    TIMER1PWMInit();
    while (1) 
    {
        printf("%d %d \n",TIMER0_interrupt_cnt, TIMER1_interrupt_cnt);
        _delay_ms(1000);
    }
}