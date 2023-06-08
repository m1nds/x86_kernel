extern gdt_desc

section .text
global gdt_load
gdt_load:
    lgdt [gdt_desc]
    jmp 0x08:.reload_segments
    
    .reload_segments:
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        ret


