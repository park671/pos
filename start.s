    .global _start
_start:
    ldr x0, =stack_top
    mov sp, x0
    mov x29, #0
    mov x30, #0

    //init ctrl flags
    mrs x0, SCTLR_EL1
    orr x0, x0, #0x6
    msr SCTLR_EL1, x0

    //enable fp & simd
    mov x0, #0x23330000
    msr CPACR_EL1, x0

    //sync all system register
    isb
    //sync all memory op
    dmb	sy

    //memset(bss, 0, sizeof(bss));
    sub sp, sp, #24
    ldr x0, =bss_start
    ldr x1, =bss_end
fill_loop_start:
    cmp x0, x1
    b.cs fill_loop_finish
    mov x2, #0
    str x2, [x0], #8
    //save ctx
    str x0, [sp, #16]
    str x1, [sp, #8]
    str x2, [sp]
    bl on_bss_fill
    //restore ctx
    ldr x0, [sp, #16]
    ldr x1, [sp, #8]
    ldr x2, [sp]
    b fill_loop_start
fill_loop_finish:
    add sp, sp, #24

    bl main
    b .
