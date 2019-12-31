.arm

.global BobOmb_decideFirstState_hook
BobOmb_decideFirstState_hook:
    mov     r0, r4
    bl      _ZN6BobOmb22decideFirstStateCustomEv
    ldmfd   sp!, {r4,pc}

.global BobOmb_checkColliderAddTimer_hook
BobOmb_checkColliderAddTimer_hook:
    mov     r5, lr
    mov     r4, r0
    bl      _ZN6BobOmb21checkColliderAddTimerEv
    mov     r0, r4
    bx      r5
