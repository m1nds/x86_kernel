CC:=gcc
LD:=ld
CFLAGS:=-I kernel/include -g -std=gnu99 -nostdlib -ffreestanding -Wall -Wextra
AS:=nasm

CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

ASM:=$(shell find . -name "*.asm")
C:=$(shell find . -name "*.c")

OBJ:= $(ASM:.asm=.o) $(C:.c=.o)
LINK:= obj/crti.o $(CRTBEGIN_OBJ) obj/boot.o obj/isr.o obj/irq.o obj/gdt_load.o obj/idt_load.o obj/tss_load.o $(addprefix obj/,$(notdir $(C:.c=.o)))  $(CRTEND_OBJ) obj/crtn.o

.PHONY: clean setup make_iso link_objects

all: make_iso

make_iso: setup link_objects
	cp bin/kernel.bin isodir/boot
	grub-mkrescue -o lkd.iso isodir

link_objects: setup $(OBJ)
	#$(LD) --nmagic --output=bin/kernel.bin --script=linker.ld $(LINK)
	$(CC) -T linker.ld -o bin/kernel.bin $(CFLAGS) $(LINK)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
	mv $@ obj/

%.o: %.asm
	$(AS) -f elf32 $<
	mv $@ obj/

setup:
	mkdir -p obj/ bin/ isodir/boot/grub
	cp grub.cfg isodir/boot/grub

clean:
	rm -rf obj/ bin/ isodir/ lkd.iso
