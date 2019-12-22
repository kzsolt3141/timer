/*
 * timer.c
 *
 * Created: 12/22/2019 3:00:52 PM
 * Author : Zsolt
 */ 

#include <avr/io.h>
#include "uart.h"
#include "timer.h"
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
    USARTInit();
    TIMERInit(0xB2);
    while (1) 
    {
        printf("%d\n",TIMER0_interrupt_cnt);
        _delay_ms(1000);
    }
}

