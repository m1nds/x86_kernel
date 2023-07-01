#include <stddef.h>
#include <stdint.h>

#include "idt.h"

void idt_setup_entry(idt_descriptor_entry* entry, uint32_t offset, uint16_t selector, uint8_t flags) {
    entry->low_offset = offset & 0xFFFF;
    entry->selector = selector;
    entry->reserved = 0;
    entry->flags = flags;
    entry->high_offset = (offset >> 16) & 0xFFFF;
}
