/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _DDR_RK3288_H
#define _DDR_RK3288_H

#include "registers.h"

#define clrbits_le32(addr, clear) (*addr = *addr & ~(clear))
#define setbits_le32(addr, set) (*addr = *addr | (set))
#define clrsetbits_le32(addr, clear, set) (*addr = (*addr & ~(clear)) | (set))
#define LPDDR3                      6
#define TEST_PATTEN                 0x5aa5f00f
#define DQS_GATE_TRAINING_ERROR_RANK0   (1 << 4)
#define DQS_GATE_TRAINING_ERROR_RANK1   (2 << 4)
#define CONFIG_SYS_SDRAM_BASE       (volatile unsigned int *)0x0

#define ARRAY_SIZE(x)               (sizeof(x) / sizeof((x)[0]))

#define DDR0_16BIT_EN_SHIFT         8
#define DDR1_16BIT_EN_SHIFT         9
#define MSCH0_MAINDDR3_SHIFT        3
#define MSCH1_MAINDDR3_SHIFT        4
#define UPCTL0_BST_DIABLE_SHIFT     9
#define UPCTL1_BST_DIABLE_SHIFT     0xc
#define LPDDR3_EN0_SHIFT            8
#define LPDDR3_EN1_SHIFT            0xb
#define UPCTL0_LPDDR3_ODT_EN_SHIFT  0xa
#define UPCTL1_LPDDR3_ODT_EN_SHIFT  0xd

#define SYS_REG_DDRTYPE_SHIFT           13
#define SYS_REG_DDRTYPE_MASK            7
#define SYS_REG_NUM_CH_SHIFT            12
#define SYS_REG_NUM_CH_MASK             1
#define SYS_REG_ROW_3_4_SHIFT(ch)       (30 + (ch))
#define SYS_REG_ROW_3_4_MASK            1
#define SYS_REG_CHINFO_SHIFT(ch)        (28 + (ch))
#define SYS_REG_RANK_SHIFT(ch)          (11 + (ch) * 16)
#define SYS_REG_RANK_MASK               1
#define SYS_REG_COL_SHIFT(ch)           (9 + (ch) * 16)
#define SYS_REG_COL_MASK                3
#define SYS_REG_BK_SHIFT(ch)            (8 + (ch) * 16)
#define SYS_REG_BK_MASK                 1
#define SYS_REG_CS0_ROW_SHIFT(ch)       (6 + (ch) * 16)
#define SYS_REG_CS0_ROW_MASK            3
#define SYS_REG_CS1_ROW_SHIFT(ch)       (4 + (ch) * 16)
#define SYS_REG_CS1_ROW_MASK            3
#define SYS_REG_BW_SHIFT(ch)            (2 + (ch) * 16)
#define SYS_REG_BW_MASK                 3
#define SYS_REG_DBW_SHIFT(ch)           ((ch) * 16)
#define SYS_REG_DBW_MASK                3

struct rk3288_sdram_channel {
        unsigned int rank;
        unsigned int col;
        unsigned int bk;
        unsigned int bw;
        unsigned int dbw;
        unsigned int row_3_4;
        unsigned int cs0_row;
        unsigned int cs1_row;
};

struct rk3288_base_params {
        unsigned int noc_timing;
        unsigned int noc_activate;
        unsigned int ddrconfig;
        unsigned int ddr_freq;
        unsigned int dramtype;
        unsigned int stride;
        unsigned int odt;
};

struct rk3288_sdram_params {
        struct rk3288_sdram_channel ch[2];
        struct rk3288_base_params base;
        int num_channels;
};

#define DDRCONF_ROW_SHIFT               4
#define DDRCONF_COL_SHIFT               0

/* PCT_DFISTCFG0 */
#define DFI_INIT_START			(1 << 0)

/* PCT_DFISTCFG1 */
#define DFI_DRAM_CLK_SR_EN		(1 << 0)
#define DFI_DRAM_CLK_DPD_EN		(1 << 1)

/* PCT_DFISTCFG2 */
#define DFI_PARITY_INTR_EN		(1 << 0)
#define DFI_PARITY_EN			(1 << 1)

/* PCT_DFILPCFG0 */
#define TLP_RESP_TIME_SHIFT		16
#define LP_SR_EN			(1 << 8)
#define LP_PD_EN			(1 << 0)

/* PCT_DFITCTRLDELAY */
#define TCTRL_DELAY_TIME_SHIFT		0

/* PCT_DFITPHYWRDATA */
#define TPHY_WRDATA_TIME_SHIFT		0

/* PCT_DFITPHYRDLAT */
#define TPHY_RDLAT_TIME_SHIFT		0

/* PCT_DFITDRAMCLKDIS */
#define TDRAM_CLK_DIS_TIME_SHIFT	0

/* PCT_DFITDRAMCLKEN */
#define TDRAM_CLK_EN_TIME_SHIFT		0

/* PCTL_DFIODTCFG */
#define RANK0_ODT_WRITE_SEL		(1 << 3)
#define RANK1_ODT_WRITE_SEL		(1 << 11)

/* PCTL_DFIODTCFG1 */
#define ODT_LEN_BL8_W_SHIFT		16

/* PUBL_ACDLLCR */
#define ACDLLCR_DLLDIS			(1 << 31)
#define ACDLLCR_DLLSRST			(1 << 30)

/* PUBL_DXDLLCR */
#define DXDLLCR_DLLDIS			(1 << 31)
#define DXDLLCR_DLLSRST			(1 << 30)

/* PUBL_DLLGCR */
#define DLLGCR_SBIAS			(1 << 30)

/* PUBL_DXGCR */
#define DQSRTT				(1 << 9)
#define DQRTT				(1 << 10)

/* PIR */
#define PIR_INIT			(1 << 0)
#define PIR_DLLSRST			(1 << 1)
#define PIR_DLLLOCK			(1 << 2)
#define PIR_ZCAL			(1 << 3)
#define PIR_ITMSRST			(1 << 4)
#define PIR_DRAMRST			(1 << 5)
#define PIR_DRAMINIT			(1 << 6)
#define PIR_QSTRN			(1 << 7)
#define PIR_RVTRN			(1 << 8)
#define PIR_ICPC			(1 << 16)
#define PIR_DLLBYP			(1 << 17)
#define PIR_CTLDINIT			(1 << 18)
#define PIR_CLRSR			(1 << 28)
#define PIR_LOCKBYP			(1 << 29)
#define PIR_ZCALBYP			(1 << 30)
#define PIR_INITBYP			(1u << 31)

/* PGCR */
#define PGCR_DFTLMT_SHIFT		3
#define PGCR_DFTCMP_SHIFT		2
#define PGCR_DQSCFG_SHIFT		1
#define PGCR_ITMDMD_SHIFT		0

/* PGSR */
#define PGSR_IDONE			(1 << 0)
#define PGSR_DLDONE			(1 << 1)
#define PGSR_ZCDONE			(1 << 2)
#define PGSR_DIDONE			(1 << 3)
#define PGSR_DTDONE			(1 << 4)
#define PGSR_DTERR			(1 << 5)
#define PGSR_DTIERR			(1 << 6)
#define PGSR_DFTERR			(1 << 7)
#define PGSR_RVERR			(1 << 8)
#define PGSR_RVEIRR			(1 << 9)

/* PTR0 */
#define PRT_ITMSRST_SHIFT		18
#define PRT_DLLLOCK_SHIFT		6
#define PRT_DLLSRST_SHIFT		0

/* PTR1 */
#define PRT_DINIT0_SHIFT		0
#define PRT_DINIT1_SHIFT		19

/* PTR2 */
#define PRT_DINIT2_SHIFT		0
#define PRT_DINIT3_SHIFT		17

/* DCR */
#define DDRMD_LPDDR			0
#define DDRMD_DDR			1
#define DDRMD_DDR2			2
#define DDRMD_DDR3			3
#define DDRMD_LPDDR2_LPDDR3		4
#define DDRMD_MASK			7
#define DDRMD_SHIFT			0
#define PDQ_MASK			7
#define PDQ_SHIFT			4

/* DXCCR */
#define DQSNRES_MASK			0xf
#define DQSNRES_SHIFT			8
#define DQSRES_MASK			0xf
#define DQSRES_SHIFT			4

/* DTPR */
#define TDQSCKMAX_SHIFT			27
#define TDQSCKMAX_MASK			7
#define TDQSCK_SHIFT			24
#define TDQSCK_MASK			7

/* DSGCR */
#define DQSGX_SHIFT			5
#define DQSGX_MASK			7
#define DQSGE_SHIFT			8
#define DQSGE_MASK			7

/* SCTL */
#define INIT_STATE			0
#define CFG_STATE			1
#define GO_STATE			2
#define SLEEP_STATE			3
#define WAKEUP_STATE			4

/* STAT */
#define LP_TRIG_SHIFT			4
#define LP_TRIG_MASK			7
#define PCTL_STAT_MSK			7
#define INIT_MEM			0
#define CONFIG				1
#define CONFIG_REQ			2
#define ACCESS				3
#define ACCESS_REQ			4
#define LOW_POWER			5
#define LOW_POWER_ENTRY_REQ		6
#define LOW_POWER_EXIT_REQ		7

/* ZQCR*/
#define PD_OUTPUT_SHIFT			0
#define PU_OUTPUT_SHIFT			5
#define PD_ONDIE_SHIFT			10
#define PU_ONDIE_SHIFT			15
#define ZDEN_SHIFT			28

/* DDLGCR */
#define SBIAS_BYPASS			(1 << 23)

/* MCFG */
#define MDDR_LPDDR2_CLK_STOP_IDLE_SHIFT	24
#define PD_IDLE_SHIFT			8
#define MDDR_EN				(2 << 22)
#define LPDDR2_EN			(3 << 22)
#define DDR2_EN				(0 << 5)
#define DDR3_EN				(1 << 5)
#define LPDDR2_S2			(0 << 6)
#define LPDDR2_S4			(1 << 6)
#define MDDR_LPDDR2_BL_2		(0 << 20)
#define MDDR_LPDDR2_BL_4		(1 << 20)
#define MDDR_LPDDR2_BL_8		(2 << 20)
#define MDDR_LPDDR2_BL_16		(3 << 20)
#define DDR2_DDR3_BL_4			0
#define DDR2_DDR3_BL_8			1
#define TFAW_SHIFT			18
#define PD_EXIT_SLOW			(0 << 17)
#define PD_EXIT_FAST			(1 << 17)
#define PD_TYPE_SHIFT			16
#define BURSTLENGTH_SHIFT		20

/* POWCTL */
#define POWER_UP_START			(1 << 0)

/* POWSTAT */
#define POWER_UP_DONE			(1 << 0)

/* MCMD */
enum {
	DESELECT_CMD			= 0,
	PREA_CMD,
	REF_CMD,
	MRS_CMD,
	ZQCS_CMD,
	ZQCL_CMD,
	RSTL_CMD,
	MRR_CMD				= 8,
	DPDE_CMD,
};

#define LPDDR2_MA_SHIFT			4
#define LPDDR2_MA_MASK			0xff
#define LPDDR2_OP_SHIFT			12
#define LPDDR2_OP_MASK			0xff

#define START_CMD			(1u << 31)

/*
 * DDRCONF
 * [5:4] row(13+n)
 * [1:0] col(9+n), assume bw=2
 */

/* DEVTODEV */
#define BUSWRTORD_SHIFT			4
#define BUSRDTOWR_SHIFT			2
#define BUSRDTORD_SHIFT			0

/* mr1 for ddr3 */
#define DDR3_DLL_DISABLE		1

struct rk3288_sdram_params params;

void setup_sdram( void );
//void ddr_test( void );

#endif
