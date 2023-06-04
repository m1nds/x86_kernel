#include <stddef.h>
#include <stdint.h>

#include "include/tty.h"

struct tty_data tty;

void insert_char(char c, size_t x, size_t y) {
    tty.screen[tty.width*y + x] = (uint16_t) c | (uint16_t) tty.color << 4;
}

void clear_screen() {
    for (size_t y = 0; y < tty.height; y++) {
        for (size_t x = 0; x < tty.width; x++) {
            insert_char(' ', x, y);
        }
    }
}

void scroll_screen() {
    
    for (size_t y = 1; y < tty.height; y++) {
        for (size_t x = 0; x < tty.width; x++) {
            tty.screen[tty.width*(y-1) + x] = tty.screen[tty.width*y + x];
        }
    }

    for (size_t x = 0; x < tty.width; x++)
        insert_char(' ', x, tty.height - 1);

    tty.y--;
    tty.x = 0;

}

void putchar(char c) {
    if (++(tty.x) >= tty.width) {
        tty.x = 0;
        tty.y++;
    }

    if (tty.y >= tty.height) {
        scroll_screen();
    }

    insert_char(c, tty.x, tty.y);
}

void print(char* string) {
    size_t i = 0;
    while(string[i]) {
        if (string[i] == '\n') {
            tty.y++;
            tty.x = 0;
        } else {
            putchar(string[i]);
        }

        i++;
    }
}

//Testing the global constructors call in _init
__attribute__ ((constructor)) void tty_init() {
    tty.x = 0;
    tty.y = 0;

    tty.height = 25;
    tty.width = 80;

    tty.color = (uint16_t) 0xF0;
    tty.screen = (uint16_t*) 0xB8000;

    clear_screen();
}
