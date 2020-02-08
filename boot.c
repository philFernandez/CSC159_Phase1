// boot.c, 159, phase 1
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#include "entry.h"
#include "kernel.h"
#include "misc.h"
#include "proc.h"
#include "spede.h"


int cur_pid; // for currently selected PID
q_t unused_q;
q_t ready_q;

pcb_t pcb[PROC_SIZE];               // process control block
char stack[PROC_SIZE][STACK_SIZE];

unsigned sys_tick;
struct i386_gate *intr_table;

void CreateProc(func_p_t p)
{
    // Get unused PID from unused_q
    cur_pid = DeQ(&unused_q);
    // Add PID to ready_q
    EnQ(cur_pid, &ready_q);

    Bzero((char *)&pcb[cur_pid], sizeof(q_t));
    Bzero(&stack[cur_pid][0], STACK_SIZE);

    pcb[cur_pid].state = READY;
    pcb[cur_pid].tf_p = &stack[cur_pid][STACK_SIZE - sizeof(tf_t)];

    // use tf_p to set its efl cs eip

    pcb[cur_pid].tf_p->eif = efl;
    pcb[cur_pid].tf_p->cs = cs;
    pcb[cur_pid].tf_p->eip = (int) p;


}

void main(void)
{
    int i = 0;
    // clear sys_tick
    sys_tick = 0;
    intr_table = (struct i386_gate *)INTR_TABLE;
    // clear both unused_q and ready_q
    Bzero((char *)&unused_q, Q_SIZE);
    Bzero((char *)&ready_q, Q_SIZE);

    unused_q.head = -1;
    unused_q.tail = -1;
    // add unused PIDs to unused_q

    ready_q.head = -1;
    ready_q.tail = -1;

    while (!QisFull(&unused_q))
    {
        EnQ(i, &unused_q);
        i++;
    }

    fill_gate(&intr_table[TIMER], (int)TimerEntry, get_cs(), ACC_INTR_GATE, 0);
    outportb(PIC_MASK_REG, PIC_MASK);
    asm("sti");

    func_p_t clockPtr = (void *)Clock;
    clockPtr();

    CreateProc(clockPtr);
    // call Loader to load the trapframe of the new process
}
