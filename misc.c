// misc.c, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#include "spede.h"
#include "kernel.h"

/**
 * Implement circular queue data structure for unused_q and ready_q
 */

/**
 * Q empty, return true
 * else return false
 */
int QisEmpty(q_t *q)
{
    return (q->head == -1) ? TRUE : FALSE;
}

/**
 * Q full, return true
 * else return false
 */
int QisFull(q_t *q)
{
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == Q_SIZE - 1))
    {
        return TRUE;
    }

    return FALSE;
}

/**
 * Remove and return element from head
 * Re-adjust head/tail pointers
 */
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

/**
 * Put new element in Q[tail]
 * adjust head/tail pointers
 */
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

/**
 * Fill string with '\0'
 */
void Bzero(char *s, unsigned n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        s[i] = '\0';
    }
}
