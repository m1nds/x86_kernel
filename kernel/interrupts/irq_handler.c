#include <stdint.h>

#include "tty.h"
#include "timer.h"
#include "pic.h"
#include "interrupts.h"
#include "keyboard.h"

void irq_handler(uint32_t int_number) {
    
    if (int_number == 0)
        timer_interrupt_handler();
    else if (int_number == 1)
        keyboard_interrupt_handler();

    pic_send_eoi(int_number);
}
