; Defining macros for multiboot header
%define MAGIC 0xE85250D6
%define MODE 0
%define LENGTH header_end - header_start
%define CHECKSUM 0x100000000 - (MAGIC + MODE + LENGTH)
%define TYPE 0
%define FLAGS 3
%define SIZE 8

; External functions
extern _init
extern kernel_main

; Defining the multiboot header
section .multiboot_header
align 4
header_start:
    dd MAGIC
    dd MODE
    dd LENGTH
    dd CHECKSUM
    dw TYPE
    dw FLAGS
    dd SIZE
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

    ; Calling _init to setup Global Constructors/Destructors
    call _init

    ; Calling the kernel_main function in kernel.c
    call kernel_main
    
    cli
    hlt
    jmp $
