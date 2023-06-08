#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define DESCRIPTORS_COUNT 5

struct gdt_descriptor {
    uint16_t limit;
    uint32_t offset;
} __attribute__ ((packed));

struct gdt_segment_descriptor {
    uint16_t low_limit;
    uint16_t low_base;
    uint8_t middle_base;
    uint8_t access_byte;
    uint8_t flags_and_limit;
    uint8_t high_base;
} __attribute__ ((packed));

typedef struct gdt_descriptor gdt_descriptor;
typedef struct gdt_segment_descriptor gdt_segment_descriptor;

void gdt_init();

#endif
