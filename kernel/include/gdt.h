#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_ENTRIES 6

struct gdt_descriptor {
    uint16_t limit;
    uint32_t offset;
} __attribute__ ((packed));

struct gdt_descriptor_entry {
    uint16_t low_limit;
    uint16_t low_base;
    uint8_t middle_base;
    uint8_t access_byte;
    uint8_t flags_and_limit;
    uint8_t high_base;
} __attribute__ ((packed));

struct tss_entry {
	uint32_t previous_task;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt_selector;
	uint32_t io_map_address;
} __attribute__ ((packed));

typedef struct gdt_descriptor gdt_descriptor;
typedef struct gdt_descriptor_entry gdt_descriptor_entry;
typedef struct tss_entry tss_entry;

void gdt_init();

#endif
