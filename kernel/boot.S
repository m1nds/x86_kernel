.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

# Multiboot1 header
.section .multiboot_header
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

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
