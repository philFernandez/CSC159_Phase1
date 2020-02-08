// misc.c, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#include "kernel.h" // uses <> brackets in original
#include "spede.h"
//#include <string.h>

// Impliment Queue for unused_q and ready_q
int QisEmpty(q_t *q)
{
    return (q->head == -1) ? TRUE : FALSE;
}

int QisFull(q_t *q)
{
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == Q_SIZE - 1))
    {
        return TRUE;
    }

    return FALSE;
}

int DeQ(q_t *q)
{
    int pid;
    if (QisEmpty(q))
    {
        return NA;
    }
    else
    {
        // Get the number pointed to by head
        pid = q->q[q->head];

        // Adjust head pointer
        if (q->head == q->tail)
        { // If this is the last number in q, reset the q
            q->head = -1;
            q->tail = -1;
        }
        else
        {
            // Adjust head pointer in circular fashion
            q->head = (q->head + 1) % Q_SIZE;
        }
        // Decrement q->size
        q->size -= 1;
        return pid;
    }
}

void EnQ(int pid, q_t *q)
{
    if (QisFull(q))
    {
        cons_printf("Panic: queue is full, cannot EnQ!\n");
        breakpoint();
    }
    else
    {
        if (q->head == -1)
            q->head = 0;
        q->tail = (q->tail + 1) % Q_SIZE;
        q->q[q->tail] = pid;
        q->size += 1;
    }
}

void Bzero(char *s, unsigned n)
{
    // memset(s, 0x0, n);
    // or
    /*bzero(s, n); */
}
