 .section ".rodata"
 .globl fsm_c
 .type fsm_c, STT_OBJECT
fsm_c:
 .incbin "../src/ctemplate/fsm_c.ctmp"
 .byte 0
 .size fsm_c, .-fsm_c
