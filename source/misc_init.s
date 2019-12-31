.arm

.global misc_init
misc_init:
    stmfd   sp!, {lr}
    blx     r1
    bl      _Z28exception_handler_initializev
    bl      _Z21socket_log_initializev
    ldmfd   sp!, {pc}
