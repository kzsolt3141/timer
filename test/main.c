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

/**
 * USART RX interrupt callback handle context
 */
struct USART_RXC_cb_ctx_t {
    uint8_t rx;  // received byte to be seved here
};

/**
 * USART RX interrupt callback handle
 * @param[inout] ctx user data for interrupt callback
 * When ISR occurs USART_RXC_cb will be called with ctx as parameter
 * UART RX data (UDR) should be saved in this function
 */
static void USART_RXC_cb_handle(void* ctx) {
    struct USART_RXC_cb_ctx_t* t_ctx = (struct USART_RXC_cb_ctx_t*)ctx;

    t_ctx->rx = UDR;
    printf("%c\n", t_ctx->rx);
}

/**
 * TIMER interrupt callback handle context
 */
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
    // UART INIT
    //-------------------------------
    const uint16_t baud_rate = 38400;

    uint8_t sts = 0;
    struct USART_RXC_cb_ctx_t USART_RXC_ctx = {};

    USART_init(baud_rate);

    sts = regiter_USART_RXC_cb(USART_RXC_cb_handle, &USART_RXC_ctx);
    if (sts) return sts;

    printf("Init Done UART baud: %u\n", (uint16_t)baud_rate);
    //-------------------------------

    // TIMER0 init
    //-------------------------------
    const uint8_t tmr0_init_val = 0x64;
    struct Timer0_OVF_cb_ctx_t timer0_ctx = {0};
    timer0_ctx.tmr0_init_val = tmr0_init_val;

    TIMER0Init(tmr0_init_val);

    regiter_TIMER0_OVF_cb(TIMER0_OVF_cb_handle, &timer0_ctx);
    //-------------------------------

    // TIMER1Init(0xE17C);
    // TIMER1CompareInit(15625);
    // TIMER1PWMInit();

    while (1) {
        printf("%d \n", timer0_ctx.tmr0_int_cnt);
        _delay_ms(1000);
    }
}
