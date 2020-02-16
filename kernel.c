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
        if (!QisEmpty(&kb.wait_q))
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
    tf_p->eax = cur_second;
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

void WriteChar(char ch) // ask about
{
    static unsigned short *cursor = (unsigned short *)VIDEO_START;
    // columnCount keeps track of columns so we know when starting new row
    static int columnCount = 0;
    unsigned short *p;
    int i;

    // Have to double MAX_COLS*MAX_ROWS because cursor pointer
    // is incremented by two for every new char (2 byte offset)
    if ((int)cursor >= VIDEO_START + 2 * MAX_COLS * MAX_ROWS)
    {
        // Start cursor back at beginning when lower right is reached
        cursor = (unsigned short *)VIDEO_START;
    }

    if (columnCount % 80 == 0)
    {
        // Use p to clear new rows so we can save place of cursor
        p = cursor;
        for (i = 0; i < 80; i++)
        {
            *p = (unsigned short *)(VIDEO_MASK + ' ');
            p++;
        }
    }

    if (ch != CR && ch != LF)
    {
        *cursor = (unsigned short *)(VIDEO_MASK + ch);
        cursor++;
        columnCount++;
    }
}

void ReadService(tf_t *tf_p)
{
    pcb[cur_pid].tf_p = tf_p;

    EnQ(cur_pid, &kb.wait_q);
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
        StrAdd(NUL, kb.buffer);
        cur_pid = DeQ(&kb.wait_q);

        StrCpy(kb.buffer, pcb[cur_pid].tf_p->eax);

        pcb[cur_pid].state = READY;
        EnQ(cur_pid, &ready_q);
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
