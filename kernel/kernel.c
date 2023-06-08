#include <stddef.h>
#include <stdint.h>

#include "include/tty.h"
#include "include/gdt.h"

void strcpy(char* str1, char* str2) {
    size_t i = 0;
    size_t z = 0;

    while(str1[i])
        i++;

    while(str2[z]) {
        str1[i] = str2[z];
        z++;
        i++;
    }
    
    str1[i] = '\0';

}

void foo(char* str) {
	char buffer[16] = {0}; 
	strcpy(buffer, str);

        print(buffer);
}

void kernel_main(void) {

    gdt_init();

    char test[] = "0123456789ABCDEF";

    foo(test);

    print("Printing line...\n");


}
