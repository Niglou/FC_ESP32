#include <ESP32/registers/specreg.h>

/*
********************* ISR ********************s
*/

#define INTR_STACK_SIZE 72

    .data
intr_lvl2_stack:
    .space      INTR_STACK_SIZE
intr_lvl3_stack:
    .space      INTR_STACK_SIZE
intr_lvl4_stack:
    .space      INTR_STACK_SIZE
intr_lvl5_stack:
    .space      INTR_STACK_SIZE
intr_nmi_stack:
    .space      INTR_STACK_SIZE

.macro intr_save_registers intr_stack
    /* save in stack */
    movi    a0, \intr_stack
    s32i    a2, a0, 0
    s32i    a3, a0, 4
    s32i    a4, a0, 8
    s32i    a5, a0, 12
    s32i    a6, a0, 16
    s32i    a7, a0, 20
    s32i    a8, a0, 24
    s32i    a9, a0, 28
    s32i    a10, a0, 32
    s32i    a11, a0, 36
    s32i    a12, a0, 40
    s32i    a13, a0, 44
    s32i    a14, a0, 48
    s32i    a15, a0, 52
    rsr     a2, LBEG
    s32i    a2, a0,  56
    rsr     a2, LEND
    s32i    a2, a0,  60
    rsr     a2, LCOUNT
    s32i    a2, a0,  64
    rsr     a2, SAR
    s32i    a2, a0,  68
    /* set LCOUNT register to 0 */
    movi    a2, 0
    wsr     a2, LCOUNT
    isync
.endm

.macro intr_restore_registers intr_stack
    /* restore register */
    movi    a0, \intr_stack
    l32i    a2, a0,  56
    wsr     a2, LBEG
    l32i    a2, a0,  60
    wsr     a2, LEND
    l32i    a2, a0,  64
    wsr     a2, LCOUNT
    l32i    a2, a0,  68
    wsr     a2, SAR
    isync

    l32i    a2, a0, 0
    l32i    a3, a0, 4
    l32i    a4, a0, 8
    l32i    a5, a0, 12
    l32i    a6, a0, 16
    l32i    a7, a0, 20
    l32i    a8, a0, 24
    l32i    a9, a0, 28
    l32i    a10, a0, 32
    l32i    a11, a0, 36
    l32i    a12, a0, 40
    l32i    a13, a0, 44
    l32i    a14, a0, 48
    l32i    a15, a0, 52
.endm

    .text
    .global     xt_highint2
    .type       xt_highint2,@function
    .align      4
xt_highint2:
    /* Quit interrupt */
    rsr     a0, EXCSAVE_2
    rfi     2

    .text
    .global     xt_highint3
    .type       xt_highint3,@function
    .align      4
xt_highint3:
    /* Quit interrupt */
    rsr     a0, EXCSAVE_3
    rfi     3

    .text
    .global     xt_highint4
    .type       xt_highint4,@function
    .align      4
xt_highint4:
    /* clear interrupt */

    /* intr xtensa */
    movi    a2, (1<<24)
    wsr.intclear a2
    rsync

    /* intr gpio status */
    movi    a2, 0x3FF44044
    movi    a3, 0
    memw
    s32i    a3, a2, 0
    memw
    /* --------------- */


    /* Quit interrupt */
    rsr     a0, EXCSAVE_4
    rfi     4



    .text
    .global     xt_highint5
    .type       xt_highint5,@function
    .align      4
xt_highint5:
    /* clear interrupt */
    movi    a0, ((1<<16) | (1<<26) | (1<<31))
    wsr.intclear a0
    rsync

    /* save state before interrupt */
    intr_save_registers intr_lvl5_stack

    /* Set PS register */
    movi    a3, 0x40025
    wsr     a3, ps

    /* Call C handler */
    call4   ISR_LVL5

    /* restore state before interrupt */
    intr_restore_registers intr_lvl5_stack

    /* Quit interrupt */
    rsr     a0, EXCSAVE_5
    rfi     5

    .text
    .global     xt_highint6
    .type       xt_highint6,@function
    .align      4
xt_highint6:
    /* Quit interrupt */
    rsr     a0, EXCSAVE_6
    rfi     6


    .text
    .global     xt_nmi
    .type       xt_nmi,@function
    .align      4
xt_nmi:
    /* clear interrupt */
    movi    a0, (1<<14)
    wsr.intclear a0
    rsync

    /* save state before interrupt */
    intr_save_registers intr_nmi_stack

    /* Set PS register */
    movi    a3, 0x40025
    wsr     a3, ps

    /* Call C handler */
    //call4   ISR_NMI

    /* restore state before interrupt */
    intr_restore_registers intr_nmi_stack
    /* Quit interrupt */
    rsr     a0, EXCSAVE_7
    rfi     7
