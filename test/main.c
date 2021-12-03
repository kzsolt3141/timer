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

struct Timer0_OVF_cb_ctx_t {
    uint8_t tmr0_init_val;
    int tmr0_int_cnt;
};

static void TIMER0_OVF_cb_handle(void* ctx) {
    struct Timer0_OVF_cb_ctx_t* t_ctx = (struct Timer0_OVF_cb_ctx_t*)ctx;

    TCNT0 = t_ctx->tmr0_init_val;
    t_ctx->tmr0_int_cnt++;
}

int main(void)
{
    struct Timer0_OVF_cb_ctx_t timer0_ctx = {0};
    timer0_ctx.tmr0_init_val = 0x64;

    USARTInit();
    TIMER0Init(0x64);

    regiter_TIMER0_OVF_cb(TIMER0_OVF_cb_handle, &timer0_ctx);
    // TIMER1Init(0xE17C);
    // TIMER1CompareInit(15625);
    // TIMER1PWMInit();
    while (1) {
        printf("%d \n", timer0_ctx.tmr0_int_cnt);
        _delay_ms(1000);
    }
}
