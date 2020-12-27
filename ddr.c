/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "ddr.h"
#include "timer.h"
#include "uart.h"

const unsigned int src[] = { 0x215, 0xc8, 0x0, 0x35, 0x26, 0x2, 0x70, 0x2000d, 0x6, 0x0, 0x8, 0x4, 0x17, 0x24, 0xd, 0x6, 0x4, 0x8, 0x4, 0x76, 0x4, 0x0, 0x30, 0x0, 0x1, 0x2, 0x2, 0x4, 0x0, 0x0, 0xc0, 0x4, 0x8, 0x1f4 };

const int ddrconf_table[] = {
        /* row      col,bw */
        0,
        ((1 << DDRCONF_ROW_SHIFT) | 1 << DDRCONF_COL_SHIFT),
        ((2 << DDRCONF_ROW_SHIFT) | 1 << DDRCONF_COL_SHIFT),
        ((3 << DDRCONF_ROW_SHIFT) | 1 << DDRCONF_COL_SHIFT),
        ((4 << DDRCONF_ROW_SHIFT) | 1 << DDRCONF_COL_SHIFT),
        ((1 << DDRCONF_ROW_SHIFT) | 2 << DDRCONF_COL_SHIFT),
        ((2 << DDRCONF_ROW_SHIFT) | 2 << DDRCONF_COL_SHIFT),
        ((3 << DDRCONF_ROW_SHIFT) | 2 << DDRCONF_COL_SHIFT),
        ((1 << DDRCONF_ROW_SHIFT) | 0 << DDRCONF_COL_SHIFT),
        ((2 << DDRCONF_ROW_SHIFT) | 0 << DDRCONF_COL_SHIFT),
        ((3 << DDRCONF_ROW_SHIFT) | 0 << DDRCONF_COL_SHIFT),
        0,
        0,
        0,
        0,
        ((4 << 4) | 2),
};

void dfi_cfg( int channel )
{
    if ( channel == 0 ) {
        *ddr_pctl0_dfistcfg0 = DFI_INIT_START;
        *ddr_pctl0_dfistcfg1 = DFI_DRAM_CLK_SR_EN | DFI_DRAM_CLK_DPD_EN;
        *ddr_pctl0_dfistcfg2 = DFI_PARITY_INTR_EN | DFI_PARITY_EN;
        *ddr_pctl0_dfilpcfg0 = (7 << TLP_RESP_TIME_SHIFT) | LP_SR_EN | LP_PD_EN;
        *ddr_pctl0_dfitctrldelay = (2 << TCTRL_DELAY_TIME_SHIFT);
        *ddr_pctl0_dfitphywrdata = (1 << TPHY_WRDATA_TIME_SHIFT);
        *ddr_pctl0_dfitphyrdlat = (0xf << TPHY_RDLAT_TIME_SHIFT);
        *ddr_pctl0_dfitdramclkdis = (2 << TDRAM_CLK_DIS_TIME_SHIFT);
        *ddr_pctl0_dfitdramclken = (2 << TDRAM_CLK_EN_TIME_SHIFT);
        *ddr_pctl0_dfitphyupdtype0 = 0x1;
        /* cs0 and cs1 write odt enable */
        *ddr_pctl0_dfiodtcfg = RANK0_ODT_WRITE_SEL | RANK1_ODT_WRITE_SEL;
        /* odt write length */
        *ddr_pctl0_dfiodtcfg1 = (7 << ODT_LEN_BL8_W_SHIFT);
        /* phyupd and ctrlupd disabled */
        *ddr_pctl0_dfiupdcfg = 0x0;
    } else {
        *ddr_pctl1_dfistcfg0 = DFI_INIT_START;
        *ddr_pctl1_dfistcfg1 = DFI_DRAM_CLK_SR_EN | DFI_DRAM_CLK_DPD_EN;
        *ddr_pctl1_dfistcfg2 = DFI_PARITY_INTR_EN | DFI_PARITY_EN;
        *ddr_pctl1_dfilpcfg0 = (7 << TLP_RESP_TIME_SHIFT) | LP_SR_EN | LP_PD_EN;
        *ddr_pctl1_dfitctrldelay = (2 << TCTRL_DELAY_TIME_SHIFT);
        *ddr_pctl1_dfitphywrdata = (1 << TPHY_WRDATA_TIME_SHIFT);
        *ddr_pctl1_dfitphyrdlat = (0xf << TPHY_RDLAT_TIME_SHIFT);
        *ddr_pctl1_dfitdramclkdis = (2 << TDRAM_CLK_DIS_TIME_SHIFT);
        *ddr_pctl1_dfitdramclken = (2 << TDRAM_CLK_EN_TIME_SHIFT);
        *ddr_pctl1_dfitphyupdtype0 = 0x1;
        /* cs0 and cs1 write odt enable */
        *ddr_pctl1_dfiodtcfg = RANK0_ODT_WRITE_SEL | RANK1_ODT_WRITE_SEL;
        /* odt write length */
        *ddr_pctl1_dfiodtcfg1 = (7 << ODT_LEN_BL8_W_SHIFT);
        /* phyupd and ctrlupd disabled */
        *ddr_pctl1_dfiupdcfg = 0x0;
    }
}

void ddr_set_enable( int channel, int enable )
{
    unsigned int val;

    val = 0;
    if ( enable ) {
        val = 1 << (channel ? DDR1_16BIT_EN_SHIFT : DDR0_16BIT_EN_SHIFT);
    }
    *GRF_SOC_CON0 = ( ( 1 << (channel ? DDR1_16BIT_EN_SHIFT : DDR0_16BIT_EN_SHIFT) | val ) << 16 ) | val;
}

void ddr_set_ddr3_mode( int channel, int ddr3_mode )
{
    unsigned int val;
    unsigned int mask;

    mask = 1 << (channel ? MSCH1_MAINDDR3_SHIFT : MSCH0_MAINDDR3_SHIFT);
    val = ddr3_mode << (channel ? MSCH1_MAINDDR3_SHIFT : MSCH0_MAINDDR3_SHIFT);
    *GRF_SOC_CON0 = ( ( mask | val ) << 16 ) | val;
}

void ddr_set_en_bst_odt( int channel, int enable, int enable_bst, int enable_odt )
{
    unsigned int mask;
    unsigned int val;
    int disable_bst;

    if ( enable_bst == 0 )
        disable_bst = 1;
    else
        disable_bst = 0;
    mask = channel ? (1 << LPDDR3_EN1_SHIFT | 1 << UPCTL1_BST_DIABLE_SHIFT | 1 << UPCTL1_LPDDR3_ODT_EN_SHIFT) : (1 << LPDDR3_EN0_SHIFT | 1 << UPCTL0_BST_DIABLE_SHIFT | 1 << UPCTL0_LPDDR3_ODT_EN_SHIFT);
    val = ( enable << (channel ? LPDDR3_EN1_SHIFT : LPDDR3_EN0_SHIFT) | disable_bst << (channel ? UPCTL1_BST_DIABLE_SHIFT : UPCTL0_BST_DIABLE_SHIFT) | enable_odt << (channel ? UPCTL1_LPDDR3_ODT_EN_SHIFT : UPCTL0_LPDDR3_ODT_EN_SHIFT) ); 
    *GRF_SOC_CON2 = ( ( mask | val ) << 16 ) | val;
}

void pctl_cfg( int channel )
{
    unsigned int burstlen;
    unsigned int i;
    int j;

    burstlen = (params.base.noc_timing >> 18) & 0x7;
    if ( channel == 0 ) {
        j = 0;
        for (i=0xff6100c0; i < 0xff610148; i = i + 4) {
            *(volatile unsigned int *)i = src[j];
            j++;
        }

        *ddr_pctl0_dfitrddataen = 0x7; //params.pctl_timing.tcl - 1;
        *ddr_pctl0_dfitphywrlat = 0x4; //params.pctl_timing.tcwl;
        burstlen = burstlen >> 1;
        *ddr_pctl0_mcfg = ( LPDDR2_S4 | 0 << MDDR_LPDDR2_CLK_STOP_IDLE_SHIFT | LPDDR2_EN | burstlen << BURSTLENGTH_SHIFT | (6 - 4) << TFAW_SHIFT | PD_EXIT_FAST | 1 << PD_TYPE_SHIFT | 0 << PD_IDLE_SHIFT );
        ddr_set_ddr3_mode( channel, 0 );
        ddr_set_enable( channel, 1 );
        ddr_set_en_bst_odt( channel, 1, 0, params.base.odt );
        setbits_le32( ddr_pctl0_scfg, 1 );
    } else {
        j = 0;
        for (i=0xff6300c0; i < 0xff630148; i = i + 4) {
            *(volatile unsigned int *)i = src[j];
            j++;
        }

        *ddr_pctl1_dfitrddataen = 0x7; //params.pctl_timing.tcl - 1;
        *ddr_pctl1_dfitphywrlat = 0x4; //params.pctl_timing.tcwl;
        burstlen = burstlen >> 1;
        *ddr_pctl1_mcfg = ( LPDDR2_S4 | 0 << MDDR_LPDDR2_CLK_STOP_IDLE_SHIFT | LPDDR2_EN | burstlen << BURSTLENGTH_SHIFT | (6 - 4) << TFAW_SHIFT | PD_EXIT_FAST | 1 << PD_TYPE_SHIFT | 0 << PD_IDLE_SHIFT );
        ddr_set_ddr3_mode( channel, 0 );
        ddr_set_enable( channel, 1 );
        ddr_set_en_bst_odt( channel, 1, 0, params.base.odt );
        setbits_le32( ddr_pctl1_scfg, 1 );
    }
}

void ddr_reset( int channel, int ctl, int phy )
{
    unsigned int phy_ctl_srstn_shift;
    unsigned int ctl_psrstn_shift;
    unsigned int ctl_srstn_shift;
    unsigned int phy_psrstn_shift;
    unsigned int phy_srstn_shift;

    if ( channel == 0 ) {
        phy_ctl_srstn_shift = 4;
        ctl_psrstn_shift = 3;
        ctl_srstn_shift = 2;
        phy_psrstn_shift = 1;
        phy_srstn_shift = 0;
    } else {
        phy_ctl_srstn_shift = 9;
        ctl_psrstn_shift = 8;
        ctl_srstn_shift = 7;
        phy_psrstn_shift = 6;
        phy_srstn_shift = 5;
    }

    *CRU_SOFTRST_CON10 = ( ( ( 1 << phy_ctl_srstn_shift | 1 << ctl_psrstn_shift | 1 << ctl_srstn_shift | 1 << phy_psrstn_shift | 1 << phy_srstn_shift ) | ( phy << phy_ctl_srstn_shift | ctl << ctl_psrstn_shift | ctl << ctl_srstn_shift | phy << phy_psrstn_shift | phy << phy_srstn_shift ) ) << 16 ) | ( phy << phy_ctl_srstn_shift | ctl << ctl_psrstn_shift | ctl << ctl_srstn_shift | phy << phy_psrstn_shift | phy << phy_srstn_shift ); 
}

void ddr_phy_ctl_reset( int channel, int n )
{
    if ( channel == 0 ) {
        *CRU_SOFTRST_CON10 = ( ( 1 << 4 | n << 4 ) << 16 ) | n << 4;
    } else {
        *CRU_SOFTRST_CON10 = ( ( 1 << 9 | n << 9 ) << 16 ) | n << 9;
    }    
}

void phy_pctrl_reset( int channel )
{
    ddr_reset( channel, 1, 1 );
    udelay( 1 );
    if ( channel == 0 ) {
        clrbits_le32(ddr_publ0_acdllcr, ACDLLCR_DLLSRST);
        clrbits_le32(ddr_publ0_dx0dllcr, DXDLLCR_DLLSRST);
        clrbits_le32(ddr_publ0_dx1dllcr, DXDLLCR_DLLSRST);
        clrbits_le32(ddr_publ0_dx2dllcr, DXDLLCR_DLLSRST);
        clrbits_le32(ddr_publ0_dx3dllcr, DXDLLCR_DLLSRST);
        udelay( 10 );
        setbits_le32(ddr_publ0_acdllcr, ACDLLCR_DLLSRST);
        setbits_le32(ddr_publ0_dx0dllcr, DXDLLCR_DLLSRST);
        setbits_le32(ddr_publ0_dx1dllcr, DXDLLCR_DLLSRST);
        setbits_le32(ddr_publ0_dx2dllcr, DXDLLCR_DLLSRST);
        setbits_le32(ddr_publ0_dx3dllcr, DXDLLCR_DLLSRST);
    } else {
        clrbits_le32(ddr_publ1_acdllcr, ACDLLCR_DLLSRST);
        clrbits_le32(ddr_publ1_dx0dllcr, DXDLLCR_DLLSRST);
        clrbits_le32(ddr_publ1_dx1dllcr, DXDLLCR_DLLSRST);
        clrbits_le32(ddr_publ1_dx2dllcr, DXDLLCR_DLLSRST);
        clrbits_le32(ddr_publ1_dx3dllcr, DXDLLCR_DLLSRST);
        udelay( 10 );
        setbits_le32(ddr_publ1_acdllcr, ACDLLCR_DLLSRST);
        setbits_le32(ddr_publ1_dx0dllcr, DXDLLCR_DLLSRST);
        setbits_le32(ddr_publ1_dx1dllcr, DXDLLCR_DLLSRST);
        setbits_le32(ddr_publ1_dx2dllcr, DXDLLCR_DLLSRST);
        setbits_le32(ddr_publ1_dx3dllcr, DXDLLCR_DLLSRST);
    }
    udelay( 10 );
    ddr_reset( channel, 1, 0 );
    udelay( 10 );
    ddr_reset( channel, 0, 0 );
    udelay( 10 );
}

void phy_cfg( int channel )
{
    unsigned int tmp;
    unsigned int dinit2;

    dinit2 = 106600;  // 533 * 200000

    /* DDR PHY Timing */
    if ( channel == 0 ) {
        *ddr_publ0_dtpr0 = 0x48d7dd93;
        *ddr_publ0_dtpr1 = 0x187008d8;
        *ddr_publ0_dtpr2 = 0x121076;
        *ddr_publ0_mr0 = 0x0;
        *ddr_publ0_mr1 = 0xc3;
        *ddr_publ0_mr2 = 0x6;
        *ddr_publ0_mr3 = 0x2;
        *ddr_msch0_ddrtiming = params.base.noc_timing;
        *ddr_msch0_readlatency = 0x3f;
        *ddr_msch0_activate = params.base.noc_activate;
        *ddr_msch0_devtodev = (2 << BUSWRTORD_SHIFT | 2 << BUSRDTOWR_SHIFT | 1 << BUSRDTORD_SHIFT);
        *ddr_publ0_ptr0 = ( 2729 << PRT_DLLLOCK_SHIFT | 27 << PRT_DLLSRST_SHIFT | 8 << PRT_ITMSRST_SHIFT );
        *ddr_publ0_ptr1 = ( 266500 << PRT_DINIT0_SHIFT | 214 << PRT_DINIT1_SHIFT );
        *ddr_publ0_ptr2 = ( 106600 << PRT_DINIT2_SHIFT | 533 << PRT_DINIT3_SHIFT );
        clrsetbits_le32(ddr_publ0_pgcr, 0x1F, ( 0 << PGCR_DFTLMT_SHIFT | 0 << PGCR_DFTCMP_SHIFT | 1 << PGCR_DQSCFG_SHIFT | 0 << PGCR_ITMDMD_SHIFT) );
        /* DDRMODE select LPDDR3 */
        clrsetbits_le32(ddr_publ0_dcr, DDRMD_MASK << DDRMD_SHIFT, DDRMD_LPDDR2_LPDDR3 << DDRMD_SHIFT);
        clrsetbits_le32(ddr_publ0_dxccr, ( DQSNRES_MASK << DQSNRES_SHIFT | DQSRES_MASK << DQSRES_SHIFT ), ( 4 << DQSRES_SHIFT | 0xc << DQSNRES_SHIFT) );
        tmp = *ddr_publ0_dtpr1;
        tmp = ((tmp >> TDQSCKMAX_SHIFT) & TDQSCKMAX_MASK) - ((tmp >> TDQSCK_SHIFT) & TDQSCK_MASK);
        clrsetbits_le32(ddr_publ0_dsgcr, ( DQSGE_MASK << DQSGE_SHIFT | DQSGX_MASK << DQSGX_SHIFT ), ( tmp << DQSGE_SHIFT | tmp << DQSGX_SHIFT) );
        if ( params.base.odt ) {
            /*dynamic RTT enable */
            setbits_le32(ddr_publ0_dx0gcr, ( DQSRTT | DQRTT) );
            setbits_le32(ddr_publ0_dx1gcr, ( DQSRTT | DQRTT) );
            setbits_le32(ddr_publ0_dx2gcr, ( DQSRTT | DQRTT) );
            setbits_le32(ddr_publ0_dx3gcr, ( DQSRTT | DQRTT) );
        } else {
            /*dynamic RTT disable */
            clrbits_le32(ddr_publ0_dx0gcr, ( DQSRTT | DQRTT) );
            clrbits_le32(ddr_publ0_dx1gcr, ( DQSRTT | DQRTT) );
            clrbits_le32(ddr_publ0_dx2gcr, ( DQSRTT | DQRTT) );
            clrbits_le32(ddr_publ0_dx3gcr, ( DQSRTT | DQRTT) );
        }
    } else {
        *ddr_publ1_dtpr0 = 0x48d7dd93;
        *ddr_publ1_dtpr1 = 0x187008d8;
        *ddr_publ1_dtpr2 = 0x121076;
        *ddr_publ1_mr0 = 0x0;
        *ddr_publ1_mr1 = 0xc3;
        *ddr_publ1_mr2 = 0x6;
        *ddr_publ1_mr3 = 0x2;
        *ddr_msch1_ddrtiming = params.base.noc_timing;
        *ddr_msch1_readlatency = 0x3f;
        *ddr_msch1_activate = params.base.noc_activate;
        *ddr_msch1_devtodev = (2 << BUSWRTORD_SHIFT | 2 << BUSRDTOWR_SHIFT | 1 << BUSRDTORD_SHIFT);
        *ddr_publ1_ptr0 = ( 2729 << PRT_DLLLOCK_SHIFT | 27 << PRT_DLLSRST_SHIFT | 8 << PRT_ITMSRST_SHIFT );
        *ddr_publ1_ptr1 = ( 266500 << PRT_DINIT0_SHIFT | 214 << PRT_DINIT1_SHIFT );
        *ddr_publ1_ptr2 = ( 106600 << PRT_DINIT2_SHIFT | 533 << PRT_DINIT3_SHIFT );
        clrsetbits_le32(ddr_publ1_pgcr, 0x1F, ( 0 << PGCR_DFTLMT_SHIFT | 0 << PGCR_DFTCMP_SHIFT | 1 << PGCR_DQSCFG_SHIFT | 0 << PGCR_ITMDMD_SHIFT) );
        /* DDRMODE select LPDDR3 */
        clrsetbits_le32(ddr_publ1_dcr, DDRMD_MASK << DDRMD_SHIFT, DDRMD_LPDDR2_LPDDR3 << DDRMD_SHIFT);
        clrsetbits_le32(ddr_publ1_dxccr, ( DQSNRES_MASK << DQSNRES_SHIFT | DQSRES_MASK << DQSRES_SHIFT ), ( 4 << DQSRES_SHIFT | 0xc << DQSNRES_SHIFT) );
        tmp = *ddr_publ1_dtpr1;
        tmp = ((tmp >> TDQSCKMAX_SHIFT) & TDQSCKMAX_MASK) - ((tmp >> TDQSCK_SHIFT) & TDQSCK_MASK);
        clrsetbits_le32(ddr_publ1_dsgcr, ( DQSGE_MASK << DQSGE_SHIFT | DQSGX_MASK << DQSGX_SHIFT ), ( tmp << DQSGE_SHIFT | tmp << DQSGX_SHIFT) );
        if ( params.base.odt ) {
            /*dynamic RTT enable */
            setbits_le32(ddr_publ1_dx0gcr, ( DQSRTT | DQRTT) );
            setbits_le32(ddr_publ1_dx1gcr, ( DQSRTT | DQRTT) );
            setbits_le32(ddr_publ1_dx2gcr, ( DQSRTT | DQRTT) );
            setbits_le32(ddr_publ1_dx3gcr, ( DQSRTT | DQRTT) );
        } else {
            /*dynamic RTT disable */
            clrbits_le32(ddr_publ1_dx0gcr, ( DQSRTT | DQRTT) );
            clrbits_le32(ddr_publ1_dx1gcr, ( DQSRTT | DQRTT) );
            clrbits_le32(ddr_publ1_dx2gcr, ( DQSRTT | DQRTT) );
            clrbits_le32(ddr_publ1_dx3gcr, ( DQSRTT | DQRTT) );
        }
    }
}

void phy_dll_bypass_set( int channel )
{
    if ( channel == 0 ) {
        clrbits_le32(ddr_publ0_dllgcr, SBIAS_BYPASS);
        clrbits_le32(ddr_publ0_acdllcr, ACDLLCR_DLLDIS);
        clrbits_le32(ddr_publ0_dx0dllcr, DXDLLCR_DLLDIS);
        clrbits_le32(ddr_publ0_dx1dllcr, DXDLLCR_DLLDIS);
        clrbits_le32(ddr_publ0_dx2dllcr, DXDLLCR_DLLDIS);
        clrbits_le32(ddr_publ0_dx3dllcr, DXDLLCR_DLLDIS);
        clrbits_le32(ddr_publ0_pir, PIR_DLLBYP);
    } else {
        clrbits_le32(ddr_publ1_dllgcr, SBIAS_BYPASS);
        clrbits_le32(ddr_publ1_acdllcr, ACDLLCR_DLLDIS);
        clrbits_le32(ddr_publ1_dx0dllcr, DXDLLCR_DLLDIS);
        clrbits_le32(ddr_publ1_dx1dllcr, DXDLLCR_DLLDIS);
        clrbits_le32(ddr_publ1_dx2dllcr, DXDLLCR_DLLDIS);
        clrbits_le32(ddr_publ1_dx3dllcr, DXDLLCR_DLLDIS);
        clrbits_le32(ddr_publ1_pir, PIR_DLLBYP);
    }
}

void phy_init( int channel )
{
    if ( channel == 0 ) {
        setbits_le32(ddr_publ0_pir, ( PIR_INIT | PIR_DLLSRST | PIR_DLLLOCK | PIR_ZCAL | PIR_ITMSRST | PIR_CLRSR) );
        udelay( 1 );
        while ( (*ddr_publ0_pgsr & (PGSR_IDONE | PGSR_DLDONE | PGSR_ZCDONE)) != (PGSR_IDONE | PGSR_DLDONE | PGSR_ZCDONE) );
    } else {
        setbits_le32(ddr_publ1_pir, ( PIR_INIT | PIR_DLLSRST | PIR_DLLLOCK | PIR_ZCAL | PIR_ITMSRST | PIR_CLRSR) );
        udelay( 1 );
        while ( (*ddr_publ1_pgsr & (PGSR_IDONE | PGSR_DLDONE | PGSR_ZCDONE)) != (PGSR_IDONE | PGSR_DLDONE | PGSR_ZCDONE) );
    }
}

void memory_init( int channel )
{
    if ( channel == 0 ) {
        setbits_le32( ddr_publ0_pir, (PIR_INIT | PIR_DRAMINIT | PIR_LOCKBYP | PIR_ZCALBYP | PIR_CLRSR | PIR_ICPC) );
        udelay( 1 );
        while( (*ddr_publ0_pgsr & (PGSR_IDONE | PGSR_DLDONE)) != (PGSR_IDONE | PGSR_DLDONE) );
    } else {
        setbits_le32( ddr_publ1_pir, (PIR_INIT | PIR_DRAMINIT | PIR_LOCKBYP | PIR_ZCALBYP | PIR_CLRSR | PIR_ICPC) );
        udelay( 1 );
        while( (*ddr_publ1_pgsr & (PGSR_IDONE | PGSR_DLDONE)) != (PGSR_IDONE | PGSR_DLDONE) );
    }
}

void move_to_config_state( int channel )
{
    unsigned int state;

    while( 1 ) {
        if ( channel == 0 ) {
            state = *ddr_pctl0_stat & PCTL_STAT_MSK;
            switch (state) {
            case LOW_POWER:
                *ddr_pctl0_sctl = WAKEUP_STATE;
                while( (*ddr_pctl0_stat & PCTL_STAT_MSK) != ACCESS );
                /* wait DLL lock */
                while( (*ddr_publ0_pgsr & PGSR_DLDONE) != PGSR_DLDONE );
            case ACCESS:
            case INIT_MEM:
                *ddr_pctl0_sctl = CFG_STATE;
                while( (*ddr_pctl0_stat & PCTL_STAT_MSK) != CONFIG );
                break;
            case CONFIG:
                return;
            default:
                break;
            }
        } else {
            state = *ddr_pctl1_stat & PCTL_STAT_MSK;
            switch (state) {
            case LOW_POWER:
                *ddr_pctl1_sctl = WAKEUP_STATE;
                while( (*ddr_pctl1_stat & PCTL_STAT_MSK) != ACCESS );
                /* wait DLL lock */
                while( (*ddr_publ1_pgsr & PGSR_DLDONE) != PGSR_DLDONE );
            case ACCESS:
            case INIT_MEM:
                *ddr_pctl1_sctl = CFG_STATE;
                while( (*ddr_pctl1_stat & PCTL_STAT_MSK) != CONFIG );
                break;
            case CONFIG:
                return;
            default:
                break;
            }
        } 
    }
}

void send_command( int channel, int rank, int cmd, int arg )
{
    if ( channel == 0 ) {
        *ddr_pctl0_mcmd = (START_CMD | (rank << 20) | arg | cmd);
        udelay( 1 );
        while( *ddr_pctl0_mcmd & START_CMD );
    } else {
        *ddr_pctl1_mcmd = (START_CMD | (rank << 20) | arg | cmd);
        udelay( 1 );
        while( *ddr_pctl1_mcmd & START_CMD );
    }
}

void send_command_op( int channel, int rank, int cmd, int ma, int op )
{
    send_command( channel, rank, cmd, ((ma & LPDDR2_MA_MASK) << LPDDR2_MA_SHIFT | (op & LPDDR2_OP_MASK) << LPDDR2_OP_SHIFT) );
}

void set_bandwidth_ratio( int channel, int n )
{
    if ( channel == 0 ) {
        if (n == 1) {
            printf( "channel 0 error, n is 1\r\n");
            setbits_le32( ddr_pctl0_ppcfg, 1 );
            *GRF_SOC_CON0 = ( (1 << 8 ) << 16 ) | (1 << 8 ); 
            *ddr_msch0_ddrtiming |= (1 << 31);
            /* Data Byte disable*/
            clrbits_le32( ddr_publ0_dx2gcr, 1 );
            clrbits_le32( ddr_publ0_dx3gcr, 1 );
            /* disable DLL */
            setbits_le32( ddr_publ0_dx2dllcr, DXDLLCR_DLLDIS );
            setbits_le32( ddr_publ0_dx3dllcr, DXDLLCR_DLLDIS );
        } else {
            clrbits_le32( ddr_pctl0_ppcfg, 1 );
            *GRF_SOC_CON0 = (1 << 8 ) << 16;
            *ddr_msch0_ddrtiming &= ~(1 << 31);
            /* Data Byte enable*/
            setbits_le32( ddr_publ0_dx2gcr, 1 );
            setbits_le32( ddr_publ0_dx3gcr, 1 );
            /* enable DLL */
            clrbits_le32( ddr_publ0_dx2dllcr, DXDLLCR_DLLDIS );
            clrbits_le32( ddr_publ0_dx3dllcr, DXDLLCR_DLLDIS );
            /* reset DLL */
            clrbits_le32( ddr_publ0_dx2dllcr, DXDLLCR_DLLSRST );
            clrbits_le32( ddr_publ0_dx3dllcr, DXDLLCR_DLLSRST );
            udelay( 10 );
            setbits_le32( ddr_publ0_dx2dllcr, DXDLLCR_DLLSRST );
            setbits_le32( ddr_publ0_dx3dllcr, DXDLLCR_DLLSRST );
        }
        setbits_le32( ddr_pctl0_dfistcfg0, 1 << 2 );
    } else {
        if (n == 1) {
            printf( "channel 1 error, n is 1\r\n");
            setbits_le32( ddr_pctl1_ppcfg, 1 );
            *GRF_SOC_CON0 = ( (1 << 9 ) << 16 ) | (1 << 9 ); 
            *ddr_msch1_ddrtiming |= (1 << 31);
            /* Data Byte disable*/
            clrbits_le32( ddr_publ1_dx2gcr, 1 );
            clrbits_le32( ddr_publ1_dx3gcr, 1 );
            /* disable DLL */
            setbits_le32( ddr_publ1_dx2dllcr, DXDLLCR_DLLDIS );
            setbits_le32( ddr_publ1_dx3dllcr, DXDLLCR_DLLDIS );
        } else {
            clrbits_le32( ddr_pctl1_ppcfg, 1 );
            *GRF_SOC_CON0 = (1 << 9 ) << 16;
            *ddr_msch1_ddrtiming &= ~(1 << 31);
            /* Data Byte enable*/
            setbits_le32( ddr_publ1_dx2gcr, 1 );
            setbits_le32( ddr_publ1_dx3gcr, 1 );
            /* enable DLL */
            clrbits_le32( ddr_publ1_dx2dllcr, DXDLLCR_DLLDIS );
            clrbits_le32( ddr_publ1_dx3dllcr, DXDLLCR_DLLDIS );
            /* reset DLL */
            clrbits_le32( ddr_publ1_dx2dllcr, DXDLLCR_DLLSRST );
            clrbits_le32( ddr_publ1_dx3dllcr, DXDLLCR_DLLSRST );
            udelay( 10 );
            setbits_le32( ddr_publ1_dx2dllcr, DXDLLCR_DLLSRST );
            setbits_le32( ddr_publ1_dx3dllcr, DXDLLCR_DLLSRST );
        }
        setbits_le32( ddr_pctl1_dfistcfg0, 1 << 2 );
    }
}

int data_training( int channel )
{
    unsigned int j;
    int ret;
    unsigned int rank;
    int i;
    unsigned int step[2] = { PIR_QSTRN, PIR_RVTRN };

    ret = 0;
    if ( channel == 0 ) {
        /* disable auto refresh */
        *ddr_pctl0_trefi = 0x0;
        rank = params.ch[0].rank | 1;
        for (j = 0; j < ARRAY_SIZE(step); j++) {
            setbits_le32( ddr_publ0_pir, PIR_CLRSR );
            /* trigger DTT */
            setbits_le32( ddr_publ0_pir, (PIR_INIT | step[j] | PIR_LOCKBYP | PIR_ZCALBYP | PIR_CLRSR) );
            udelay( 1 );
            /* wait echo byte DTDONE */
            while( (*ddr_publ0_dx0gsr0 & rank) != rank );
            while( (*ddr_publ0_dx1gsr0 & rank) != rank );
            if ( !(*ddr_pctl0_ppcfg & 0x1) ) {
                while( (*ddr_publ0_dx2gsr0 & rank) != rank );
                while( (*ddr_publ0_dx3gsr0 & rank) != rank );
            }
            if ( *ddr_publ0_pgsr & (PGSR_DTERR | PGSR_RVERR | PGSR_RVEIRR) ) {
                ret = -1;
                break;
            }
        }
        /* send some auto refresh to complement the lost while DTT */
        for (i = 0; i < (rank > 1 ? 8 : 4); i++)
            send_command( channel, rank, REF_CMD, 0 );
        /* resume auto refresh */
        *ddr_pctl0_trefi = 0x26;
    } else {
        /* disable auto refresh */
        *ddr_pctl1_trefi = 0x0;
        rank = params.ch[1].rank | 1;
        for (j = 0; j < ARRAY_SIZE(step); j++) {
            setbits_le32( ddr_publ1_pir, PIR_CLRSR );
            /* trigger DTT */
            setbits_le32( ddr_publ1_pir, (PIR_INIT | step[j] | PIR_LOCKBYP | PIR_ZCALBYP | PIR_CLRSR) );
            udelay( 1 );
            /* wait echo byte DTDONE */
            while( (*ddr_publ1_dx0gsr0 & rank) != rank );
            while( (*ddr_publ1_dx1gsr0 & rank) != rank );
            if ( !(*ddr_pctl1_ppcfg & 0x1) ) {
                while( (*ddr_publ1_dx2gsr0 & rank) != rank );
                while( (*ddr_publ1_dx3gsr0 & rank) != rank );
            }
            if ( *ddr_publ1_pgsr & (PGSR_DTERR | PGSR_RVERR | PGSR_RVEIRR) ) {
                ret = -1;
                break;
            }
        }
        /* send some auto refresh to complement the lost while DTT */
        for (i = 0; i < (rank > 1 ? 8 : 4); i++)
            send_command( channel, rank, REF_CMD, 0 );
        /* resume auto refresh */
        *ddr_pctl1_trefi = 0x26;
    }

    return ret;
}

void move_to_access_state( int channel )
{
    unsigned int state;

    while (1) {
        if ( channel == 0 ) {
            state = *ddr_pctl0_stat & PCTL_STAT_MSK;
    
            switch (state) {
                case LOW_POWER:
                    if ( (*ddr_pctl0_stat >> LP_TRIG_SHIFT) & LP_TRIG_MASK )
                        return;
                    *ddr_pctl0_sctl = WAKEUP_STATE;
                    while( (*ddr_pctl0_stat & PCTL_STAT_MSK) != ACCESS );
                    /* wait DLL lock */
                    while( (*ddr_publ0_pgsr & PGSR_DLDONE) != PGSR_DLDONE );
                    break;
                case INIT_MEM:
                    *ddr_pctl0_sctl = CFG_STATE;
                    while ( (*ddr_pctl0_stat & PCTL_STAT_MSK) != CONFIG );
                case CONFIG:
                    *ddr_pctl0_sctl = GO_STATE;
                    while ( (*ddr_pctl0_stat & PCTL_STAT_MSK) == CONFIG );
                    break;
                case ACCESS:
                    return;
                default:
                    break;
            }
        } else {
            state = *ddr_pctl1_stat & PCTL_STAT_MSK;
    
            switch (state) {
                case LOW_POWER:
                    if ( (*ddr_pctl1_stat >> LP_TRIG_SHIFT) & LP_TRIG_MASK )
                        return;
                    *ddr_pctl1_sctl = WAKEUP_STATE;
                    while( (*ddr_pctl1_stat & PCTL_STAT_MSK) != ACCESS );
                    /* wait DLL lock */
                    while( (*ddr_publ1_pgsr & PGSR_DLDONE) != PGSR_DLDONE );
                    break;
                case INIT_MEM:
                    *ddr_pctl1_sctl = CFG_STATE;
                    while ( (*ddr_pctl1_stat & PCTL_STAT_MSK) != CONFIG );
                case CONFIG:
                    *ddr_pctl1_sctl = GO_STATE;
                    while ( (*ddr_pctl1_stat & PCTL_STAT_MSK) == CONFIG );
                    break;
                case ACCESS:
                    return;
                default:
                    break;
            }
        }
    }
}

int sdram_rank_bw_detect( int channel )
{
    int need_trainig;

    need_trainig = 0;
    if ( channel == 0 ) {
        if ( data_training( 0 ) < 0 ) {
            printf( "data_training channel0 failed !\r\n");
            /* Check the result for rank 0 */
            if (*ddr_publ0_dx0gsr0 & DQS_GATE_TRAINING_ERROR_RANK0) {
                printf( "data training fail!\r\n");
                return -1;
            }
     
            /* Check the result for rank 1 */
            if (*ddr_publ0_dx0gsr0 & DQS_GATE_TRAINING_ERROR_RANK1) {
                params.ch[0].rank = 1;
                clrsetbits_le32( ddr_publ0_pgcr, 0xF << 18, params.ch[0].rank << 18 );
                need_trainig = 1;
            }
            if (*ddr_publ0_dx2gsr0 & (1 << 4)) {
                params.ch[0].bw = 1;
                set_bandwidth_ratio( 0, params.ch[0].bw );
                need_trainig = 1;
            }
        }
        /* Assume the Die bit width are the same with the chip bit width */
        params.ch[0].dbw = params.ch[0].bw;

        if (need_trainig && (data_training( 0 ) < 0)) {
            ddr_phy_ctl_reset( 0, 1 );
            udelay( 10 );
            ddr_phy_ctl_reset( 0, 0 );
            udelay( 10 );
            printf( "2nd data training channel0 failed!\r\n");
            return -1;
        } else {
            printf( "data_training channel0 passed !\r\n");
        }
    } else {
        if ( data_training( 1 ) < 0 ) {
            printf( "data_training channel1 failed !\r\n");
            /* Check the result for rank 0 */
            if (*ddr_publ1_dx0gsr0 & DQS_GATE_TRAINING_ERROR_RANK0) {
                params.num_channels = 1;
            }
     
            /* Check the result for rank 1 */
            if (*ddr_publ1_dx0gsr0 & DQS_GATE_TRAINING_ERROR_RANK1) {
                params.ch[1].rank = 1;
                clrsetbits_le32( ddr_publ1_pgcr, 0xF << 18, params.ch[channel].rank << 18 );
                need_trainig = 1;
            }
            if (*ddr_publ1_dx2gsr0 & (1 << 4)) {
                params.ch[1].bw = 1;
                set_bandwidth_ratio( 1, params.ch[1].bw );
                need_trainig = 1;
            }
        }
        /* Assume the Die bit width are the same with the chip bit width */
        params.ch[1].dbw = params.ch[1].bw;

        if (need_trainig && (data_training( 1 ) < 0)) {
            ddr_phy_ctl_reset( 1, 1 );
            udelay( 10 );
            ddr_phy_ctl_reset( 1, 0 );
            udelay( 10 );
            printf( "2nd data training channel1 failed!\r\n");
            return -1;
        } else {
            printf( "data_training channel1 passed !\r\n");
        }
    }

    return 0;
}

int sdram_col_row_detect( int channel )
{
    int row;
    int col;
    int ret;
    unsigned int addr;

    ret = 0;
    /* Detect col */
    for (col = 11; col >= 9; col--) {
        *CONFIG_SYS_SDRAM_BASE = 0x0;
        addr = (1 << (col + params.ch[channel].bw - 1));
        *(volatile unsigned int *)addr = TEST_PATTEN;
        if ( (*(volatile unsigned int *)addr == TEST_PATTEN) && (*CONFIG_SYS_SDRAM_BASE == 0x0) )
            break;
    }
    if ( col == 8 ) {
        printf( "Col detect error\r\n");
        ret = 1;
        goto out;
    } else {
        params.ch[channel].col = col;
    }
   
    move_to_config_state( channel );
    if ( channel == 0 )
        *ddr_msch0_ddrconf = 4;
    else
        *ddr_msch1_ddrconf = 4;
    move_to_access_state( channel );
    /* Detect row*/
    for (row = 16; row >= 12; row--) {
        *CONFIG_SYS_SDRAM_BASE = 0x0;
        addr = (1 << (row + 15 - 1));
        *(volatile unsigned int *)addr = TEST_PATTEN;
        if ( (*(volatile unsigned int *)addr == TEST_PATTEN) && (*CONFIG_SYS_SDRAM_BASE == 0x0) )
            break;
    }
    if (row == 11) {
        printf( "Row detect error\r\n");
        ret = 1;
    } else {
        params.ch[channel].cs1_row = row;
        params.ch[channel].row_3_4 = 0;
        params.ch[channel].cs0_row = row;
    }

out:
    return ret;
}

int sdram_get_niu_config( void )
{
    int i;
    int tmp;
    int size;
    int ret;

    ret = 0;
    tmp = params.ch[0].col - 9;
    tmp -= (params.ch[0].bw == 2) ? 0 : 1;
    tmp |= (params.ch[0].cs0_row - 12) << 4;
    size = sizeof(ddrconf_table)/sizeof(ddrconf_table[0]);
    for (i = 0; i < size; i++)
        if (tmp == ddrconf_table[i])
            break;
    if (i >= size) {
        printf( "niu config not found\r\n");
        ret = -1;
    } else {
        params.base.ddrconfig = i;
    }

    return ret;
}

int sdram_get_stride( void )
{
    int stride;
    int ret;
    unsigned int cap;

    stride = -1;
    ret = 0;
    cap = 1 << (params.ch[0].cs0_row + params.ch[0].col + (params.ch[0].rank - 1) + params.ch[0].bw + 3 - 20);
    if ( params.num_channels == 2 )
        cap = cap << 1;

    switch (cap) {
        case 512:
            stride = 0;
            break;
        case 1024:
            stride = 5;
            break;
        case 2048:
            stride = 9;
            break;
        case 4096:
            stride = 0xd;
            break;
        default:
            stride = -1;
            printf( "could not find correct stride, cap error!\r\n");
            ret = -1;
            break;
    }
    params.base.stride = stride;

    return ret;
}

void dram_cfg_rbc( int channel )
{
    if ( channel == 0 ) {
        if ( params.ch[0].bk == 3 )
            clrsetbits_le32( ddr_publ0_dcr, PDQ_MASK << PDQ_SHIFT, 1 << PDQ_SHIFT );
        else
            clrbits_le32( ddr_publ0_dcr, PDQ_MASK << PDQ_SHIFT );

        *ddr_msch0_ddrconf = params.base.ddrconfig;
    } else {
        if ( params.ch[1].bk == 3 )
            clrsetbits_le32( ddr_publ1_dcr, PDQ_MASK << PDQ_SHIFT, 1 << PDQ_SHIFT );
        else
            clrbits_le32( ddr_publ1_dcr, PDQ_MASK << PDQ_SHIFT );

        *ddr_msch1_ddrconf = params.base.ddrconfig;
    }
}

void dram_all_config( void )
{
    int channel;
    unsigned int sys_reg;

    sys_reg = params.base.dramtype << SYS_REG_DDRTYPE_SHIFT;
    sys_reg |= (params.num_channels - 1) << SYS_REG_NUM_CH_SHIFT;
    for ( channel = 0; channel < params.num_channels; channel++ ) {
        sys_reg |= params.ch[channel].row_3_4 << SYS_REG_ROW_3_4_SHIFT(channel);
        sys_reg |= 1 << SYS_REG_CHINFO_SHIFT(channel);
        sys_reg |= (params.ch[channel].rank - 1) << SYS_REG_RANK_SHIFT(channel);
        sys_reg |= (params.ch[channel].col - 9) << SYS_REG_COL_SHIFT(channel);
        sys_reg |= (params.ch[channel].bk == 3 ? 0 : 1) << SYS_REG_BK_SHIFT(channel);
        sys_reg |= (params.ch[channel].cs0_row - 13) << SYS_REG_CS0_ROW_SHIFT(channel);
        sys_reg |= (params.ch[channel].cs1_row - 13) << SYS_REG_CS1_ROW_SHIFT(channel);
        sys_reg |= (2 >> params.ch[channel].bw) << SYS_REG_BW_SHIFT(channel);
        sys_reg |= (2 >> params.ch[channel].dbw) << SYS_REG_DBW_SHIFT(channel);
        dram_cfg_rbc( channel ); 
    }
    *PMU_SYS_REG2 = sys_reg;
    *SGRF_SOC_CON2 = ( ( 0x1f | params.base.stride ) << 16 ) | params.base.stride;
}

int sdram_init( void )
{   
    int i;
    int ret;
    int channel;
    unsigned int zqcr;

    ret = 0;
    for (channel = 0; channel < 2; channel++) {
        if ( channel == 0 ) {
            *SGRF_SOC_CON2 = ( ( 0x1f | 0x1a ) << 16 ) | 0x1a;
            phy_pctrl_reset( channel );
            phy_dll_bypass_set( channel );
            dfi_cfg( channel );
            pctl_cfg( channel );
            phy_cfg( channel );
            phy_init( channel );
            *ddr_pctl0_powctl = POWER_UP_START;
            while( !(*ddr_pctl0_powstat & POWER_UP_DONE) );
            memory_init( channel );
            move_to_config_state( channel );

            send_command( channel, 3, DESELECT_CMD, 0 );
            udelay( 1 );
            send_command( channel, 3, PREA_CMD, 0 );
            udelay( 1 );
            send_command_op( channel, 3, MRS_CMD, 63, 0xfc );
            udelay( 1 );
            send_command_op( channel, 3, MRS_CMD, 1, 0xc3 );
            udelay( 1 );
            send_command_op( channel, 3, MRS_CMD, 2, 0x6 );
            udelay( 1 );
            send_command_op( channel, 3, MRS_CMD, 3, 0x2 );
            udelay( 1 );

            /* Using 32bit bus width for detect */
            params.ch[0].bw = 2;
            set_bandwidth_ratio( channel, 2 );
            params.ch[0].rank = 2;
            clrsetbits_le32( ddr_publ0_pgcr, 0xF << 18, ( params.ch[0].rank | 1 ) << 18);
            /* DS=40ohm,ODT=155ohm */
            zqcr = 1 << ZDEN_SHIFT | 2 << PU_ONDIE_SHIFT | 2 << PD_ONDIE_SHIFT | 0x19 << PU_OUTPUT_SHIFT | 0x19 << PD_OUTPUT_SHIFT;
            *ddr_publ0_zq1cr0 = zqcr;
            *ddr_publ0_zq0cr0 = zqcr;

            udelay( 10 );
            send_command_op( channel, (params.ch[0].rank | 1), MRS_CMD, 11, 0 );
            *ddr_pctl0_mrrcfg0 = 0x0;
            send_command_op( channel, 1, MRR_CMD, 8, 0 );
            if ( (*ddr_pctl0_mrrstat0 & 0x3) != 0x3 ) { 
                printf( "failed!\r\n");
                return -1;
            }
            /* Detect the rank and bit-width with data-training */
            sdram_rank_bw_detect( channel );

            *ddr_pctl0_mrrcfg0 = 0x0;
            for (i=0; i<17; i++)
                send_command_op( channel, 1, MRR_CMD, i, 0 );
            *ddr_msch0_ddrconf = 15;
            move_to_access_state( channel );
            /* DDR3 and LPDDR3 are always 8 bank, no need detect */
            params.ch[channel].bk = 3;
            /* Detect Col and Row number*/
            ret = sdram_col_row_detect( channel );
            if (ret != 0 )
                goto error;

        } else {
            *SGRF_SOC_CON2 = ( ( 0x1f | 0x17 ) << 16 ) | 0x17;
            phy_pctrl_reset( channel );
            phy_dll_bypass_set( channel );
            dfi_cfg( channel );
            pctl_cfg( channel );
            phy_cfg( channel );
            phy_init( channel );
            *ddr_pctl1_powctl = POWER_UP_START;
            while( !(*ddr_pctl1_powstat & POWER_UP_DONE) );
            memory_init( channel );
            move_to_config_state( channel );

            send_command( channel, 3, DESELECT_CMD, 0 );
            udelay( 1 );
            send_command( channel, 3, PREA_CMD, 0 );
            udelay( 1 );
            send_command_op( channel, 3, MRS_CMD, 63, 0xfc );
            udelay( 1 );
            send_command_op( channel, 3, MRS_CMD, 1, 0xc3 );
            udelay( 1 );
            send_command_op( channel, 3, MRS_CMD, 2, 0x6 );
            udelay( 1 );
            send_command_op( channel, 3, MRS_CMD, 3, 0x2 );
            udelay( 1 );

            /* Using 32bit bus width for detect */
            params.ch[1].bw = 2;
            set_bandwidth_ratio( channel, 2 );
            params.ch[1].rank = 2;
            clrsetbits_le32( ddr_publ1_pgcr, 0xF << 18, ( params.ch[1].rank | 1 ) << 18);
            /* DS=40ohm,ODT=155ohm */
            zqcr = 1 << ZDEN_SHIFT | 2 << PU_ONDIE_SHIFT | 2 << PD_ONDIE_SHIFT | 0x19 << PU_OUTPUT_SHIFT | 0x19 << PD_OUTPUT_SHIFT;
            *ddr_publ1_zq1cr0 = zqcr;
            *ddr_publ1_zq0cr0 = zqcr;

            udelay( 10 );
            send_command_op( channel, (params.ch[1].rank | 1), MRS_CMD, 11, 0 );
            /* Detect the rank and bit-width with data-training */
            sdram_rank_bw_detect( channel );

            *ddr_pctl1_mrrcfg0 = 0x0;
            for (i=0; i<17; i++)
                send_command_op( channel, 1, MRR_CMD, i, 0 );
            *ddr_msch1_ddrconf = 15;
            move_to_access_state( channel );
            /* DDR3 and LPDDR3 are always 8 bank, no need detect */
            params.ch[channel].bk = 3;
            /* Detect Col and Row number*/
            ret = sdram_col_row_detect( channel );
            if (ret != 0 )
                goto error;
        }
    }
    /* Find NIU DDR configuration */
    ret = sdram_get_niu_config();
    if (ret)
        goto error;
    
    ret = sdram_get_stride();
    if (ret)
        goto error;

    dram_all_config();

    return 0;

error:
    printf( "DRAM init failed!\r\n");
    while( 1 );
}

void setup_sdram( void )
{
    params.base.noc_timing = 0x20d266a4;
    params.base.noc_activate = 0x5b6;
    params.base.ddrconfig = 0x2;
    params.base.ddr_freq = 0x1fc4ef40;
    params.base.dramtype = 0x6;
    params.base.stride = 0x9;
    params.base.odt = 0x0;
    params.num_channels = 0x2;
    params.ch[0].bk = 0x0;
    params.ch[1].bk = 0x0;
    params.ch[0].bw = 0x0;
    params.ch[1].bw = 0x0;
    params.ch[0].col = 0x0;
    params.ch[1].col = 0x0;
    params.ch[0].cs0_row = 0x0;
    params.ch[1].cs0_row = 0x0;
    params.ch[0].cs1_row = 0x0;
    params.ch[1].cs1_row = 0x0;
    params.ch[0].dbw = 0x0;
    params.ch[1].dbw = 0x0;
    params.ch[0].rank = 0x0;
    params.ch[1].rank = 0x0;
    params.ch[0].row_3_4 = 0x0;
    params.ch[1].row_3_4 = 0x0;

    sdram_init();
}
