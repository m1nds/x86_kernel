global tss_load
tss_load:
    mov ax, 0x28
    ltr ax
    ret
