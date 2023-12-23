#ifndef TTY_H
#define TTY_H

#include <stddef.h>
#include <stdint.h>

struct tty_data
{
    size_t x;
    size_t y;

    size_t height;
    size_t width;

    uint8_t color;
    uint16_t *screen;
};

void tty_init();
void putchar(char c);
void print(char *string);
void printf(char *format, ...);

#endif
