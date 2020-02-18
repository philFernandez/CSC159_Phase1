// kernel.h, 159, kernel stuff prototyped here
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#ifndef __KERNEL__
#define __KERNEL__

// H/W & I/O stuff
#define CS              8
#define FLAGS           0x212
#define INTR_TABLE      0x3914c
#define TIMER           32
#define GET_TIME        48
#define WRITE           49
#define READ            50
#define PIC_MASK_REG    0x21
#define PIC_MASK        ~0x01
#define PIC_CONTROL_REG 0x20
#define TIMER_ACK       0x60
#define VIDEO_MASK      0x0f00
#define VIDEO_START     0xb8000

// system limit stuff
#define TIME_SIZE  100
#define PROC_SIZE  20
#define STACK_SIZE 4096
#define Q_SIZE     20
#define MAX_COLS   80
#define MAX_ROWS   25

// prog logic stuff
#define TRUE     1
#define FALSE    0
#define NUL      0
#define NA       -1
#define STR_SIZE 100
#define CR       '\r'
#define LF       '\n'

typedef void (*func_p_t)(void);

typedef enum
{
    UNUSED,
    READY,
    RUN,
    WAIT
} state_t;

typedef struct
{
    unsigned edi, esi, ebp, esp, ebx, edx, ecx, eax, eip, cs, efl;
} tf_t;

typedef struct
{
    state_t state;
    unsigned run_tick, total_tick;
    tf_t *tf_p;
} pcb_t;

typedef struct
{
    int head, tail, size;
    int q[Q_SIZE];
} q_t;

typedef struct
{
    char buffer[STR_SIZE];
    q_t wait_q;
} kb_t;

extern int cur_pid;
extern unsigned sys_tick;
extern q_t unused_q, ready_q;
extern pcb_t pcb[PROC_SIZE];
extern char stack[PROC_SIZE][STACK_SIZE];
extern kb_t kb;

void Swapper(void);
void TimerService(tf_t *);
void GetTimeService(tf_t *);
void WriteService(tf_t *);
void ReadService(tf_t *);
void WriteChar(char);
void KbService(char);

#endif

// vi: ft=c
