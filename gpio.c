/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "gpio.h"
#include "timer.h"

void pinMode( void )
{
    *GPIO5B = (0x3 << 16);                  // 5B0, GPIO = alt 0
    *GPIO5_SWPORTA_DDR &= ~(0x100); 
    *GPIO5B = (0xc << 16);                  // 5B1, GPIO = alt 0
    *GPIO5_SWPORTA_DDR |= 0x200;
}

int digitalRead( void )
{
    if ((*GPIO5_EXT_PORTA_OFFSET & 0x100) != 0x0) {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

void digitalWrite( int state )
{
    if ( state == LOW ) {
        *GPIO5_SWPORTA_DR &= ~(0x200);
    } else if ( state == HIGH ) {
        *GPIO5_SWPORTA_DR |= 0x200;
    }
}

void led_test( void )
{
    int i;

    pinMode();
    for (i=0; i< 5; i++) {
        digitalWrite( HIGH );
        udelay( 1000000 );
        digitalWrite( LOW );
        udelay( 1000000 );
    }
}

void button_test( void )
{
    int i;
    int old_state;
    int current_state;

    printf("Push button 10 times\r\n");
    pinMode();
    old_state = 0;
    for (i=0; i<10; ) {
        current_state = digitalRead();
        if ( old_state == 0 && current_state == 1 ) {
            digitalWrite( HIGH );  // On
            old_state = current_state;
        } else if ( old_state == 1 && current_state == 0 ) {
            digitalWrite( LOW );   // Off
            old_state = current_state;
            i++;
        }
        udelay( 50000 );
    }
}
