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
 * TIMER 0 interrupt callback handle context
 */
struct Timer0_cb_ctx_t {
    uint8_t tmr0_init_val;
    int tmr0_int_cnt;
};

static void TIMER0_OVF_cb_handle(void* ctx) {
    struct Timer0_cb_ctx_t* t_ctx = (struct Timer0_cb_ctx_t*)ctx;

    TCNT0 = t_ctx->tmr0_init_val;
    t_ctx->tmr0_int_cnt++;
}

/**
 * TIMER 1 interrupt callback handle context
 */
struct Timer1_cb_ctx_t {
    uint16_t tmr1_init_val;
    int tmr1_int_cnt;
};

static void TIMER1_OVF_cb_handle(void* ctx) {
    struct Timer1_cb_ctx_t* t_ctx = (struct Timer1_cb_ctx_t*)ctx;

    TCNT1 = t_ctx->tmr1_init_val;
    t_ctx->tmr1_int_cnt++;
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
    struct Timer0_cb_ctx_t timer0_ctx = {0};
    timer0_ctx.tmr0_init_val = tmr0_init_val;

    TIMER0_init(tmr0_init_val);

    regiter_TIMER0_isr_cb(TIMER0_OVF_cb_handle, &timer0_ctx);
    //-------------------------------

    // TIMER1 init
    //-------------------------------
    const uint16_t tmr1_init_val = 15625;
    struct Timer1_cb_ctx_t timer1_ctx = {0};
    timer1_ctx.tmr1_init_val = tmr1_init_val;

    TIMER1_init(tmr1_init_val);
    // TIMER1CompareInit(15625);
    // TIMER1PWMInit();

    regiter_TIMER1_isr_cb(TIMER1_OVF_cb_handle, &timer1_ctx);
    //-------------------------------

    while (1) {
        printf("T0:%d T1:%d\n", timer0_ctx.tmr0_int_cnt, timer1_ctx.tmr1_int_cnt);
        _delay_ms(1000);
    }
}
