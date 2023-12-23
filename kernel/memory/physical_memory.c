#include "physical_memory.h"

#include <stddef.h>
#include <stdint.h>

#include "bitmap.h"
#include "multiboot.h"
#include "string.h"
#include "tty.h"

#define FRAME_SIZE 4096

extern uint32_t kernel_start;
extern uint32_t kernel_end;

uint8_t *bitmap;
uint32_t bitmap_size = 0;

uint32_t frames = 0;

void set_memory_map(uint8_t *bm, uint32_t region_address, uint32_t region_size)
{
    uint32_t frame_base = region_address / FRAME_SIZE;
    uint32_t frame_number = region_size / FRAME_SIZE;

    for (uint32_t i = 0; i < frame_number; i++)
        set_bit(bm, frame_base + i);
}

void clear_memory_map(uint8_t *bm, uint32_t region_address,
                      uint32_t region_size)
{
    uint32_t frame_base = region_address / FRAME_SIZE;
    uint32_t frame_number = region_size / FRAME_SIZE;

    for (uint32_t i = 0; i < frame_number; i++)
        clear_bit(bm, frame_base + i);
}

void *allocate_frame()
{
    for (uint32_t i = 1; i < frames; i++)
    {
        if (get_bit(bitmap, i))
        {
            clear_bit(bitmap, i);
            return (void *)(FRAME_SIZE * i);
        }
    }

    print("No page available!\n");
    return NULL;
}

void free_frame(void *address)
{
    uint32_t frame = ((uint32_t)address) / FRAME_SIZE;

    if (get_bit(bitmap, frame) == 0)
    {
        set_bit(bitmap, frame);
        return;
    }

    print("Freing a non used page!\n");
}

void setup_physical_memory_manager(multiboot_info_t *mbd)
{
    bitmap = (uint8_t *)((uint32_t)&kernel_end & 0xFFFFF000) + 0x1000;
    frames = (mbd->mem_lower + mbd->mem_upper) / 4;
    bitmap_size = frames / 8;

    uint32_t kernel_size = (uint32_t *)(bitmap + bitmap_size) - &kernel_start;

    memset(bitmap, 0, bitmap_size);

    for (int i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t))
    {
        multiboot_memory_map_t *mmmt =
            (multiboot_memory_map_t *)(mbd->mmap_addr + i);

        if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE)
            set_memory_map(bitmap, mmmt->addr_low, mmmt->len_low);
    }
    clear_memory_map(bitmap, (uint32_t)&kernel_start, kernel_size);
}
