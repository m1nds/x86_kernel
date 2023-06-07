#Multiboot2 variables
.set MAGIC, 0xE85250D6
.set MODE, 0
.set LENGTH, header_end - header_start
.set CHECKSUM, 0x100000000 - (MAGIC + MODE + LENGTH)
.set TYPE, 0
.set FLAGS, 0
.set SIZE, 8

# Multiboot2 header
.section .multiboot_header
.align 4
header_start:
    .long MAGIC
    .long MODE
    .long LENGTH
    .long CHECKSUM
    .word TYPE
    .word FLAGS
    .long SIZE
header_end:

# Allocating 4KiB for the Stack
.section .bss
.align 16
stack_bottom:
    .skip 4096
stack_top:

# Entry Point
.section .text
.global _start
.type _start, @function
_start:
        #Setting-up the Stack
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Call the kernel_main function in kernel.c
	call kernel_main


	cli
loop:	hlt
	jmp loop
