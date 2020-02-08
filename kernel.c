// kernel.c, 159, phase 1
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#include "kernel.h"
#include "entry.h"
#include "misc.h"
#include "proc.h"
#include "spede.h"

void TimerService(tf_t *tf_p)
{
    char ch;

    pcb[cur_pid].tf_p = tf_p;

    if (cons_kbhit())
    {
        ch = cons_getchar();
        if(ch == 'g')breakpoint();
    }

    // notify PIC the timer is serviced
    outportb(PIC_CONTROL_REG, TIMER_ACK);

    sys_tick++;
    pcb[cur_pid].run_tick++;
    pcb[cur_pid].total_tick++;

    if (pcb[cur_pid].run_tick == TIME_SIZE)
    {
        EnQ(cur_pid, &ready_q);
        pcb[cur_pid].state = READY;
        cur_pid = NA;
        Swapper();
    }
    Loader(pcb[cur_pid].tf_p);
}

void Swapper(void)
{
    if(QisEmpty(ready_q))
    {
        cons_printf("Kernel: panic, no more process ready to run!\n");
        breakpoint();
    }

    cur_pid = DeQ(ready_q);
    pcb[cur_pid].run_tick = 0;
    pcb[cur_pid].state = RUN;
}
