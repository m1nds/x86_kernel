#include <stddef.h>
#include <stdint.h>

#include "../include/gdt.h"

gdt_descriptor_entry gdt_entries[GDT_ENTRIES];
gdt_descriptor gdt_desc;

extern void gdt_load(void);

void gdt_setup_entry(size_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt_entries[i].low_limit = limit & 0xFFFF;
    gdt_entries[i].low_base = base & 0xFFFF;
    gdt_entries[i].middle_base = (base >> 16) && 0xFF;
    gdt_entries[i].access_byte = access;
    gdt_entries[i].flags_and_limit = ((flags & 0xF) << 4) | ((limit >> 16) & 0xF);
    gdt_entries[i].high_base = (base >> 24);
}

void gdt_init() {
    
    // Null segment descriptor
    gdt_setup_entry(0, 0, 0, 0, 0);

    // Kernel code segment descriptor
    gdt_setup_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Kernel data code segment
    gdt_setup_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // User code segment descriptor
    gdt_setup_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // User data segment descriptor
    gdt_setup_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_desc.offset = (uint32_t) &gdt_entries;
    gdt_desc.limit = sizeof(gdt_descriptor_entry) * GDT_ENTRIES - 1;

    gdt_load();
}
