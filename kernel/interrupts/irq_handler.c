#include <stdint.h>

#include "tty.h"
#include "timer.h"
#include "pic.h"
#include "interrupts.h"

void irq_handler(uint32_t int_number) {
    char test[] = "IRQ: --\n";

    test[5] = '0' +  int_number % 10;
    test[6] = '0' +  int_number % 10;
    
    print(test);

    if (int_number == 0)
        timer_interrupt_handler();

    pic_send_eoi(int_number);
}
