// kernel.c, 159, phase 1
//
// Team Name: ??????? (Members: ??????...)

#include <entry.h>
#include <kernel.h>
#include <misc.h>
#include <proc.h>
#include <spede.h>

void TimerService(tf_t *trapframe) {}
/*program a void-returning function TimerService which receives*/
/*an argument that is the type: tf_t * {*/
save tf_p to the PCB of cur_pid

    if cons_kbhit()
    : read in the character if it 's ' g' goto GDB

      ACK to PIC the timer event(like phase 0)

          increment sys_tick by 1 increment both run_tick
      and total_tick by 1 in the PCB of cur_pid

              if its run_tick equals TIME_SIZE
    : move
      /
      append cur_pid to ready_q alter /
      downgrade its state clear cur_pid to become NA
}

if
    cur_pid is NA call
    Swapper() to find one call Loader with the tf_p of cur_pid
}

program a void - returning function Swapper that takes no argument
{
    if
        ready_q is empty
            : cons_printf("Kernel: panic, no more process ready to run!\n");
    goto GDB

        set cur_pid to a PID dequeued from ready_q clear run_tick of
            the new cur_pid set the state of cur_pid to RUN
}
