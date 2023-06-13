#include <stddef.h>
#include <stdint.h>

#include "../include/idt.h"
#include "../include/string.h"

idt_descriptor_entry idt_entries[IDT_ENTRIES];
idt_descriptor idt_desc;

extern void idt_load(void);

void idt_setup_entry(size_t i, uint32_t offset, uint16_t selector, uint8_t flags) {
    idt_entries[i].low_offset = offset & 0xFFFF;
    idt_entries[i].selector = selector;
    idt_entries[i].reserved = 0;
    idt_entries[i].flags = flags;
    idt_entries[i].high_offset = (offset >> 16) & 0xFFFF;
}

void idt_init() {
    
    memset(&idt_entries, 0, sizeof(idt_descriptor_entry) * 256);

    idt_desc.offset = (uint32_t) &idt_entries;
    idt_desc.limit = sizeof(idt_descriptor_entry) * IDT_ENTRIES - 1;

    idt_load();
}
