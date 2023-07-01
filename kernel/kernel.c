#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "gdt.h"
#include "interrupts.h"

void kernel_main(void) {

    gdt_init();
    interrupts_init();
    
    print("lkd\n");
}
