#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>

static inline uint8_t get_bit(uint8_t *bitmap, uint32_t frame)
{
    uint32_t bit = frame / 8;
    uint32_t offset = frame % 8;

    return (bitmap[bit] & (1 << offset));
}

static inline void set_bit(uint8_t *bitmap, uint32_t frame)
{
    uint32_t bit = frame / 8;
    uint32_t offset = frame % 8;

    bitmap[bit] |= (1 << offset);
}

static inline void clear_bit(uint8_t *bitmap, uint32_t frame)
{
    uint32_t bit = frame / 8;
    uint32_t offset = frame % 8;

    bitmap[bit] &= ~(1 << offset);
}

#endif
