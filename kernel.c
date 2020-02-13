// kernel.c, 159, phase 1
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#include "spede.h"
#include "kernel.h"
#include "proc.h"
#include "misc.h"
#include "entry.h"

void TimerService(tf_t *tf_p)
{
    char ch;

    pcb[cur_pid].tf_p = tf_p;

    if (cons_kbhit())
    {
        ch = cons_getchar();
        if (ch == 'g')
            breakpoint();
        if (!QisEmpty(&wait_q))
            KbService(ch);
    }

    // notify PIC the timer is serviced
    outportb(PIC_CONTROL_REG, TIMER_ACK);

    sys_tick++;
    pcb[cur_pid].run_tick++;
    pcb[cur_pid].total_tick++;

    if (pcb[cur_pid].run_tick == TIME_SIZE)
    {
        EnQ(cur_pid, &ready_q);
        pcb[cur_pid].state = UNUSED; // should be READY??
        cur_pid = NA;
        Swapper();
    }
    Loader(pcb[cur_pid].tf_p);
}

void Swapper(void)
{
    if (QisEmpty(&ready_q))
    {
        cons_printf("Kernel: panic, no more process ready to run!\n");
        breakpoint();
    }

    cur_pid = DeQ(&ready_q);
    pcb[cur_pid].run_tick = 0;
    pcb[cur_pid].state = RUN;
}

void GetTimeService(tf_t *tf_p)
{
    pcb[cur_pid].tf_p->eax = ;
    Loader(pcb[cur_pid].tf_p);
}

void WriteService(tf_t *tf_p)
{
    pcb[cur_pid].tf_p->eax =

        for (int i =) Loader(pcb[cur_pid].tf_p);
}

void WriteChar(char c) // ask about
{
    static unsigned short *cursor = (typecast)VIDEO_START;

    if (cursor)
    {
        if (c != CR || c != LF)
        {
        }
    }
}

void ReadService(tf_t *tf_p)
{
    pcb[cur_pid].tf_p = tf_p;

    EnQ(cur_pid, &kb->wait_q);
    pcb[cur_pid].state = WAIT;
    cur_pid = NA;

    Swapper();
    Loader(pcb[cur_pid].tf_p);
}

void KbService(char c)
{
    WriteChar(c);

    if (c != CR)
        StrAdd(c, kb.buffer);
    else
    {
        StrAdd('\0', kb.buffer);
        cur_pid = DeQ(&kb.wait_q);

        StrCpy(kb.buffer, pcb[cur_pid].tf_p->eax);

        pcb[cur_pid].state = READY;
        Bzero(kb.buffer, sizeof(kb.buffer));
    }
}
