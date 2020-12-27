/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "registers.h"
#include "timer.h"
#include "uart.h"
#include "clock.h"
#include "gic.h"
#include "ddr.h"
#include "mmc.h"

void Flash_StartApplication( unsigned int startAddress )
{
    asm volatile("mov SP, r0\n"
                 "mov PC, r0\n"
                 "nop\n"
                 "nop\n");
}

int main() {
        unsigned int i;
        int j;

        uart_init();
        config_GIC( 90, 1 );         // UART3_ISR, CPU0
        timer_init();
        rkclk_init();
        rkclk_configure_ddr();
        udelay( 50000 );

        // initialize ddr
        setup_sdram();
        // Use rkpwm by default
        *GRF_SOC_CON2 = 0x10001;

        mmc_init();
        // start lba #128 for application
        j = 128;
        // load code from sd card to ddr address 0x10000
        for (i=0x10000; i<0x18000; i=i+512) {
            mmc_bread( (char *)i, j, 1 );
            j = j + 1;
        }
        mmc_go_idle();

        udelay( 10000 );
        Flash_StartApplication( (unsigned int)0x10000 );

        return 0;
}
