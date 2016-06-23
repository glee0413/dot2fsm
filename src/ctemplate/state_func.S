 .section ".rodata"
 .globl state_h
 .type state_h, STT_OBJECT
state_h:
 .incbin "../src/ctemplate/state_h.ctmp"
 .byte 0
 .size state_h, .-state_h
