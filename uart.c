/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "uart.h"

int UART3_ISR( void )
{
    if ( (*UART3_IIR & 0xf) == 0x4 ) {
        *irqdatarx = *UART3_DR;
        *irqflagrx = 0x1;
    }

    return 0;
}

char uart_getc( void )
{
    char ch;

    while ( *irqflagrx == 0x0 )  // wait for received data interrupt
          ;
    ch = *irqdatarx;             // got receive interrupt data
    *irqflagrx = 0x0;            // clear receive interrupt flag

    return ch;
}

void uart_putc( char ch )
{
    while (*UART3_LSR & UART_LSR_THRE)
          ;
    *UART3_THR = ch;
}

// clear terminal screen

void uart_clear( void )
{
    char ch[5];

    ch[0] = 27;
    ch[1] = '[';
    ch[2] = '2';
    ch[3] = 'J';
    ch[4] = '\0';
    printf( ch );
}

void uart_init( void )
{
    char ch;
    *irqflagrx = 0x0;     // initialize receive interrupt flag
    *irqdatarx = 0x0;     // initialize receive interrupt data
    *GPIO7B = (0x3 << 16) | 0x1;        // 7B0 out TX, alt 1
    *GPIO7A = (0xc000 << 16) | 0x4000;  // 7A7 in  RX, alt 1
    *UART3_LCR = 0x83;    // 8N1
    *UART3_DLL = 0x0d;    // 24000000 / 16 / 115200 = 13
    *UART3_DLM = 0x0;
    *UART3_LCR = 0x03;    // 8N1
    *UART3_IER = 0x0;
    *UART3_MCR = 0x03;    // DTR, RTS
    *UART3_FCR = 0x07;    // enable fifo, reset rx fifo, reset tx fifo
    // clear received data
    while (*UART3_LSR & UART_LSR_DRY) {
        ch = *UART3_DR;
    }
    *UART3_IER = 0x81;
}

void uart_test( void )
{
    char ch;

    printf( "Hello ! Type a sentance and press enter.\r\n" );
    ch = '\0';
    while( ch != '\r') {
        ch = uart_getc();
        uart_putc( ch );
    }
    printf( "\r\n" );
}
