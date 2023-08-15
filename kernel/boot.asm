; Defining macros for multiboot header
%define FLAGS 3
%define MAGIC 0x1BADB002
%define CHECKSUM - (MAGIC + FLAGS)

; External functions
extern _init
extern _main

; Defining the multiboot header
section .multiboot_header
align 4
header_start:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
header_end:

; Allocating 4 Kib of space for the stack
section .bss
stack_top:
    resb 4096
stack_bottom:


section .text
global _start
_start:
    ; Setting up the stack
    mov esp, stack_bottom

    ; Calling the _main function in kernel.c
    push eax
    push ebx
    call _main
    
    cli
    hlt
    jmp $
