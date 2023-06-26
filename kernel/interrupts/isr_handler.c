#include "tty.h"

__attribute__ ((noreturn)) void isr_handler() {
    print("ISR handled!\n");
    __asm__ volatile ("cli; hlt");
}
