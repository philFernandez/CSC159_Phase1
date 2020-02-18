// entry.S, entries to kernel, build process trapframe

// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#include <spede/machine/asmacros.h>       // do not use/include "spede.h"

#define KERNEL_STACK_SIZE 32768           // 32 KB should be enough

.text
.comm kernel_stack, KERNEL_STACK_SIZE, 1  // ... by unit of 1 byte

// loads the trapframe of the process to run it
ENTRY(Loader)
   movl 4(%esp), %ebx
   movl %ebx, %esp
   popal
   iret

// build trapframe then go to kernel service code
ENTRY(TimerEntry)
   pushal
   movl %esp, %ecx
   leal kernel_stack+KERNEL_STACK_SIZE, %esp
   pushl %ecx
   cld
   call CNAME(TimerService)


ENTRY(GetTimeEntry)
   pushal
   movl %esp, %ecx
   leal kernel_stack+KERNEL_STACK_SIZE, %esp
   pushl %ecx
   cld
   call CNAME(GetTimeService)

ENTRY(WriteEntry)
   pushal
   movl %esp, %ecx
   leal kernel_stack+KERNEL_STACK_SIZE, %esp
   pushl %ecx
   cld
   call CNAME(WriteService)

ENTRY(ReadEntry)
   pushal
   movl %esp, %ecx
   leal kernel_stack+KERNEL_STACK_SIZE, %esp
   pushl %ecx
   cld
   call CNAME(ReadService)

