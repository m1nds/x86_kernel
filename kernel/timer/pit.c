#include <stdint.h>

#include "io.h"
#include "timer.h"
#include "tty.h"

uint32_t ticks = 0;

void timer_interrupt_handler()
{
    ticks += 1;
}

void timer_init()
{
    uint32_t divisor = 1193180 / 1000;
    outb(PIT_COMMAND, PIT_REPEAT_MODE);

    uint8_t low_divisor_byte = (uint8_t)(divisor & 0xFF);
    uint8_t high_divisor_byte = (uint8_t)((divisor >> 8) & 0xFF);

    outb(PIT_DATA_CH0, low_divisor_byte);
    outb(PIT_DATA_CH0, high_divisor_byte);
}
