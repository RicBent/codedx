.section ".crt0", "ax"

_crt0_section:
    .word 0
    .word __mod0_start - _crt0_section
    
.global __mod0_start
__mod0_start:
    .ascii "MOD0"
    .word _DYNAMIC             - __mod0_start
    .word __bss_start__        - __mod0_start
    .word __bss_end__          - __mod0_start
    .word __eh_frame_hdr_start - __mod0_start
    .word __eh_frame_hdr_end   - __mod0_start
    .word __bss_start__        - __mod0_start   @ Runtime-generated module object: Linkerscript reserves 0x60 bytes for this at __bss_start__

.global _init
_init:
    bx      lr      @ Return to rltd


@ Assure that custom constructors are called after main ones
.global static_init_hook
static_init_hook:
    bl      static_init
    sub     sp, r11, #8
    ldmfd   sp!, {r4,r5,r11,pc}
