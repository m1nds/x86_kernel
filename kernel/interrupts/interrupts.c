#include <stddef.h>
#include <stdint.h>

#include "idt.h"
#include "pic.h"
#include "string.h"

idt_descriptor_entry idt_entries[IDT_ENTRIES];
idt_descriptor idt_desc;

extern void idt_load(void);

extern void* isr_table[];
extern void* irq_table[];

void interrupts_init() {
    memset(&idt_entries, 0, sizeof(idt_descriptor_entry) * 256);

    idt_desc.offset = (uint32_t) &idt_entries;
    idt_desc.limit = sizeof(idt_descriptor_entry) * IDT_ENTRIES - 1;

    for (size_t i = 0; i < 32; i++) {
        idt_setup_entry(&idt_entries[i], (uint32_t) isr_table[i], 0x08, 0x8e);
    }

    pic_remap();

    for (size_t i = 32; i < 48; i++) {
        idt_setup_entry(&idt_entries[i], (uint32_t) irq_table[i-32], 0x08, 0x8e);
    }

    idt_load();
}
