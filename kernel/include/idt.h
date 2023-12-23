#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

struct idt_descriptor
{
    uint16_t limit;
    uint32_t offset;
} __attribute__((packed));

struct idt_descriptor_entry
{
    uint16_t low_offset;
    uint16_t selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed));

typedef struct idt_descriptor idt_descriptor;
typedef struct idt_descriptor_entry idt_descriptor_entry;

void idt_setup_entry(idt_descriptor_entry *entry, uint32_t offset,
                     uint16_t selector, uint8_t flags);

#endif
