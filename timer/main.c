/*
 * timer.c
 *
 * Created: 12/22/2019 3:00:52 PM
 * Author : Zsolt
 */ 

#include <avr/io.h>
#include "uart.h"
#include "timer0.h"
#include "timer1.h"
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
    USARTInit();
    TIMER0Init(0xB2);
    TIMER1CompareInit(1728);
    while (1) 
    {
        printf("%d %d \n",TIMER0_interrupt_cnt, TIMER1_interrupt_cnt);
        _delay_ms(1000);
    }
}

