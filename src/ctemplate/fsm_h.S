 .section ".rodata"
 .globl fsm_h
 .type fsm_h, STT_OBJECT
fsm_h:
 .incbin "../src/ctemplate/fsm_h.ctmp"
 .byte 0
 .size fsm_h, .-fsm_h
