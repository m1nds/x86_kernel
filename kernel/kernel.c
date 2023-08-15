#include <stddef.h>
#include <stdint.h>

#include "tty.h"
#include "timer.h"
#include "gdt.h"
#include "interrupts.h"

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

    if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        print("Invalid magic number!\n");
    }
 
    /* Check bit 6 to see if we have a valid memory map */
    if(!(mbd->flags >> 6 & 0x1)) {
        print("Invalid memory map given by GRUB bootloader\n");
    }
 
    /* Loop through the memory map and display the values */
    for (multiboot_uint32_t i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) 
    {
        multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*) (mbd->mmap_addr + i);
         
        printf("Start Addr: 0x%x %x | Length: 0x%x %x | Size: %x | Type: %d\n",
            mmmt->addr_high, mmmt->addr_low, mmmt->len_high, mmmt->len_low, mmmt->size, mmmt->type);
 
        if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
            /* 
             * Do something with this memory block!
             * BE WARNED that some of memory shown as availiable is actually 
             * actively being used by the kernel! You'll need to take that
             * into account before writing to memory!
             */
        }
    }

    kernel_main();
}
