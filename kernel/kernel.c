#include <stddef.h>
#include <stdint.h>

#include "include/tty.h"
#include "include/gdt.h"
#include "include/idt.h"

void kernel_main(void) {

    gdt_init();
    idt_init();

    print("lkd\n");


}
