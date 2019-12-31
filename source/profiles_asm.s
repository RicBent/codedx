.arm

.global loadNumProfilesR4
loadNumProfilesR4:
    stmfd   sp!, {r0-r3,lr}
    bl      _ZN7Profile14getNumProfilesEv
    mov     r4, r0
    ldmfd   sp!, {r0-r3,pc}


.global loadNumProfilesR6
loadNumProfilesR6:
    stmfd   sp!, {r0-r3,lr}
    bl      _ZN7Profile14getNumProfilesEv
    mov     r6, r0
    ldmfd   sp!, {r0-r3,pc}
