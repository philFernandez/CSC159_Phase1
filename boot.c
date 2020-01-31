// boot.c, 159, phase 1
//
// Team Name: ??????? (Members: ??????...)
#include <spede.h>
#include <kernel.h>
#include <entry.h>
#include <misc.h>
#include <proc.h>


needs to include spede.h kernel.h entry.h misc.h proc.h

// kernel data are all declared here (prototyped in kernel.h):
deaclare an integer: cur_pid for currently selected PID
declare 2 queues: unused_q ready_q
declare a pcb_t array: pcb, size PROC_SIZE
declare a 2D char array: stack, size PROC_SIZE x STACK_SIZE

declare un unsigned integer: sys_tick
declare: struct i386_gate *intr_table

program a void-returning function CreateProc,
that takes an argument of the func_p_t type:
{
   get a PID from unused_q
   add it to ready_q

   clear both the PCB and stack for the new PID

   set its state to READY
   point its tf_p to the correct place in its stack
   use tf_p to set its efl cs eip
}

void main(void) {                   // kernel boots
   clear sys_tick
   init intr_table to INTR_TABLE

   clear both unused_q and ready_q
   add all unused PID's into unused_q

   call fill_gate() to set timer interrupt handling entry (like phase 0)
   send the PIC mask to PIC mask register (like phase 0)

   call CreateProc() to create the Clock process
   set cur_pid to PID 0
   call Loader to load the trapframe of the new process
}

