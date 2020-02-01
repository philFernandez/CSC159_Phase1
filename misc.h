// misc.h, 159

#ifndef __MISC__
#define __MISC__

#include "kernel.h" // need definition of 'q_t' below

int
QisEmpty(q_t*);

int
QisFull(q_t*);

int
DeQ(q_t*);

void
EnQ(int, q_t*);


//typedef struct {             // circular queue
   //int head, tail, size;     // head dequeue, tail enqueue, current size
   //int q[Q_SIZE];            // PID's are queued in que[] array
//} q_t;


#endif

