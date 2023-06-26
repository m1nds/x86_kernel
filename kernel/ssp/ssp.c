#include <stdint.h>
#include "tty.h"
 
#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif
 
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;
 
__attribute__((noreturn)) void __stack_chk_fail(void)
{
    print("Stack Smash detected!\n");
    //TODO: Need to implement kernel panic

}
