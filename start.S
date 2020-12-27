/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

@ vim: filetype=arm
#define USR_MODE 0x10
#define FIQ_MODE 0x11
#define IRQ_MODE 0x12
#define SVC_MODE 0x13
#define ABT_MODE 0x17
#define UND_MODE 0x1B
#define SYS_MODE 0x1F

        .section .stack
        .align  3
#ifdef __STACK_SIZE
        .equ    Stack_Size, __STACK_SIZE
#else
        .equ    Stack_Size, 0xc00
#endif
        .globl  __StackTop
        .globl  __StackLimit
__StackLimit:
        .space  Stack_Size
        .size   __StackLimit, . - __StackLimit
__StackTop:
        .size   __StackTop, . - __StackTop

        .section .heap
        .align  3
#ifdef __HEAP_SIZE
        .equ    Heap_Size, __HEAP_SIZE
#else
        .equ    Heap_Size, 0
#endif
        .globl  __HeapBase
        .globl  __HeapLimit
__HeapBase:
        .if     Heap_Size
        .space  Heap_Size
        .endif
        .size   __HeapBase, . - __HeapBase
__HeapLimit:
        .size   __HeapLimit, . - __HeapLimit

        .section .isr_vector
        .align  2
        .text
        .align  2
        .globl Reset_Handler

Reset_Handler:
	@ Needs to be here as mkimage will overwrite this
	@ with 'RK32'
	nop

Reset_Handler1:
	@ Mask interrupts
	CPSID   if                           

	@ Put any cores other than 0 to sleep
	MRC     p15, 0, R0, c0, c0, 5       // Read MPIDR
	ANDS    R0, R0, #3
.goToSleep:
	WFINE
	BNE     .goToSleep

	@ Reset SCTLR Settings
	MRC     p15, 0, R0, c1, c0, 0       // Read CP15 System Control register
	BIC     R0, R0, #(0x1 << 12)        // Clear I bit 12 to disable I Cache
	BIC     R0, R0, #(0x1 <<  2)        // Clear C bit  2 to disable D Cache
	BIC     R0, R0, #0x1                // Clear M bit  0 to disable MMU
	BIC     R0, R0, #(0x1 << 11)        // Clear Z bit 11 to disable branch prediction
	BIC     R0, R0, #(0x1 << 13)        // Clear V bit 13 to disable hivecs
	MCR     p15, 0, R0, c1, c0, 0       // Write value back to CP15 System Control register
	ISB

	@ Configure ACTLR
	MRC     p15, 0, r0, c1, c0, 1       // Read CP15 Auxiliary Control Register
	ORR     r0, r0, #(1 <<  1)          // Enable L2 prefetch hint (UNK/WI since r4p1)
	MCR     p15, 0, r0, c1, c0, 1       // Write CP15 Auxiliary Control Register

	@ Set Vector Base Address Register (VBAR) to point to this application's vector table
	LDR    R0, =__Vectors
	MCR    p15, 0, R0, c12, c0, 0

#ifdef __STARTUP_COPY_MULTIPLE
        ldr     r4, =__copy_table_start__
        ldr     r5, =__copy_table_end__

.L_loop0:
        cmp     r4, r5
        bge     .L_loop0_done
        ldr     r1, [r4]
        ldr     r2, [r4, #4]
        ldr     r3, [r4, #8]

.L_loop0_0:
        subs    r3, #4
        ittt    ge
        ldrge   r0, [r1, r3]
        strge   r0, [r2, r3]
        bge     .L_loop0_0

        adds    r4, #12
        b       .L_loop0

.L_loop0_done:
#else
        ldr     r1, =__etext
        ldr     r2, =__data_start__
        ldr     r3, =__data_end__

.L_loop1:
        cmp     r2, r3
        ittt    lt
        ldrlt   r0, [r1], #4
        strlt   r0, [r2], #4
        blt     .L_loop1
#endif

#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
        ldr     r3, =__zero_table_start__
        ldr     r4, =__zero_table_end__

.L_loop2:
        cmp     r3, r4
        bge     .L_loop2_done
        ldr     r1, [r3]
        ldr     r2, [r3, #4]
        movs    r0, 0

.L_loop2_0:
        subs    r2, #4
        itt     ge
        strge   r0, [r1, r2]
        bge     .L_loop2_0

        adds    r3, #8
        b       .L_loop2
.L_loop2_done:
#elif defined (__STARTUP_CLEAR_BSS)
        ldr     r1, =__bss_start__
        ldr     r2, =__bss_end__

        movs    r0, 0
.L_loop3:
        cmp     r1, r2
        itt     lt
        strlt   r0, [r1], #4
        blt     .L_loop3
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

	@ Setup Stack for each exceptional mode
        @ Stacks must be 8 byte aligned
	CPS    #FIQ_MODE
	LDR    SP, =__StackTop - 400
	CPS    #IRQ_MODE 
	LDR    SP, =__StackTop - 200
	CPS    #SVC_MODE
	LDR    SP, =__StackTop
	CPS    #ABT_MODE
	LDR    SP, =__StackTop
	CPS    #UND_MODE
	LDR    SP, =__StackTop
	CPS    #SYS_MODE
	LDR    SP, =__StackTop

	@ Unmask interrupts
	CPSIE  if

	bl main

1:	b 1b

	@ Vector table must be 32 byte aligned
	.balign 0x20
__Vectors:
        LDR    PC, =Reset_Handler1
        LDR    PC, =Undef_Handler
        LDR    PC, =SVC_Handler
        LDR    PC, =PAbt_Handler
        LDR    PC, =DAbt_Handler
        NOP
        LDR    PC, =IRQ_Handler
        LDR    PC, =FIQ_Handler

Undef_Handler:
  	b Undef_Handler
SVC_Handler:
  	b SVC_Handler
PAbt_Handler:
  	b PAbt_Handler
DAbt_Handler:
  	b DAbt_Handler
IRQ_Handler:
	PUSH {R0-R7, R12, LR}
	@ Read the GICC_IAR from the CPU Interface
	LDR R4, =0xFFC02000
	LDR R5, [R4, #0x0C]
	@ read from GICC_IAR
UART_IRQ_HANDLER:
	CMP R5, #90
	BNE UNEXPECTED
	BL UART3_ISR
        B  EXIT_IRQ
UNEXPECTED:
        B  EXIT_IRQ
EXIT_IRQ:
	@ Write to the End of Interrupt Register (GICC_EOIR)
	STR R5, [R4, #0x10]
	@ write to GICC_EOIR
	POP {R0-R7, R12, LR}
	SUBS PC, LR, #4

FIQ_Handler:
        PUSH {R0-R7, R12, LR}
        @ Read the GICC_IAR from the CPU Interface
        LDR R4, =0xFFC02000
        LDR R5, [R4, #0x0C]
        @ read from GICC_IAR
UART_FIQ_HANDLER:
        CMP R5, #90
        BNE UNEXPECTED1
        BL UART3_ISR
        B EXIT_FIQ
UNEXPECTED1:
        B EXIT_FIQ
EXIT_FIQ:
        @ Write to the End of Interrupt Register (GICC_EOIR)
        STR R5, [R4, #0x10]
        @ write to GICC_EOIR
        POP {R0-R7, R12, LR}
        SUBS PC, LR, #4

        .globl Get_PC
Get_PC:
	mov r0, pc
	bx  lr

	.end
