 .section ".rodata"
 .globl state_c
 .type state_c, STT_OBJECT
state_c:
 .incbin "../src/ctemplate/state_c.ctmp"
 .byte 0
 .size state_c, .-state_c
