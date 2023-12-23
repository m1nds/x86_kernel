#ifndef PIC_H
#define PIC_H

#include <stdint.h>

// IO Ports for the PICs
#define PIC_MASTER_COMMAND 0x20
#define PIC_SLAVE_COMMAND 0xA0
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_DATA 0xA1

// ICW1 Macro
#define ICW1 0x11

// Offsets for ICW2
#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET 0x28

// ICW3 Macros
#define PIC_MASTER_ICW3 0x04
#define PIC_SLAVE_ICW3 0x02

// ICW4 Macro
#define ICW4 0x1

void pic_remap();
void pic_send_eoi(uint32_t irq);

#endif
