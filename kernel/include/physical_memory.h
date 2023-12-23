#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <multiboot.h>
#include <stddef.h>
#include <stdint.h>

void setup_physical_memory_manager(multiboot_info_t *mbt);

#endif
