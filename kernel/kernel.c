#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "timer.h"
#include "gdt.h"
#include "interrupts.h"
#include "physical_memory.h"

#include "multiboot.h"

extern void _init(void);

void kernel_main() {

    _init();

    gdt_init();
    interrupts_init();
    timer_init();
    
    print("lkd\n");

    for (;;);
}

void _main(multiboot_info_t* mbd, unsigned int magic) {
    tty_init();
   
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC || !(mbd->flags >> 6 & 0x1)) {
    	print("Kernel panic!\n");
		for (;;);
    }
 
    tty_init();
    setup_physical_memory_manager(mbd); 
    kernel_main();
}
