/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "timer.h"
#include "clock.h"

void rkclk_set_pll( int clk_id )  // 3=GENERAL, 2=CODEC, 1=CLK_DDR, 0=CLK_ARM
{
    if ( clk_id == 3 ) {          // GENERAL, nr=2 nf=GPLL_HZ * nr * no / OSC_HZ no=2
        // enter reset
        *PLL3_CON3 = 0x200020;
        *PLL3_CON0 = ((CLKR_MASK | PLL_OD_MASK) << 16) | ((0x1 << CLKR_SHIFT) | 0x1);
        *PLL3_CON1 = (CLKF_MASK << 16) | 98;
        *PLL3_CON2 = (PLL_BWADJ_MASK << 16) | 48;
        udelay( 10 );
        *PLL3_CON3 = 0x200000;
    } else if ( clk_id == 2 ) {   // CODEC, nr=1 nf=CPLL_HZ * nr * no / OSC_HZ no=2
        // enter reset
        *PLL2_CON3 = 0x200020;
        *PLL2_CON0 = ((CLKR_MASK | PLL_OD_MASK) << 16) | ((0 << CLKR_SHIFT) | 0x1);
        *PLL2_CON1 = (CLKF_MASK << 16) | 31;
        *PLL2_CON2 = (PLL_BWADJ_MASK << 16) | 15;
        udelay( 10 );
        *PLL2_CON3 = 0x200000;
    } else if ( clk_id == 1 ) {   // CLK_DDR533, nr=9 nf=400 no=2
        // enter reset
        *PLL1_CON3 = 0x200020;
        *PLL1_CON0 = ((CLKR_MASK | PLL_OD_MASK) << 16) | ((8 << CLKR_SHIFT) | 0x1);
        *PLL1_CON1 = (CLKF_MASK << 16) | 399;
        *PLL1_CON2 = (PLL_BWADJ_MASK << 16) | 199;
        udelay( 10 );
        *PLL1_CON3 = 0x200000;
    } else if ( clk_id == 0 ) {   // CLK_ARM, nr=1 nf=APLL_HZ * nr * no / OSC_HZ  no=1
        // enter reset
        *PLL0_CON3 = 0x200020;
        *PLL0_CON0 = ((CLKR_MASK | PLL_OD_MASK) << 16) | ((0 << CLKR_SHIFT) | 0x0);
        *PLL0_CON1 = (CLKF_MASK << 16) | 999;
        *PLL0_CON2 = (PLL_BWADJ_MASK << 16) | 499;
        udelay( 10 );
        *PLL0_CON3 = 0x200000;
    }
}

void rkclk_init( void )
{
    int aclk_div;
    int hclk_div;
    int pclk_div;

    // pll enter slow-mode
    *CRU_MODE_CON = ((GPLL_MODE_MASK | CPLL_MODE_MASK) << 16) | (GPLL_MODE_SLOW << GPLL_MODE_SHIFT | CPLL_MODE_SLOW << CPLL_MODE_SHIFT);
    rkclk_set_pll( 3 );
    rkclk_set_pll( 2 );

    // waiting for pll lock
    while ((*GRF_SOC_STATUS1 & (SOCSTS_CPLL_LOCK | SOCSTS_GPLL_LOCK)) != (SOCSTS_CPLL_LOCK | SOCSTS_GPLL_LOCK))
       udelay(1);

    aclk_div = 1; //GPLL_HZ / PD_BUS_ACLK_HZ - 1;
    hclk_div = 1; //PD_BUS_ACLK_HZ / PD_BUS_HCLK_HZ - 1;
    pclk_div = 3; //PD_BUS_ACLK_HZ / PD_BUS_PCLK_HZ - 1;
    *CRU_CLKSEL_CON1 = ((PD_BUS_PCLK_DIV_MASK | PD_BUS_HCLK_DIV_MASK | PD_BUS_ACLK_DIV0_MASK | PD_BUS_ACLK_DIV1_MASK) << 16) | (pclk_div << PD_BUS_PCLK_DIV_SHIFT | hclk_div << PD_BUS_HCLK_DIV_SHIFT | aclk_div << PD_BUS_ACLK_DIV0_SHIFT);

    aclk_div = 3; //GPLL_HZ / PERI_ACLK_HZ - 1;
    hclk_div = 0; //ilog2(PERI_ACLK_HZ / PERI_HCLK_HZ);
    pclk_div = 1; //ilog2(PERI_ACLK_HZ / PERI_PCLK_HZ);
    *CRU_CLKSEL_CON10 = ((PERI_PCLK_DIV_MASK | PERI_HCLK_DIV_MASK | PERI_ACLK_DIV_MASK) << 16) | (PERI_SEL_GPLL << PERI_SEL_PLL_SHIFT | pclk_div << PERI_PCLK_DIV_SHIFT | hclk_div << PERI_HCLK_DIV_SHIFT | aclk_div << PERI_ACLK_DIV_SHIFT);

    // PLL enter normal-mode
    *CRU_MODE_CON = ((GPLL_MODE_MASK | CPLL_MODE_MASK) << 16) | (GPLL_MODE_NORMAL << GPLL_MODE_SHIFT | CPLL_MODE_NORMAL << CPLL_MODE_SHIFT);
}

void rkclk_configure_ddr( void )
{
    // pll enter slow-mode
    *CRU_MODE_CON = (DPLL_MODE_MASK << 16) | (DPLL_MODE_SLOW << DPLL_MODE_SHIFT);
    rkclk_set_pll( 1 );

    // waiting for pll lock
    while (!(*GRF_SOC_STATUS1 & SOCSTS_DPLL_LOCK))
       udelay(1);

    // PLL enter normal-mode
    *CRU_MODE_CON = (DPLL_MODE_MASK << 16) | (DPLL_MODE_NORMAL << DPLL_MODE_SHIFT);
}

