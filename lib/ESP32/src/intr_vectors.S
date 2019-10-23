#include <ESP32/registers/specreg.h>

    .begin      literal_prefix .Level2InterruptVector
    .section    .Level2InterruptVector.text, "ax"
    .global     _Level2Vector
    .type       _Level2Vector,@function
    .global     xt_highint2
    .align      4
_Level2Vector:
    wsr     a0, EXCSAVE_2
    call0   xt_highint2

    .end        literal_prefix

    .begin      literal_prefix .Level3InterruptVector
    .section    .Level3InterruptVector.text, "ax"
    .global     _Level3Vector
    .type       _Level3Vector,@function
    .global     xt_highint3
    .align      4
_Level3Vector:
    wsr     a0, EXCSAVE_3
    call0   xt_highint3

    .end        literal_prefix

    .begin      literal_prefix .Level4InterruptVector
    .section    .Level4InterruptVector.text, "ax"
    .global     _Level4Vector
    .type       _Level4Vector,@function
    .global     xt_highint4
    .align      4
_Level4Vector:
    wsr     a0, EXCSAVE_4
    call0   xt_highint4

    .end        literal_prefix


    .begin      literal_prefix .LevelI5nterruptVector
    .section    .Level5InterruptVector.text, "ax"
    .global     _Level5Vector
    .type       _Level5Vector,@function
    .global     xt_highint5
    .align      4
_Level5Vector:
    wsr     a0, EXCSAVE_5
    call0   xt_highint5

    .end        literal_prefix


    .begin      literal_prefix .Level6InterruptVector
    .section    .Level6InterruptVector.text, "ax"
    .global     _Level6Vector
    .type       _Level6Vector,@function
    .global     xt_highint6
    .align      4
_Level6Vector:
    wsr     a0, EXCSAVE_6
    call0   xt_highint6

    .end        literal_prefix


    .begin      literal_prefix .NMIExceptionVector
    .section    .NMIExceptionVector.text, "ax"
    .global     _NMIExceptionVector
    .type       _NMIExceptionVector,@function
    .global     xt_nmi
    .align      4
_NMIExceptionVector:
    wsr     a0, EXCSAVE_7
    call0   xt_nmi

    .end        literal_prefix


    .begin      literal_prefix .KernelExceptionVector
    .section    .KernelExceptionVector.text, "ax"
    .global     _KernelExceptionVector
    .align      4
_KernelExceptionVector:
    wsr     a0, EXCSAVE_1
    //call0   _xt_kernel_exc
    //rfe

    .end        literal_prefix


    .begin      literal_prefix .UserExceptionVector
    .section    .UserExceptionVector.text, "ax"
    .global     _UserExceptionVector
    .type       _UserExceptionVector,@function
    .align      4
_UserExceptionVector:
    wsr     a0, EXCSAVE_1
    //call0   _xt_user_exc
    //rfe

    .end        literal_prefix



    .begin      literal_prefix .DoubleExceptionVector
    .section    .DoubleExceptionVector.text, "ax"
    .global     _DoubleExceptionVector
    .align      4
_DoubleExceptionVector:

    #if XCHAL_HAVE_DEBUG
    break   1, 4
    #endif
    /*
    movi    a0,PANIC_RSN_DOUBLEEXCEPTION
    wsr     a0,EXCCAUSE
    call0   _xt_panic
    */
    //rfde

    .end        literal_prefix
