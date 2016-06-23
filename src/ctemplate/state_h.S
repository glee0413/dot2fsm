 .section ".rodata"
 .globl state_func
 .type state_func, STT_OBJECT
state_func:
 .incbin "../src/ctemplate/state_func.ctmp"
 .byte 0
 .size state_func, .-state_func
