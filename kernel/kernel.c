#include <stddef.h>
#include <stdint.h>

#include "gdt.h"
#include "interrupts.h"
#include "multiboot.h"
#include "physical_memory.h"
#include "timer.h"
#include "tty.h"

extern void _init(void);

void kernel_main()
{
    _init();

    gdt_init();
    interrupts_init();
    timer_init();

    print("lkd\n");

    for (;;);
}

void _main(multiboot_info_t *mbd)
{
    tty_init();
    setup_physical_memory_manager(mbd);
    kernel_main();
}
