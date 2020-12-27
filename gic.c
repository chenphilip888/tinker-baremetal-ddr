/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "gic.h"

void config_GIC( int N, int CPU_target )
{
    config_interrupt ( N, CPU_target );
    // Set the enable in the CPU Interface Control Register (GICC_CTLR)
    *GICC_CTLR = 0x1;   // 0x1 select IRQ group 0, 0x9 select FIQ group 0
    // Set Interrupt Priority Mask Register (GICC_PMR). Enable all priorities
    *GICC_PMR = 0xFF;
    // Set the enable in the Distributor Control Register (GICD_CTLR)
    *GICD_CTLR = 0x1;
}

/*
* Configure registers in the GIC for an individual Interrupt ID. We
* configure only the Interrupt Set Enable Registers (ICDISERn) and
* Interrupt Processor Target Registers (ICDIPTRn). The default (reset)
* values are used for other registers in the GIC
*/
void config_interrupt ( int N, int CPU_target )
{
    int i;
    int reg_offset, index, index1, value, address;

    // clear all interrupts GICD_ICENABLERn, 1024 total
    for (i=0xffc01180; i<0xffc01200; i=i+4) {
        *(volatile unsigned int *)i = 0xffffffff;
    }
    // all level trigger, GICD_ICFGR, 1024 total. This register is obsoleted
    //for (i=0xffc01c00; i<0xffc01d00; i=i+4) {
    //    *(volatile unsigned int *)i = 0x55555555;
    //}
    // all group 0 GICD_IGROUPRn, 192 total
    for (i=0xffc01080; i<0xffc01098; i=i+4) {
        *(volatile unsigned int *)i = 0x0;
    }
    // all highest priority 0
    for (i=0xffc01400; i<0xffc01800; i=i+4) {
        *(volatile unsigned int *)i = 0x0;
    }
    /* Configure the Interrupt Set-Enable Registers (GICD_ISENABLERn).
    * reg_offset = (integer_div(N / 32) * 4; value = 1 << (N mod 32) */
    reg_offset = (N >> 3) & 0xFFFFFFFC;
    index = N & 0x1F;
    value = 0x1 << index;
    address = GICD_ISENABLERnx + reg_offset;
    /* Using the address and value, set the appropriate bit */
    *(volatile unsigned int *)address |= value;
    /* Configure the Interrupt Processor Targets Register (GICD_ITARGETSRn)
    * reg_offset = integer_div(N / 4) * 4; index = N mod 4 */
    reg_offset = (N & 0xFFFFFFFC);
    index = N & 0x3;
    index1 = index << 3;
    value = CPU_target << index1;
    address = GICD_ITARGETSRnx + reg_offset;
    /* Using the address and value, write to (only) the appropriate byte */
    *(volatile unsigned int *)address |= value;
}
