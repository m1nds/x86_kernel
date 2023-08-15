#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

#include "tty.h"

struct tty_data tty;

uint32_t stack[256];
size_t stack_pointer = 0;

char hex[] = "0123456789ABCDEF";

void insert_char(char c, size_t x, size_t y) {
    tty.screen[tty.width*y + x] = (uint16_t) c | (uint16_t) tty.color << 4;
}

void clear_screen() {
    for (size_t y = 0; y < tty.height; y++)
        for (size_t x = 0; x < tty.width; x++)
            insert_char(' ', x, y);
}

void scroll_screen() {
    
    for (size_t y = 1; y < tty.height; y++)
        for (size_t x = 0; x < tty.width; x++)
            tty.screen[tty.width*(y-1) + x] = tty.screen[tty.width*y + x];

    for (size_t x = 0; x < tty.width; x++)
        insert_char(' ', x, tty.height - 1);

    tty.y--;
    tty.x = 0;

}

void putchar(char c) {
    if (++(tty.x) >= tty.width || c == '\n') {
        tty.x = 0;
        tty.y++;

        if (c == '\n')
            return;
    }

    if (tty.y >= tty.height)
        scroll_screen();

    insert_char(c, tty.x, tty.y);
}

void print(char* string) {
    size_t i = 0;
    while(string[i]) {
        putchar(string[i]);
        i++;
    }
}

void print_hex(uint32_t value) {

    uint32_t save = value;
    uint32_t digits = 0;
    
    while (save) {
        stack[stack_pointer++] = save % 16;
        digits++;
        save /= 16;
    }

    for (uint8_t i = 0; i < digits; i++) {
        putchar(hex[stack[--stack_pointer]]);
    }
}

void print_dec(uint32_t value) {
    uint32_t save = value;
    uint32_t digits = 0;

    while (save) {
        stack[stack_pointer++] = save % 10;
        digits++;
        save /= 10;
    }

    for (uint8_t i = 0; i < digits; i++) {
        putchar('0' + stack[--stack_pointer]);
    }
}

void printf(char* format, ...) {
    va_list args;
    va_start(args, format);

    size_t i = 0;
    while (format[i]) {
        if (format[i] == '%') {
            switch (format[i+1]) {
                case '\0':
                    print("Invalid format!\n");
                    va_end(args);
                    return;

                case 'x':
                    print_hex((uint32_t) va_arg(args, uint32_t));
                    i++;
                    break;

                case 'd':
                    print_dec((uint32_t) va_arg(args, uint32_t));
                    i++;
                    break;

                case '%':
                    putchar('%');
                    i++;
            }
        } else {
            putchar(format[i]);
        }
        if (format[i])
            i++;
    }
    va_end(args);    
}

void tty_init() {
    tty.x = 0;
    tty.y = 0;

    tty.height = 25;
    tty.width = 80;

    tty.color = (uint16_t) 0xF0;
    tty.screen = (uint16_t*) 0xB8000;

    clear_screen();
}
