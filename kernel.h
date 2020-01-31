// kernel.h, 159, kernel stuff prototyped here

#ifndef __KERNEL__
#define __KERNEL__

Define these constants:
// H/W & I/O stuff
CS 8                   // Code Segment register
FLAGS 0x212            // CPU flags for trapframe
INTR_TABLE 0x3914c     // location of the interrupt table
TIMER 32               // timer event code
PIC_MASK_REG 0x21      // I/O # of PIC mask register
PIC_MASK ~0x01         // mask value for PIC mask
PIC_CONTROL_REG 0x20   // I/O # of PIC control register
TIMER_ACK 0x60         // control code sent to PIC
VIDEO_MASK 0x0f00      // bold white on black
VIDEO_START 0xb8000    // upper-left corner

// system limit stuff
TIME_SIZE 300          // max timer count, then rotate process
PROC_SIZE 20            // max number of processes
STACK_SIZE 4096        // process stack in bytes
Q_SIZE 20              // capacity of a process queue

// prog logic stuff
TRUE 1
FALSE 0
NUL 0
NA -1

typedef void (*func_p_t)(void); // void-return function pointer type

typedef enum {UNUSED, READY, RUN} state_t;  // process states

typedef struct {
   unsigned edi, esi, ebp, esp, ebx, edx, ecx, eax, eip, cs, efl;
} tf_t;                      // 'trapframe' type

typedef struct {
   state_t state;            // state of process
   unsigned run_tick, total_tick; // runtime of process and lifespan
   tf_t *tf_p;               // points to proc's trapframe
} pcb_t;                     

typedef struct {             // circular queue
   int head, tail, size;     // head dequeue, tail enqueue, current size
   int q[Q_SIZE];            // PID's are queued in que[] array
} q_t;

// kernel data are all declared in boot.c during bootstrap
extern int cur_pid;                 // PID currently selected as running process
extern unsigned sys_tick;           // counting for a system time
extern q_t unused_q, ready_q;       // unused PID's and ready-to-run PID's
extern pcb_t pcb[PROC_SIZE];        // Process Control Blocks
extern char stack[PROC_SIZE][STACK_SIZE];  // process runtime stacks

void Swapper(void);
void TimerService(tf_t *);

#endif

