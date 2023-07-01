#ifndef INTERRUPTS_H
#define INTERRUPTS_H

void isr_handler(uint32_t int_number);
void irq_handler(uint32_t int_number);

void interrupts_init();

#endif
