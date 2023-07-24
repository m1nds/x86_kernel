#include <stdint.h>

#include "keyboard.h"
#include "io.h"
#include "tty.h"

char* scancode_to_key[84] = {
    "[ERROR]\n", "[ESC]\n",
    "[1]\n", "[2]\n", "[3]\n", "[4]\n", "[5]\n", "[6]\n", "[7]\n", "[8]\n", "[9]\n", "[0]\n", "[-]\n", "[=]\n", "[BACKSPACE]\n", 
    "[TAB]\n", "[q]\n", "[w]\n", "[e]\n", "[r]\n", "[t]\n", "[y]\n", "[u]\n", "[i]\n", "[o]\n", "[p]\n", "'['\n", "']'\n",
    "[ENTER]\n", 
    "[LEFT_CONTROL]\n",
    "[a]\n", "[s]\n", "[d]\n", "[f]\n", "[g]\n", "[h]\n", "[j]\n", "[k]\n", "[l]\n", "[;]\n", "[']\n", 
    "[`]\n",
    "[LEFT_SHIFT]\n", 
    "[BACKSLASH]\n",
    "[z]\n", "[x]\n", "[c]\n", "[v]\n", "[b]\n", "[n]\n", "[m]\n", "[,]\n", "[.]\n", "[/]\n", "[RIGHT_SHIFT]\n",
    "[KEYPAD-*]\n",
    "[LEFT_ALT]\n", "[SPACE]\n", 
    "[CAPSLOCK]\n",
    "[F1]\n", "[F2]\n", "[F3]\n", "[F4]\n", "[F5]\n", "[F6]\n", "[F7]\n", "[F8]\n", "[F9]\n", "[F10]\n",
    "[NUMLOCK]\n", 
    "[SCROL_LOCK]\n", 
    "[KEYPAD-7]\n", "[KEYPAD-8]\n", "[KEYPAD-9]\n",
    "[KEYPAD--]\n",
    "[KEYPAD-4]\n", "[KEYPAD-5]\n", "[KEYPAD-6]\n", "[KEYPAD-+]\n",
    "[KEYPAD-1]\n", "[KEYPAD-2]\n", "[KEYPAD-3]\n",
    "[KEYPAD-0]\n", "[KEYPAD-DEL]\n",
};		

void keyboard_interrupt_handler() {
    uint8_t scanCode = inb(KEYBOARD_DATA);

    if (scanCode <= 83) {
        print(scancode_to_key[scanCode]);
    }
}
