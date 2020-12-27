/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "registers.h"
#include "timer.h"
#include "uart.h"
#include "pwm.h"
#include "clock.h"
#include "i2c.h"
#include "gpio.h"
#include "spi.h"
#include "gic.h"
#include "mmc.h"
#include "dmac.h"

const unsigned char sram2ddrcode[32] __attribute__((aligned(64))) = {0xbc,0x0,0x0,0x40,0x70,0xff,0xbc,0x2,0x0,0x0,0x0,0x10,0xbc,0x1,0xf7,0xc0,0x3d,0x0,0x20,0x7f,0x4,0x8,0x38,0x02,0x0};
const unsigned char ddr2ddrcode[32] __attribute__((aligned(64))) = {0xbc,0x0,0x0,0x00,0x00,0x10,0xbc,0x2,0x0,0x0,0x0,0x20,0xbc,0x1,0xf7,0xc0,0x3d,0x0,0x20,0x7f,0x4,0x8,0x38,0x02,0x0};

void led_blink( int delay )
{
    // LED on
    *GPIO1_SWPORTA_DR = 0x01000000;
    udelay( delay );

    // LED off
    *GPIO1_SWPORTA_DR = 0;
    udelay( delay );
}

unsigned int randomized( unsigned int i )
{
    unsigned int j;
    int k;
    int m;

    k = (i >> 28) + (i >> 2) & 0xf;
    if ( k < 5 )
        k = 5;
    j = i + 3;
    for (m = 0; m < k; m++) {
       if ( j & 0x80000000 ) {
           j = ((j ^ 0x00000062) << 1) + 1;
       } else {
           j = (j << 1);
       }
    }
    return j;
}

void ddr_test( void )
{
    unsigned int i;
    printf( "In ddr_test\r\n");

    printf( "Writing 2GB DDR with random data\r\n");
    for ( i = 0x20000; i < 0x8000000; i = i + 4 ) {
        *(volatile unsigned int *)i = randomized( i );
        if ( i < 0x100 )
            printf( "0x%x\r\n", *(volatile unsigned int *)i);
        if ( (i & 0xfffff) == 0x0 )
            printf( ".");
    }
    printf( "Reading 2GB DDR\r\n");
    for ( i = 0x20000; i < 0x8000000; i = i + 4 ) {
        if ( i < 0x100 )
            printf( "0x%x\r\n", *(volatile unsigned int *)i);
        if ( *(volatile unsigned int *)i != randomized( i ) )
            printf( "dram test failed !\r\n");
        if ( (i & 0xfffff) == 0x0 )
            printf( ".");
    }
}

void displaydst( char *dst )
{
    int i;
    unsigned int tmp;

    for (i=0; i<512; i++) {
        printf( "%02X ", dst[i] );
        if ( (i & 0xf) == 0xf ) {
            printf( "\r\n" );
        }
    }
}

void mmc_test( void )
{
    int i;
    char dst[512] __attribute__((aligned(64)));
    char src[512] __attribute__((aligned(64)));

    printf( "In mmc_test\r\n");
    printf( "Read sdcard lba 8192\r\n");
    mmc_bread( dst, 8192, 1 );       // 0, 64, 68, 8192, 139260, 6283260
    displaydst( dst );
    printf( "Read sdcard lba 6283260\r\n");
    mmc_bread( dst, 6283260, 1 );
    displaydst( dst );
    // erase 4MB from lba 6275072 to 6283263
    printf( "Erase sdcard lba 6275072 to 6283263\r\n");
    mmc_berase( 6275072, 8192 );
    printf( "Read sdcard lba 6283260\r\n");
    mmc_bread( dst, 6283260, 1 );
    displaydst( dst );
    // prepare write data
    for (i=0; i < 512; i++) {
        src[i] = i;
    }
    printf( "Write sdcard lba 6283260\r\n");
    mmc_bwrite( src, 6283260, 1 );
    printf( "Read sdcard lba 6283260\r\n");
    mmc_bread( dst, 6283260, 1 );
    displaydst( dst );
}

void dmac_test( void )
{
    unsigned int i;
    unsigned int j;
    unsigned int m;
    int k;
    // dma 16KB, 16 beats with 8 byte width, loop 128 times
    // DMAMOV SAR 0xff704000           (BC,00,00,40,70,ff)
    // DMAMOV DAR 0x10000000           (BC,02,00,00,00,10)
    // DMAMOV CCR SB16 SS64 DB16 DS64  (BC,01,F7,C0,3D,00)
    // DMALP lc0 128                   (20,7f)
    // DMALD                           (04)
    // DMAST                           (08)
    // DMALPEND lc0                    (38,02)
    // DMAEND                          (00)

    //---- sram to ddr then ddr to ddr  -----------------------------
    for ( k = 0; k < 2; k++ ) {
        // wait idle
        while( *DMAC_BUS_DBGST & 0x1 );
        *DMAC_BUS_DBGINST0 = 0x00A00000;
        if ( k == 0 )
            *DMAC_BUS_DBGINST1 = (unsigned int)sram2ddrcode;
        else
            *DMAC_BUS_DBGINST1 = (unsigned int)ddr2ddrcode;
        *DMAC_BUS_DBGCMD = 0x0;
        udelay( 10 );
        // wait idle
        while( *DMAC_BUS_DBGST & 0x1 );

        if ( k == 0 ) {
            j = 0xff704000;
            m = 0x10000000;
        } else {
            j = 0x10000000;
            m = 0x20000000;
        }
        for (i=0x0; i<0x4000; i = i + 4) {
            if (i < 0x20 )
                printf( "0x%x\r\n", *(volatile int *)m );
            if ( *(volatile int *)m != *(volatile int *)j ) {
                printf( "Error !\r\n");
                printf( "0x%x\r\n", m );
                printf( "0x%x\r\n", *(volatile int *)m );
                printf( "0x%x\r\n", *(volatile int *)j );
                break;
            }
            j = j + 4;
            m = m + 4;
        }
        // registers changed after dma
        printf( "DMAC_BUS_CPC0 = 0x%x\r\n", *DMAC_BUS_CPC0 );
        printf( "DMAC_BUS_SAR0 = 0x%x\r\n", *DMAC_BUS_SAR0 );
        printf( "DMAC_BUS_DAR0 = 0x%x\r\n", *DMAC_BUS_DAR0 );
        printf( "DMAC_BUS_CCR0 = 0x%x\r\n", *DMAC_BUS_CCR0 );
    }
}

char test_menu( void )
{
    char ch;

    uart_clear();
    printf( "--- select a test ---\r\n" );
    printf( "1. uart test\r\n2. led test\r\n3. button test\r\n4. pwm led test\r\n5. i2c lcd test\r\n6. tongsong\r\n7. servo\r\n8. spi oled test\r\n9. ddr test\r\na. mmc test\r\nb. dmac test\r\nq. quit\r\n");
    ch = uart_getc();
    if ( ch == 'q' )
        printf( "Goodbye !\r\n" );
    return ch;
}

int main() {
    char ch;
    char test_item;

    uart_init();
    config_GIC( 90, 1 );         // UART3_ISR, CPU0
    timer_init();
    rkclk_init();
    udelay( 50000 );
    // Use rkpwm by default
    *GRF_SOC_CON2 = 0x10001;
    mmc_init();

    test_item = '\0';
    while( test_item != 'q' ) {
        test_item = test_menu();
        if ( test_item == '1' ) {
            uart_test();
        } else if ( test_item == '2' ) {
            led_test();
        } else if ( test_item == '3' ) {
            button_test();
        } else if ( test_item == '4' ) {
            pwm_led_test();
        } else if ( test_item == '5' ) {
            i2c_lcd_test();
            printf( "press x to exit i2c lcd test\r\n" );
            ch = uart_getc();
        } else if ( test_item == '6' ) {
            tongsong();
        } else if ( test_item == '7' ) {
            servo();
        } else if ( test_item == '8' ) {
            ssd1306_test();
        } else if ( test_item == '9' ) {
            ddr_test();
        } else if ( test_item == 'a' ) {
            mmc_test();
        } else if ( test_item == 'b' ) {
            dmac_test();
        }
    }

    *GPIO1_SWPORTA_DDR = 0x01000000;

    while (1) {
        led_blink( 1000000 );
    }
    return 0;
}
