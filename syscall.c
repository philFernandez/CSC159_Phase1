// syscall.c
// OS service calls

// clang-format off
#include "kernel.h"

// returns current system time in seconds
int get_time_call(void) {    // phase2
   int time;

   asm("int $48;
        movl %%eax, %0"
       : "=g" (time)      // time is output, obtained from eax
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
       : "g" ((int)str)  // str is input, moved into eax
       : "eax"
   );
}

// read in a string from target keyboard (move keyboard input into str)
// See pg 96 for solutions to problems
void read_call(char *str) {
    asm("movl %%eax, %0;
         int $50"
         :
         : "g" ((int)str)
    );
}
