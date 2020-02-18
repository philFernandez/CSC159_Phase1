// syscall.c
// OS service calls

// clang-format off
#include "kernel.h"

// returns current system time in seconds
int get_time_call(void) {
   int time;

   asm("int $48;
        movl %%eax, %0"
       : "=g" (time)
       :
       : "eax"
   );

   return time;
}

// display a string to target console
void write_call(char *str) {
   asm("movl %0, %%eax;
        int $49"
       :
       : "g" ((int)str)
       : "eax"
   );
}

// read in a string from target keyboard
void read_call(char *str) {
    asm("movl %%eax, %0;
         int $50"
         :
         : "g" ((int)str)
    );
}
