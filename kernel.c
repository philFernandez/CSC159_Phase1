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
        pcb[cur_pid].state = READY;
        cur_pid = NA;
        Swapper();
    }
    Loader(pcb[cur_pid].tf_p);
}

void GetTimeService(tf_t *tf_p)
{
    // Ask professor if this is right??
    tf_p->eax = sys_tick;
    Loader(tf_p);
}

void WriteService(tf_t *tf_p)
{
    // eax has the address to the string we need to print
    char *charsToWrite = (char *)tf_p->eax;

    while (*charsToWrite != NUL)
    {
        WriteChar(*charsToWrite);
        charsToWrite++;
    }

    // Call loader to resume process that was happening before WriteChar?
    Loader(tf_p);
}

void WriteChar(char c) // ask about
{
    static unsigned short *cursor = (unsigned short *)VIDEO_START;

    if (cursor % 80 == 0) // cursor is at beginning of row
    {
        while (TRUE)
        {
            for (i = 0; i < 80; i++)
                *p = " " + VIDEO_MASK;
        }
    }

    if (c != CR || c != LF) // c is a normal character
    {
        cursor = c + VIDEO_MASK;
        cursor++;
    }
    if (cursor > 75 * 25)
    {
        cursor = (unsigned short *)VIDEO_START;
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
