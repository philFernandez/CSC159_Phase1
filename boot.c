
// boot.c, 159, phase 1
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#include "spede.h"
#include "kernel.h"
#include "entry.h"
#include "misc.h"
#include "proc.h"

int cur_pid; // For currently selected PID
q_t unused_q;
q_t ready_q;
kb_t kb;

pcb_t pcb[PROC_SIZE]; // Process control block

char stack[PROC_SIZE][STACK_SIZE];

unsigned sys_tick;
struct i386_gate *intr_table;

void CreateProc(func_p_t p)
{
    // Get unused PID from unused_q
    cur_pid = DeQ(&unused_q);
    // Add PID to ready_q
    EnQ(cur_pid, &ready_q);

    // Clear pcb and stack for new proc
    Bzero((char *)&pcb[cur_pid], sizeof(&pcb[0]));
    Bzero(&stack[cur_pid][0], STACK_SIZE);

    // Set up pcb for new proc
    pcb[cur_pid].state = READY;
    pcb[cur_pid].tf_p = (tf_t *)&stack[cur_pid][STACK_SIZE - sizeof(tf_t)];
    pcb[cur_pid].tf_p->efl = FLAGS;
    pcb[cur_pid].tf_p->cs = CS;
    pcb[cur_pid].tf_p->eip = (int)p;
}

void main(void)
{
    int i = 0;
    // Clear sys_tick
    sys_tick = 0;
    intr_table = (struct i386_gate *)INTR_TABLE;

    // Clear both unused_q and ready_q
    Bzero((char *)&unused_q, sizeof(q_t));
    Bzero((char *)&ready_q, sizeof(q_t));
    Bzero((char *)&kb, sizeof(kb_t));
    kb.wait_q.head = 0;
    kb.wait_q.tail = -1;
    kb.wait_q.size = 0;

    unused_q.head = 0;
    unused_q.tail = -1;
    unused_q.size = 0;

    ready_q.head = 0;
    ready_q.tail = -1;
    ready_q.size = 0;

    // Add unused PIDs to unused_q
    while (!QisFull(&unused_q))
    {
        EnQ(i, &unused_q);
        i++;
    }

    fill_gate(&intr_table[TIMER], (int)TimerEntry, get_cs(), ACC_INTR_GATE, 0);
    outportb(PIC_MASK_REG, PIC_MASK);
    asm("sti");

    fill_gate(&intr_table[GET_TIME], (int)GetTimeEntry, get_cs(), ACC_INTR_GATE,0);
    fill_gate(&intr_table[WRITE], (int)WriteEntry, get_cs(), ACC_INTR_GATE, 0);
    fill_gate(&intr_table[READ], (int)ReadEntry, get_cs(), ACC_INTR_GATE, 0);

    CreateProc(Clock);
    CreateProc(Init);
    cur_pid = DeQ(&ready_q);
    Loader(pcb[cur_pid].tf_p);
}
