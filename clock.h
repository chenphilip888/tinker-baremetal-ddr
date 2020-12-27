/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "registers.h"

#define APLL_INIT_CFG_NR 1
#define APLL_INIT_CFG_NF 75
#define APLL_INIT_CFG_NO 1
#define GPLL_INIT_CFG_NR 2
#define GPLL_INIT_CFG_NF 99
#define GPLL_INIT_CFG_NO 2
#define CPLL_INIT_CFG_NR 1
#define CPLL_INIT_CFG_NF 32
#define CPLL_INIT_CFG_NO 2
#define CLKR_SHIFT      8
#define CLKR_MASK       0x3f << CLKR_SHIFT
#define PLL_OD_MASK     0x0f
#define CLKF_SHIFT      0
#define CLKF_MASK       0x1fff << CLKF_SHIFT
#define PLL_BWADJ_MASK  0x0fff
#define CRU_MODE_MASK      3
#define DPLL_MODE_SLOW     0
#define DPLL_MODE_SHIFT    4
#define APLL_MODE_SLOW     0
#define APLL_MODE_SHIFT    0
#define GPLL_MODE_SLOW     0
#define GPLL_MODE_SHIFT    0xc
#define CPLL_MODE_SLOW     0
#define CPLL_MODE_SHIFT    8
#define DPLL_MODE_MASK     CRU_MODE_MASK << DPLL_MODE_SHIFT
#define APLL_MODE_MASK     CRU_MODE_MASK << APLL_MODE_SHIFT
#define GPLL_MODE_MASK     CRU_MODE_MASK << GPLL_MODE_SHIFT
#define CPLL_MODE_MASK     CRU_MODE_MASK << CPLL_MODE_SHIFT
#define SOCSTS_DPLL_LOCK   1 << 5
#define SOCSTS_APLL_LOCK   1 << 6
#define SOCSTS_CPLL_LOCK   1 << 7
#define SOCSTS_GPLL_LOCK   1 << 8
#define A17_DIV_SHIFT      8
#define MP_DIV_SHIFT       4
#define M0_DIV_SHIFT       0
#define CORE_SEL_PLL_SHIFT 15
#define CORE_SEL_PLL_MASK  1 << CORE_SEL_PLL_SHIFT
#define A17_DIV_MASK       0x1f << A17_DIV_SHIFT
#define MP_DIV_MASK        0xf << MP_DIV_SHIFT
#define M0_DIV_MASK        0xf << M0_DIV_SHIFT
#define CLK_L2RAM_DIV_SHIFT      0
#define ATCLK_CORE_DIV_CON_SHIFT 4
#define PCLK_CORE_DBG_DIV_SHIFT  9
#define CLK_L2RAM_DIV_MASK       7 << CLK_L2RAM_DIV_SHIFT
#define ATCLK_CORE_DIV_CON_MASK  0x1f << ATCLK_CORE_DIV_CON_SHIFT
#define PCLK_CORE_DBG_DIV_MASK   0x1f << PCLK_CORE_DBG_DIV_SHIFT
#define GPLL_HZ                594000000
#define CPLL_HZ                384000000
#define APLL_HZ               1800000000
#define OSC_HZ                  24000000
#define PD_BUS_ACLK_HZ         297000000
#define PD_BUS_HCLK_HZ         148500000
#define PD_BUS_PCLK_HZ         74250000
#define PD_BUS_PCLK_DIV_SHIFT  12
#define PD_BUS_HCLK_DIV_SHIFT  8
#define PD_BUS_ACLK_DIV0_SHIFT 3
#define PD_BUS_ACLK_DIV1_SHIFT 0
#define PD_BUS_PCLK_DIV_MASK   7 << PD_BUS_PCLK_DIV_SHIFT
#define PD_BUS_HCLK_DIV_MASK   3 << PD_BUS_HCLK_DIV_SHIFT
#define PD_BUS_ACLK_DIV0_MASK  0x1f << PD_BUS_ACLK_DIV0_SHIFT
#define PD_BUS_ACLK_DIV1_MASK  0x7 << PD_BUS_ACLK_DIV1_SHIFT
#define PERI_ACLK_HZ           148500000
#define PERI_HCLK_HZ           148500000
#define PERI_PCLK_HZ           74250000
#define PERI_SEL_GPLL          1
#define PERI_SEL_PLL_SHIFT     15
#define PERI_PCLK_DIV_SHIFT    12
#define PERI_HCLK_DIV_SHIFT    8
#define PERI_ACLK_DIV_SHIFT    0
#define PERI_PCLK_DIV_MASK     3 << PERI_PCLK_DIV_SHIFT
#define PERI_HCLK_DIV_MASK     3 << PERI_HCLK_DIV_SHIFT
#define PERI_ACLK_DIV_MASK     0x1f << PERI_ACLK_DIV_SHIFT
#define DPLL_MODE_NORMAL       1
#define APLL_MODE_NORMAL       1
#define GPLL_MODE_NORMAL       1
#define CPLL_MODE_NORMAL       1

void rkclk_set_pll( int clk_id );
void rkclk_init( void );
void rkclk_configure_ddr( void );

#endif
