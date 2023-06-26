#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "gdt.h"
#include "idt.h"

void kernel_main(void) {

    gdt_init();
    idt_init();
    
    print("lkd\n");

    int test = 5/0;
}
