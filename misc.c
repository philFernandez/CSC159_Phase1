// misc.c, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#include "spede.h"
#include "kernel.h"

// If q->size is zero returns true
int QisEmpty(q_t *ptr)
{
    return !ptr->size;
}

// if q->size is equal to max size returns true
int QisFull(q_t *ptr)
{
    return ptr->size == Q_SIZE;
}

int DeQ(q_t *ptr)
{
    int item;
    if (QisEmpty(ptr))
        return NA; // -1

    // Get element from front of queue
    item = ptr->q[ptr->head];
    // Adjust head pointer to point at new item in front
    ptr->head = (ptr->head + 1) % Q_SIZE;
    ptr->size--;

    return item;
}

void EnQ(int item, q_t *ptr)
{
    if (QisFull(ptr))
    {
        cons_printf("Panic queue is full, cannot EnQ!\n");
        breakpoint();
    }
    else
    {
        // Adjust tail pointer to point to new item
        ptr->tail = (ptr->tail + 1) % Q_SIZE;
        // Insert new item in queue
        ptr->q[ptr->tail] = item;
        ptr->size++;
    }
}

/**
 * Fill string with NUL
 */
void Bzero(char *s, unsigned n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        s[i] = NUL;
    }
}

void StrAdd(char ch, char *s)
{
    int i = 0;
    while (s[i] != NUL) // Loop ends when NULL is reached in src
        i++;
    s[i] = ch;
    s[i + 1] = NUL;

    /*printf("StrAdd : %s\n", s);*/
}

void StrCpy(char *src, char *dst)
{
    int i = 0;
    while (src[i] != '\0') // Loop ends when NULL is reached in src
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0'; // Properly delimiting dst
}

