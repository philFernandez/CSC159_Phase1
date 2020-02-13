// kernel.h, 159, kernel stuff prototyped here
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#ifndef __KERNEL__
#define __KERNEL__

// H/W & I/O stuff
#define CS              8       // Code Segment register
#define FLAGS           0x212   // CPU flags for trapframe
#define INTR_TABLE      0x3914c // location of the interrupt table
#define TIMER           32      // timer event code
#define GET_TIME        48
#define WRITE           49
#define READ            50
#define PIC_MASK_REG    0x21    // I/O # of PIC mask register
#define PIC_MASK        ~0x01   // mask value for PIC mask
#define PIC_CONTROL_REG 0x20    // I/O # of PIC control register
#define TIMER_ACK       0x60    // control code sent to PIC
#define VIDEO_MASK      0x0f00  // bold white on black
#define VIDEO_START     0xb8000 // upper-left corner

// system limit stuff
#define TIME_SIZE  100  // max timer count, then rotate process
#define PROC_SIZE  20   // max number of processes
#define STACK_SIZE 4096 // process stack in bytes
#define Q_SIZE     20   // capacity of a process queue

// prog logic stuff
#define TRUE  1
#define FALSE 0
#define NUL   0
#define NA    -1

// For process I/O functionality

#define STR_SIZE 100
#define CR       '\r'
#define LF       '\n'

typedef void (*func_p_t)(void); // void-return function pointer type

typedef enum
{
    UNUSED,
    READY,
    RUN,
    WAIT
} state_t; // process states

typedef struct
{
    unsigned edi, esi, ebp, esp, ebx, edx, ecx, eax, eip, cs, efl;
} tf_t; // 'trapframe' type

typedef struct
{
    state_t state;                 // state of process
    unsigned run_tick, total_tick; // runtime of process and lifespan
    tf_t *tf_p;                    // points to proc's trapframe
} pcb_t;

typedef struct
{                         // circular queue
    int head, tail, size; // head dequeue, tail enqueue, current size
    int q[Q_SIZE];        // PID's are queued in que[] array
} q_t;

typedef struct
{ // keyboard type
    int buffer[STR_SIZE];
    q_t wait_q;
} kb_t;

// kernel data are all declared in boot.c during bootstrap
extern int cur_pid;           // PID currently selected as running process
extern unsigned sys_tick;     // counting for a system time
extern q_t unused_q, ready_q; // unused PID's and ready-to-run PID's
extern pcb_t pcb[PROC_SIZE];  // Process Control Blocks
extern char stack[PROC_SIZE][STACK_SIZE]; // process runtime stacks
extern kb_t kb;

// Prototypes
void Swapper(void);
void TimerService(tf_t *);
void GetTimeService(tf_t *);
void WriteService(tf_t *);
void ReadService(tf_t *);
void WriteChar(char);
void KbService(char);

#endif

// vi: ft=c
