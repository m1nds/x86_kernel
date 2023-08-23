#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <stdint.h>
#include <stddef.h>
#include <multiboot.h>

void setup_physical_memory_manager(multiboot_info_t* mbt);

#endif

