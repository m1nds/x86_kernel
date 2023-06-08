#include <stddef.h>
#include <stdint.h>

#include "../include/gdt.h"

gdt_segment_descriptor descriptors[DESCRIPTORS_COUNT];
gdt_descriptor gdt_desc;

extern void gdt_load(void);

void gdt_setup_descriptor(size_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    descriptors[i].low_limit = limit & 0xFFFF;
    descriptors[i].low_base = base & 0xFFFF;
    descriptors[i].middle_base = (base >> 16) && 0xFF;
    descriptors[i].access_byte = access;
    descriptors[i].flags_and_limit = ((flags & 0xF) << 4) | ((limit >> 16) & 0xF);
    descriptors[i].high_base = (base >> 24);
}

void gdt_init() {
    
    // Null segment descriptor
    gdt_setup_descriptor(0, 0, 0, 0, 0);

    // Kernel code segment descriptor
    gdt_setup_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Kernel data code segment
    gdt_setup_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // User code segment descriptor
    gdt_setup_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // User data segment descriptor
    gdt_setup_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_desc.offset = (uint32_t) &descriptors;
    gdt_desc.limit = sizeof(gdt_segment_descriptor) * DESCRIPTORS_COUNT - 1;

    gdt_load();
}
