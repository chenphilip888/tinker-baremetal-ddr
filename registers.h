/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#define BUTTON  160
#define LED     161
#define I2C1    252
#define I2C4    233
#define PWM2    238
#define PWM3    239
#define SPI0    166
#define SPI2    257
#define LOW     0
#define HIGH    1
#define INPUT   0
#define OUTPUT  1
#define UART_LSR_THRE   0x20          /* Xmit holding register empty */
#define UART_LSR_DRY    0x1           /* data ready */

#define BOOTROM_BASE            0xffff0000
#define SRAM_BASE               0xff700000

#define irqflagrx               (volatile unsigned int *)0xff703fe0
#define irqdatarx               (volatile unsigned int *)0xff703fe4

/* DMAC PL330 */
#define DMAC_BUS_DSR                (volatile unsigned int *)0xffb20000
#define DMAC_BUS_DPC                (volatile unsigned int *)0xffb20004
#define DMAC_BUS_INTEN              (volatile unsigned int *)0xffb20020
#define DMAC_BUS_INTCLR             (volatile unsigned int *)0xffb2002c
#define DMAC_BUS_FSRD               (volatile unsigned int *)0xffb20030
#define DMAC_BUS_FSRC               (volatile unsigned int *)0xffb20034
#define DMAC_BUS_FTRD               (volatile unsigned int *)0xffb20038
#define DMAC_BUS_FTR0               (volatile unsigned int *)0xffb20040
#define DMAC_BUS_CSR0               (volatile unsigned int *)0xffb20100
#define DMAC_BUS_CPC0               (volatile unsigned int *)0xffb20104
#define DMAC_BUS_SAR0               (volatile unsigned int *)0xffb20400
#define DMAC_BUS_DAR0               (volatile unsigned int *)0xffb20404
#define DMAC_BUS_CCR0               (volatile unsigned int *)0xffb20408
#define DMAC_BUS_LC0_0              (volatile unsigned int *)0xffb2040c
#define DMAC_BUS_DBGST              (volatile unsigned int *)0xffb20d00
#define DMAC_BUS_DBGCMD             (volatile unsigned int *)0xffb20d04
#define DMAC_BUS_DBGINST0           (volatile unsigned int *)0xffb20d08
#define DMAC_BUS_DBGINST1           (volatile unsigned int *)0xffb20d0c
#define DMAC_BUS_CR0                (volatile unsigned int *)0xffb20e00
#define DMAC_BUS_CR1                (volatile unsigned int *)0xffb20e04
#define DMAC_BUS_CR2                (volatile unsigned int *)0xffb20e08
#define DMAC_BUS_CR3                (volatile unsigned int *)0xffb20e0c
#define DMAC_BUS_CR4                (volatile unsigned int *)0xffb20e10
#define DMAC_BUS_CDRn               (volatile unsigned int *)0xffb20e14

#define ddr_msch0_coreid            (volatile unsigned int *)0xffac0000
#define ddr_msch0_revisionid        (volatile unsigned int *)0xffac0004
#define ddr_msch0_ddrconf           (volatile unsigned int *)0xffac0008
#define ddr_msch0_ddrtiming         (volatile unsigned int *)0xffac000c
#define ddr_msch0_ddrmode           (volatile unsigned int *)0xffac0010
#define ddr_msch0_readlatency       (volatile unsigned int *)0xffac0014
#define ddr_msch0_activate          (volatile unsigned int *)0xffac0038
#define ddr_msch0_devtodev          (volatile unsigned int *)0xffac003c
#define ddr_msch1_coreid            (volatile unsigned int *)0xffac0080
#define ddr_msch1_revisionid        (volatile unsigned int *)0xffac0084
#define ddr_msch1_ddrconf           (volatile unsigned int *)0xffac0088
#define ddr_msch1_ddrtiming         (volatile unsigned int *)0xffac008c
#define ddr_msch1_ddrmode           (volatile unsigned int *)0xffac0090
#define ddr_msch1_readlatency       (volatile unsigned int *)0xffac0094
#define ddr_msch1_activate          (volatile unsigned int *)0xffac00b8
#define ddr_msch1_devtodev          (volatile unsigned int *)0xffac00bc

/* DDR DMC Registers */

#define ddr_pctl0_scfg              (volatile unsigned int *)0xff610000
#define ddr_pctl0_sctl              (volatile unsigned int *)0xff610004
#define ddr_pctl0_stat              (volatile unsigned int *)0xff610008
#define ddr_pctl0_mcmd              (volatile unsigned int *)0xff610040
#define ddr_pctl0_powctl            (volatile unsigned int *)0xff610044
#define ddr_pctl0_powstat           (volatile unsigned int *)0xff610048
#define ddr_pctl0_mrrcfg0           (volatile unsigned int *)0xff610060
#define ddr_pctl0_mrrstat0          (volatile unsigned int *)0xff610064
#define ddr_pctl0_mcfg              (volatile unsigned int *)0xff610080
#define ddr_pctl0_ppcfg             (volatile unsigned int *)0xff610084

#define ddr_pctl0_togcnt1u          (volatile unsigned int *)0xff6100c0
#define ddr_pctl0_tinit             (volatile unsigned int *)0xff6100c4
#define ddr_pctl0_trsth             (volatile unsigned int *)0xff6100c8
#define ddr_pctl0_togcnt100n        (volatile unsigned int *)0xff6100cc
#define ddr_pctl0_trefi             (volatile unsigned int *)0xff6100d0
#define ddr_pctl0_tmrd              (volatile unsigned int *)0xff6100d4
#define ddr_pctl0_trfc              (volatile unsigned int *)0xff6100d8
#define ddr_pctl0_trp               (volatile unsigned int *)0xff6100dc
#define ddr_pctl0_trtw              (volatile unsigned int *)0xff6100e0
#define ddr_pctl0_tal               (volatile unsigned int *)0xff6100e4
#define ddr_pctl0_tcl               (volatile unsigned int *)0xff6100e8
#define ddr_pctl0_tcwl              (volatile unsigned int *)0xff6100ec
#define ddr_pctl0_tras              (volatile unsigned int *)0xff6100f0
#define ddr_pctl0_trc               (volatile unsigned int *)0xff6100f4
#define ddr_pctl0_trcd              (volatile unsigned int *)0xff6100f8
#define ddr_pctl0_trrd              (volatile unsigned int *)0xff6100fc
#define ddr_pctl0_trtp              (volatile unsigned int *)0xff610100
#define ddr_pctl0_twr               (volatile unsigned int *)0xff610104
#define ddr_pctl0_twtr              (volatile unsigned int *)0xff610108
#define ddr_pctl0_texsr             (volatile unsigned int *)0xff61010c
#define ddr_pctl0_txp               (volatile unsigned int *)0xff610110
#define ddr_pctl0_txpdll            (volatile unsigned int *)0xff610114
#define ddr_pctl0_tzqcs             (volatile unsigned int *)0xff610118
#define ddr_pctl0_tzqcsi            (volatile unsigned int *)0xff61011c
#define ddr_pctl0_tdqs              (volatile unsigned int *)0xff610120
#define ddr_pctl0_tcksre            (volatile unsigned int *)0xff610124
#define ddr_pctl0_tcksrx            (volatile unsigned int *)0xff610128
#define ddr_pctl0_tcke              (volatile unsigned int *)0xff61012c
#define ddr_pctl0_tmod              (volatile unsigned int *)0xff610130
#define ddr_pctl0_trstl             (volatile unsigned int *)0xff610134
#define ddr_pctl0_tzqcl             (volatile unsigned int *)0xff610138
#define ddr_pctl0_tmrr              (volatile unsigned int *)0xff61013c
#define ddr_pctl0_tckesr            (volatile unsigned int *)0xff610140
#define ddr_pctl0_tdpd              (volatile unsigned int *)0xff610144

#define ddr_pctl0_dfitctrldelay     (volatile unsigned int *)0xff610240
#define ddr_pctl0_dfiodtcfg         (volatile unsigned int *)0xff610244
#define ddr_pctl0_dfiodtcfg1        (volatile unsigned int *)0xff610248
#define ddr_pctl0_dfitphywrdata     (volatile unsigned int *)0xff610250
#define ddr_pctl0_dfitphywrlat      (volatile unsigned int *)0xff610254
#define ddr_pctl0_dfitrddataen      (volatile unsigned int *)0xff610260
#define ddr_pctl0_dfitphyrdlat      (volatile unsigned int *)0xff610264
#define ddr_pctl0_dfitphyupdtype0   (volatile unsigned int *)0xff610270
#define ddr_pctl0_dfiupdcfg         (volatile unsigned int *)0xff610290
#define ddr_pctl0_dfistcfg0         (volatile unsigned int *)0xff6102c4
#define ddr_pctl0_dfistcfg1         (volatile unsigned int *)0xff6102c8
#define ddr_pctl0_dfistcfg2         (volatile unsigned int *)0xff6102cc
#define ddr_pctl0_dfitdramclken     (volatile unsigned int *)0xff6102d0
#define ddr_pctl0_dfitdramclkdis    (volatile unsigned int *)0xff6102d4
#define ddr_pctl0_dfilpcfg0         (volatile unsigned int *)0xff6102f0

#define ddr_publ0_pir        (volatile unsigned int *)0xff620004
#define ddr_publ0_pgcr       (volatile unsigned int *)0xff620008
#define ddr_publ0_pgsr       (volatile unsigned int *)0xff62000c
#define ddr_publ0_dllgcr     (volatile unsigned int *)0xff620010
#define ddr_publ0_acdllcr    (volatile unsigned int *)0xff620014
#define ddr_publ0_ptr0       (volatile unsigned int *)0xff620018
#define ddr_publ0_ptr1       (volatile unsigned int *)0xff62001c
#define ddr_publ0_ptr2       (volatile unsigned int *)0xff620020
#define ddr_publ0_dxccr      (volatile unsigned int *)0xff620028
#define ddr_publ0_dsgcr      (volatile unsigned int *)0xff62002c
#define ddr_publ0_dcr        (volatile unsigned int *)0xff620030
#define ddr_publ0_dtpr0      (volatile unsigned int *)0xff620034
#define ddr_publ0_dtpr1      (volatile unsigned int *)0xff620038
#define ddr_publ0_dtpr2      (volatile unsigned int *)0xff62003c
#define ddr_publ0_mr0        (volatile unsigned int *)0xff620040
#define ddr_publ0_mr1        (volatile unsigned int *)0xff620044
#define ddr_publ0_mr2        (volatile unsigned int *)0xff620048
#define ddr_publ0_mr3        (volatile unsigned int *)0xff62004c
#define ddr_publ0_zq0cr0     (volatile unsigned int *)0xff620180
#define ddr_publ0_zq1cr0     (volatile unsigned int *)0xff620190
#define ddr_publ0_dx0gcr     (volatile unsigned int *)0xff6201c0
#define ddr_publ0_dx0gsr0    (volatile unsigned int *)0xff6201c4
#define ddr_publ0_dx0dllcr   (volatile unsigned int *)0xff6201cc
#define ddr_publ0_dx1gcr     (volatile unsigned int *)0xff620200
#define ddr_publ0_dx1gsr0    (volatile unsigned int *)0xff620204
#define ddr_publ0_dx1dllcr   (volatile unsigned int *)0xff62020c
#define ddr_publ0_dx2gcr     (volatile unsigned int *)0xff620240
#define ddr_publ0_dx2gsr0    (volatile unsigned int *)0xff620244
#define ddr_publ0_dx2dllcr   (volatile unsigned int *)0xff62024c
#define ddr_publ0_dx3gcr     (volatile unsigned int *)0xff620280
#define ddr_publ0_dx3gsr0    (volatile unsigned int *)0xff620284
#define ddr_publ0_dx3dllcr   (volatile unsigned int *)0xff62028c

#define ddr_pctl1_scfg              (volatile unsigned int *)0xff630000
#define ddr_pctl1_sctl              (volatile unsigned int *)0xff630004
#define ddr_pctl1_stat              (volatile unsigned int *)0xff630008
#define ddr_pctl1_mcmd              (volatile unsigned int *)0xff630040
#define ddr_pctl1_powctl            (volatile unsigned int *)0xff630044
#define ddr_pctl1_powstat           (volatile unsigned int *)0xff630048
#define ddr_pctl1_mrrcfg0           (volatile unsigned int *)0xff630060
#define ddr_pctl1_mrrstat0          (volatile unsigned int *)0xff630064
#define ddr_pctl1_mcfg              (volatile unsigned int *)0xff630080
#define ddr_pctl1_ppcfg             (volatile unsigned int *)0xff630084

#define ddr_pctl1_togcnt1u          (volatile unsigned int *)0xff6300c0
#define ddr_pctl1_tinit             (volatile unsigned int *)0xff6300c4
#define ddr_pctl1_trsth             (volatile unsigned int *)0xff6300c8
#define ddr_pctl1_togcnt100n        (volatile unsigned int *)0xff6300cc
#define ddr_pctl1_trefi             (volatile unsigned int *)0xff6300d0
#define ddr_pctl1_tmrd              (volatile unsigned int *)0xff6300d4
#define ddr_pctl1_trfc              (volatile unsigned int *)0xff6300d8
#define ddr_pctl1_trp               (volatile unsigned int *)0xff6300dc
#define ddr_pctl1_trtw              (volatile unsigned int *)0xff6300e0
#define ddr_pctl1_tal               (volatile unsigned int *)0xff6300e4
#define ddr_pctl1_tcl               (volatile unsigned int *)0xff6300e8
#define ddr_pctl1_tcwl              (volatile unsigned int *)0xff6300ec
#define ddr_pctl1_tras              (volatile unsigned int *)0xff6300f0
#define ddr_pctl1_trc               (volatile unsigned int *)0xff6300f4
#define ddr_pctl1_trcd              (volatile unsigned int *)0xff6300f8
#define ddr_pctl1_trrd              (volatile unsigned int *)0xff6300fc
#define ddr_pctl1_trtp              (volatile unsigned int *)0xff630100
#define ddr_pctl1_twr               (volatile unsigned int *)0xff630104
#define ddr_pctl1_twtr              (volatile unsigned int *)0xff630108
#define ddr_pctl1_texsr             (volatile unsigned int *)0xff63010c
#define ddr_pctl1_txp               (volatile unsigned int *)0xff630110
#define ddr_pctl1_txpdll            (volatile unsigned int *)0xff630114
#define ddr_pctl1_tzqcs             (volatile unsigned int *)0xff630118
#define ddr_pctl1_tzqcsi            (volatile unsigned int *)0xff63011c
#define ddr_pctl1_tdqs              (volatile unsigned int *)0xff630120
#define ddr_pctl1_tcksre            (volatile unsigned int *)0xff630124
#define ddr_pctl1_tcksrx            (volatile unsigned int *)0xff630128
#define ddr_pctl1_tcke              (volatile unsigned int *)0xff63012c
#define ddr_pctl1_tmod              (volatile unsigned int *)0xff630130
#define ddr_pctl1_trstl             (volatile unsigned int *)0xff630134
#define ddr_pctl1_tzqcl             (volatile unsigned int *)0xff630138
#define ddr_pctl1_tmrr              (volatile unsigned int *)0xff63013c
#define ddr_pctl1_tckesr            (volatile unsigned int *)0xff630140
#define ddr_pctl1_tdpd              (volatile unsigned int *)0xff630144

#define ddr_pctl1_dfitctrldelay     (volatile unsigned int *)0xff630240
#define ddr_pctl1_dfiodtcfg         (volatile unsigned int *)0xff630244
#define ddr_pctl1_dfiodtcfg1        (volatile unsigned int *)0xff630248
#define ddr_pctl1_dfitphywrdata     (volatile unsigned int *)0xff630250
#define ddr_pctl1_dfitphywrlat      (volatile unsigned int *)0xff630254
#define ddr_pctl1_dfitrddataen      (volatile unsigned int *)0xff630260
#define ddr_pctl1_dfitphyrdlat      (volatile unsigned int *)0xff630264
#define ddr_pctl1_dfitphyupdtype0   (volatile unsigned int *)0xff630270
#define ddr_pctl1_dfiupdcfg         (volatile unsigned int *)0xff630290
#define ddr_pctl1_dfistcfg0         (volatile unsigned int *)0xff6302c4
#define ddr_pctl1_dfistcfg1         (volatile unsigned int *)0xff6302c8
#define ddr_pctl1_dfistcfg2         (volatile unsigned int *)0xff6302cc
#define ddr_pctl1_dfitdramclken     (volatile unsigned int *)0xff6302d0
#define ddr_pctl1_dfitdramclkdis    (volatile unsigned int *)0xff6302d4
#define ddr_pctl1_dfilpcfg0         (volatile unsigned int *)0xff6302f0

#define ddr_publ1_pir        (volatile unsigned int *)0xff640004
#define ddr_publ1_pgcr       (volatile unsigned int *)0xff640008
#define ddr_publ1_pgsr       (volatile unsigned int *)0xff64000c
#define ddr_publ1_dllgcr     (volatile unsigned int *)0xff640010
#define ddr_publ1_acdllcr    (volatile unsigned int *)0xff640014
#define ddr_publ1_ptr0       (volatile unsigned int *)0xff640018
#define ddr_publ1_ptr1       (volatile unsigned int *)0xff64001c
#define ddr_publ1_ptr2       (volatile unsigned int *)0xff640020
#define ddr_publ1_dxccr      (volatile unsigned int *)0xff640028
#define ddr_publ1_dsgcr      (volatile unsigned int *)0xff64002c
#define ddr_publ1_dcr        (volatile unsigned int *)0xff640030
#define ddr_publ1_dtpr0      (volatile unsigned int *)0xff640034
#define ddr_publ1_dtpr1      (volatile unsigned int *)0xff640038
#define ddr_publ1_dtpr2      (volatile unsigned int *)0xff64003c
#define ddr_publ1_mr0        (volatile unsigned int *)0xff640040
#define ddr_publ1_mr1        (volatile unsigned int *)0xff640044
#define ddr_publ1_mr2        (volatile unsigned int *)0xff640048
#define ddr_publ1_mr3        (volatile unsigned int *)0xff64004c
#define ddr_publ1_zq0cr0     (volatile unsigned int *)0xff640180
#define ddr_publ1_zq1cr0     (volatile unsigned int *)0xff640190
#define ddr_publ1_dx0gcr     (volatile unsigned int *)0xff6401c0
#define ddr_publ1_dx0gsr0    (volatile unsigned int *)0xff6401c4
#define ddr_publ1_dx0dllcr   (volatile unsigned int *)0xff6401cc
#define ddr_publ1_dx1gcr     (volatile unsigned int *)0xff640200
#define ddr_publ1_dx1gsr0    (volatile unsigned int *)0xff640204
#define ddr_publ1_dx1dllcr   (volatile unsigned int *)0xff64020c
#define ddr_publ1_dx2gcr     (volatile unsigned int *)0xff640240
#define ddr_publ1_dx2gsr0    (volatile unsigned int *)0xff640244
#define ddr_publ1_dx2dllcr   (volatile unsigned int *)0xff64024c
#define ddr_publ1_dx3gcr     (volatile unsigned int *)0xff640280
#define ddr_publ1_dx3gsr0    (volatile unsigned int *)0xff640284
#define ddr_publ1_dx3dllcr   (volatile unsigned int *)0xff64028c

/* Distributor Registers */
#define GICD_CTLR               (volatile unsigned int *)0xffc01000
#define GICD_TYPER              (volatile unsigned int *)0xffc01004
#define GICD_IIDR               (volatile unsigned int *)0xffc01008
#define GICD_IGROUPRn           (volatile unsigned int *)0xffc01080
#define GICD_IGROUPRnx                                   0xffc01080
#define GICD_ISENABLERn         (volatile unsigned int *)0xffc01100
#define GICD_ISENABLERnx                                 0xffc01100
#define GICD_ICENABLERn         (volatile unsigned int *)0xffc01180
#define GICD_ISPENDRn           (volatile unsigned int *)0xffc01200
#define GICD_ICPENDRn           (volatile unsigned int *)0xffc01280
#define GICD_ICACTIVERn         (volatile unsigned int *)0xffc01380
#define GICD_IPRIORITYRn        (volatile unsigned int *)0xffc01400
#define GICD_ITARGETSRn         (volatile unsigned int *)0xffc01800
#define GICD_ITARGETSRnx                                 0xffc01800
#define GICD_ICFGR              (volatile unsigned int *)0xffc01c00
#define GICD_SGIR               (volatile unsigned int *)0xffc01f00

/* Cpu Interface Memory Mapped Registers */
#define GICC_CTLR               (volatile unsigned int *)0xffc02000
#define GICC_PMR                (volatile unsigned int *)0xffc02004
#define GICC_BPR                (volatile unsigned int *)0xffc02008
#define GICC_IAR                (volatile unsigned int *)0xffc0200C
#define GICC_EOIR               (volatile unsigned int *)0xffc02010
#define GICC_RPR                (volatile unsigned int *)0xffc02014
#define GICC_HPPIR              (volatile unsigned int *)0xffc02018
#define GICC_ABPR               (volatile unsigned int *)0xffc0201c
#define GICC_IIDR               (volatile unsigned int *)0xffc020fc

#define DWMCI_CTRL              (volatile unsigned int *)0xff0c0000
#define DWMCI_PWREN             (volatile unsigned int *)0xff0c0004
#define DWMCI_CLKDIV            (volatile unsigned int *)0xff0c0008
#define DWMCI_CLKSRC            (volatile unsigned int *)0xff0c000C
#define DWMCI_CLKENA            (volatile unsigned int *)0xff0c0010
#define DWMCI_TMOUT             (volatile unsigned int *)0xff0c0014
#define DWMCI_CTYPE             (volatile unsigned int *)0xff0c0018
#define DWMCI_BLKSIZ            (volatile unsigned int *)0xff0c001C
#define DWMCI_BYTCNT            (volatile unsigned int *)0xff0c0020
#define DWMCI_INTMASK           (volatile unsigned int *)0xff0c0024
#define DWMCI_CMDARG            (volatile unsigned int *)0xff0c0028
#define DWMCI_CMD               (volatile unsigned int *)0xff0c002C
#define DWMCI_RESP0             (volatile unsigned int *)0xff0c0030
#define DWMCI_RESP1             (volatile unsigned int *)0xff0c0034
#define DWMCI_RESP2             (volatile unsigned int *)0xff0c0038
#define DWMCI_RESP3             (volatile unsigned int *)0xff0c003C
#define DWMCI_MINTSTS           (volatile unsigned int *)0xff0c0040
#define DWMCI_RINTSTS           (volatile unsigned int *)0xff0c0044
#define DWMCI_STATUS            (volatile unsigned int *)0xff0c0048
#define DWMCI_FIFOTH            (volatile unsigned int *)0xff0c004C
#define DWMCI_CDETECT           (volatile unsigned int *)0xff0c0050
#define DWMCI_WRTPRT            (volatile unsigned int *)0xff0c0054
#define DWMCI_GPIO              (volatile unsigned int *)0xff0c0058
#define DWMCI_TCMCNT            (volatile unsigned int *)0xff0c005C
#define DWMCI_TBBCNT            (volatile unsigned int *)0xff0c0060
#define DWMCI_DEBNCE            (volatile unsigned int *)0xff0c0064
#define DWMCI_USRID             (volatile unsigned int *)0xff0c0068
#define DWMCI_VERID             (volatile unsigned int *)0xff0c006C
#define DWMCI_HCON              (volatile unsigned int *)0xff0c0070
#define DWMCI_UHS_REG           (volatile unsigned int *)0xff0c0074
#define DWMCI_BMOD              (volatile unsigned int *)0xff0c0080
#define DWMCI_PLDMND            (volatile unsigned int *)0xff0c0084
#define DWMCI_DBADDR            (volatile unsigned int *)0xff0c0088
#define DWMCI_IDSTS             (volatile unsigned int *)0xff0c008C
#define DWMCI_IDINTEN           (volatile unsigned int *)0xff0c0090
#define DWMCI_DSCADDR           (volatile unsigned int *)0xff0c0094
#define DWMCI_BUFADDR           (volatile unsigned int *)0xff0c0098
#define DWMCI_DATA              (volatile unsigned int *)0xff0c0200

#define SPI0_CTRLR0    (volatile unsigned int *)0xff110000
#define SPI0_CTRLR1    (volatile unsigned int *)0xff110004
#define SPI0_ENR       (volatile unsigned int *)0xff110008
#define SPI0_SER       (volatile unsigned int *)0xff11000c
#define SPI0_BAUDR     (volatile unsigned int *)0xff110010
#define SPI0_TXFTLR    (volatile unsigned int *)0xff110014
#define SPI0_RXFTLR    (volatile unsigned int *)0xff110018
#define SPI0_TXFLR     (volatile unsigned int *)0xff11001c
#define SPI0_RXFLR     (volatile unsigned int *)0xff110020
#define SPI0_SR        (volatile unsigned int *)0xff110024
#define SPI0_IPR       (volatile unsigned int *)0xff110028
#define SPI0_IMR       (volatile unsigned int *)0xff11002c
#define SPI0_ISR       (volatile unsigned int *)0xff110030
#define SPI0_RISR      (volatile unsigned int *)0xff110034
#define SPI0_ICR       (volatile unsigned int *)0xff110038
#define SPI0_DMACR     (volatile unsigned int *)0xff11003c
#define SPI0_DMATDLR   (volatile unsigned int *)0xff110040
#define SPI0_DMARDLR   (volatile unsigned int *)0xff110044
#define SPI0_TXDR_BASE (volatile unsigned int *)0xff110400
#define SPI0_RXDR_BASE (volatile unsigned int *)0xff110800
#define SPI2_CTRLR0    (volatile unsigned int *)0xff130000
#define SPI2_CTRLR1    (volatile unsigned int *)0xff130004
#define SPI2_ENR       (volatile unsigned int *)0xff130008
#define SPI2_SER       (volatile unsigned int *)0xff13000c
#define SPI2_BAUDR     (volatile unsigned int *)0xff130010
#define SPI2_TXFTLR    (volatile unsigned int *)0xff130014
#define SPI2_RXFTLR    (volatile unsigned int *)0xff130018
#define SPI2_TXFLR     (volatile unsigned int *)0xff13001c
#define SPI2_RXFLR     (volatile unsigned int *)0xff130020
#define SPI2_SR        (volatile unsigned int *)0xff130024
#define SPI2_IPR       (volatile unsigned int *)0xff130028
#define SPI2_IMR       (volatile unsigned int *)0xff13002c
#define SPI2_ISR       (volatile unsigned int *)0xff130030
#define SPI2_RISR      (volatile unsigned int *)0xff130034
#define SPI2_ICR       (volatile unsigned int *)0xff130038
#define SPI2_DMACR     (volatile unsigned int *)0xff13003c
#define SPI2_DMATDLR   (volatile unsigned int *)0xff130040
#define SPI2_DMARDLR   (volatile unsigned int *)0xff130044
#define SPI2_TXDR_BASE (volatile unsigned int *)0xff130400
#define SPI2_RXDR_BASE (volatile unsigned int *)0xff130800

#define I2C1_CON       (volatile unsigned int *)0xff140000
#define I2C1_CLKDIV    (volatile unsigned int *)0xff140004
#define I2C1_MRXADDR   (volatile unsigned int *)0xff140008
#define I2C1_MRXRADDR  (volatile unsigned int *)0xff14000c
#define I2C1_MTXCNT    (volatile unsigned int *)0xff140010
#define I2C1_MRXCNT    (volatile unsigned int *)0xff140014
#define I2C1_IEN       (volatile unsigned int *)0xff140018
#define I2C1_IPD       (volatile unsigned int *)0xff14001c
#define I2C1_FCNT      (volatile unsigned int *)0xff140020
#define I2C1_TXDATA    (volatile unsigned int *)0xff140100
#define I2C1_RXDATA    (volatile unsigned int *)0xff140200
#define I2C1_TXDATA_BASE (volatile unsigned int *)0xff140100
#define I2C1_RXDATA_BASE (volatile unsigned int *)0xff140200
#define I2C4_CON       (volatile unsigned int *)0xff160000
#define I2C4_CLKDIV    (volatile unsigned int *)0xff160004
#define I2C4_MRXADDR   (volatile unsigned int *)0xff160008
#define I2C4_MRXRADDR  (volatile unsigned int *)0xff16000c
#define I2C4_MTXCNT    (volatile unsigned int *)0xff160010
#define I2C4_MRXCNT    (volatile unsigned int *)0xff160014
#define I2C4_IEN       (volatile unsigned int *)0xff160018
#define I2C4_IPD       (volatile unsigned int *)0xff16001c
#define I2C4_FCNT      (volatile unsigned int *)0xff160020
#define I2C4_TXDATA    (volatile unsigned int *)0xff160100
#define I2C4_RXDATA    (volatile unsigned int *)0xff160200
#define I2C4_TXDATA_BASE (volatile unsigned int *)0xff160100
#define I2C4_RXDATA_BASE (volatile unsigned int *)0xff160200

#define UART1_THR (volatile unsigned int *)0xff190000
#define UART1_DR  (volatile unsigned int *)0xff190000
#define UART1_DLL (volatile unsigned int *)0xff190000
#define UART1_DLM (volatile unsigned int *)0xff190004
#define UART1_IER (volatile unsigned int *)0xff190004
#define UART1_FCR (volatile unsigned int *)0xff190008
#define UART1_IIR (volatile unsigned int *)0xff190008
#define UART1_LCR (volatile unsigned int *)0xff19000c
#define UART1_MCR (volatile unsigned int *)0xff190010
#define UART1_LSR (volatile unsigned int *)0xff190014
#define UART1_MSR (volatile unsigned int *)0xff190018
#define UART3_THR (volatile unsigned int *)0xff1b0000
#define UART3_DR  (volatile unsigned int *)0xff1b0000
#define UART3_DLL (volatile unsigned int *)0xff1b0000
#define UART3_DLM (volatile unsigned int *)0xff1b0004
#define UART3_IER (volatile unsigned int *)0xff1b0004
#define UART3_FCR (volatile unsigned int *)0xff1b0008
#define UART3_IIR (volatile unsigned int *)0xff1b0008
#define UART3_LCR (volatile unsigned int *)0xff1b000c
#define UART3_MCR (volatile unsigned int *)0xff1b0010
#define UART3_LSR (volatile unsigned int *)0xff1b0014
#define UART3_MSR (volatile unsigned int *)0xff1b0018
#define UART4_THR (volatile unsigned int *)0xff1c0000
#define UART4_DR  (volatile unsigned int *)0xff1c0000
#define UART4_DLL (volatile unsigned int *)0xff1c0000
#define UART4_DLM (volatile unsigned int *)0xff1c0004
#define UART4_IER (volatile unsigned int *)0xff1c0004
#define UART4_FCR (volatile unsigned int *)0xff1c0008
#define UART4_IIR (volatile unsigned int *)0xff1c0008
#define UART4_LCR (volatile unsigned int *)0xff1c000c
#define UART4_MCR (volatile unsigned int *)0xff1c0010
#define UART4_LSR (volatile unsigned int *)0xff1c0014
#define UART4_MSR (volatile unsigned int *)0xff1c0018

#define TIMER_LOAD_COUNT0 (volatile unsigned int *)0xff810020
#define TIMER_LOAD_COUNT1 (volatile unsigned int *)0xff810024
#define TIMER_CURR_VALUE0 (volatile unsigned int *)0xff810028
#define TIMER_CURR_VALUE1 (volatile unsigned int *)0xff81002c
#define TIMER_CTRL_REG    (volatile unsigned int *)0xff810030
#define TIMER_INT_STATUS  (volatile unsigned int *)0xff810034

#define PLL0_CON0         (volatile unsigned int *)0xff760000
#define PLL0_CON1         (volatile unsigned int *)0xff760004
#define PLL0_CON2         (volatile unsigned int *)0xff760008
#define PLL0_CON3         (volatile unsigned int *)0xff76000c
#define PLL1_CON0         (volatile unsigned int *)0xff760010
#define PLL1_CON1         (volatile unsigned int *)0xff760014
#define PLL1_CON2         (volatile unsigned int *)0xff760018
#define PLL1_CON3         (volatile unsigned int *)0xff76001c
#define PLL2_CON0         (volatile unsigned int *)0xff760020
#define PLL2_CON1         (volatile unsigned int *)0xff760024
#define PLL2_CON2         (volatile unsigned int *)0xff760028
#define PLL2_CON3         (volatile unsigned int *)0xff76002c
#define PLL3_CON0         (volatile unsigned int *)0xff760030
#define PLL3_CON1         (volatile unsigned int *)0xff760034
#define PLL3_CON2         (volatile unsigned int *)0xff760038
#define PLL3_CON3         (volatile unsigned int *)0xff76003c
#define PLL4_CON0         (volatile unsigned int *)0xff760040
#define PLL4_CON1         (volatile unsigned int *)0xff760044
#define PLL4_CON2         (volatile unsigned int *)0xff760048
#define PLL4_CON3         (volatile unsigned int *)0xff76004c

#define CRU_MODE_CON      (volatile unsigned int *)0xff760050
#define CRU_CLKSEL_CON0   (volatile unsigned int *)0xff760060
#define CRU_CLKSEL_CON1   (volatile unsigned int *)0xff760064
#define CRU_CLKSEL_CON10  (volatile unsigned int *)0xff760088
#define CRU_CLKSEL_CON11  (volatile unsigned int *)0xff76008c
#define CRU_CLKSEL_CON25  (volatile unsigned int *)0xff7600c4
#define CRU_CLKSEL_CON26  (volatile unsigned int *)0xff7600c8
#define CRU_CLKSEL_CON37  (volatile unsigned int *)0xff7600f4
#define CRU_CLKSEL_CON39  (volatile unsigned int *)0xff7600fc
#define CRU_CLKGATE14_CON (volatile unsigned int *)0xff760198
#define CRU_CLKGATE17_CON (volatile unsigned int *)0xff7601a4
#define CRU_SOFTRST_CON10 (volatile unsigned int *)0xff7601e0
#define GRF_SOC_CON0      (volatile unsigned int *)0xff770244
#define GRF_SOC_CON2      (volatile unsigned int *)0xff77024c
#define GRF_SOC_STATUS1   (volatile unsigned int *)0xff770284
#define SGRF_SOC_CON2     (volatile unsigned int *)0xff740008
#define PMU_SYS_REG2      (volatile unsigned int *)0xFF73009c
#define GPIO1_SWPORTA_DR       (volatile unsigned int *)0xff780000
#define GPIO1_SWPORTA_DDR      (volatile unsigned int *)0xff780004
#define GPIO5_SWPORTA_DR       (volatile unsigned int *)0xff7c0000
#define GPIO5_SWPORTA_DDR      (volatile unsigned int *)0xff7c0004
#define GPIO5_EXT_PORTA_OFFSET (volatile unsigned int *)0xff7c0050
#define GPIO5B                 (volatile unsigned int *)0xFF770050
#define GPIO5C                 (volatile unsigned int *)0xFF770054
#define GPIO6A                 (volatile unsigned int *)0xFF77005C
#define GPIO7A                 (volatile unsigned int *)0xFF77006C
#define GPIO7B                 (volatile unsigned int *)0xFF770070
#define GPIO7CL                (volatile unsigned int *)0xFF770074
#define GPIO7CH                (volatile unsigned int *)0xFF770078
#define GPIO8A                 (volatile unsigned int *)0xFF770080
#define GPIO8B                 (volatile unsigned int *)0xFF770084

#define PWM2_CTRL              (volatile unsigned int *)0xFF68002c
#define PWM2_DUTY              (volatile unsigned int *)0xFF680028
#define PWM2_PERIOD            (volatile unsigned int *)0xFF680024
#define PWM3_CTRL              (volatile unsigned int *)0xFF68003c
#define PWM3_DUTY              (volatile unsigned int *)0xFF680038
#define PWM3_PERIOD            (volatile unsigned int *)0xFF680034

#define GPIO7C7_SHIFT            12
#define GPIO7C6_SHIFT            8
#define GPIO7C7_MASK             7
#define GPIO7C7_PWM_3            3

void printf(const char *fmt, ...);

#endif
