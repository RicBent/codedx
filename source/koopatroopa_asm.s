.arm

.global KoopaTroopa_decideFirstState_hook
KoopaTroopa_decideFirstState_hook:
    mov     r4, r0
    stmfd   sp!, {lr}
    bl      _ZN11KoopaTroopa22decideFirstStateCustomEv
    ldmfd   sp!, {lr}
    cmp     r0, #0
    bxeq    lr
    ldmfd   sp!, {r4,pc}
