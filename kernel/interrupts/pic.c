#include "pic.h"

#include "io.h"

void pic_remap()
{
    // ICW1
    outb(PIC_MASTER_COMMAND, ICW1);
    outb(PIC_SLAVE_COMMAND, ICW1);

    // ICW2
    outb(PIC_MASTER_DATA, PIC_MASTER_OFFSET);
    outb(PIC_SLAVE_DATA, PIC_SLAVE_OFFSET);

    // ICW3
    outb(PIC_MASTER_DATA, PIC_MASTER_ICW3);
    outb(PIC_SLAVE_DATA, PIC_SLAVE_ICW3);

    // ICW4
    outb(PIC_MASTER_DATA, ICW4);
    outb(PIC_SLAVE_DATA, ICW4);

    outb(PIC_MASTER_DATA, 0x0);
    outb(PIC_SLAVE_DATA, 0x0);
}

void pic_send_eoi(uint32_t irq)
{
    if (irq >= 8)
        outb(PIC_SLAVE_COMMAND, 0x20);

    outb(PIC_MASTER_COMMAND, 0x20);
}
