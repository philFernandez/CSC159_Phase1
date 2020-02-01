// misc.c, 159
#include <kernel.h>
#include <spede.h>

// Can also check if q->tail == q->head
// That should mean that it is empty
int QisEmpty(q_t *q) { return (q->size == 0) ? TRUE : FALSE; }

int QisFull(q_t *q) { return (q->size == Q_SIZE) ? TRUE : FALSE; }

int DeQ(q_t *q) {
  if (QisEmpty(q))
    return NA;

  int pid = q->q[q->head];
  q->head = (q->head + 1) % Q_SIZE;
  q->size -= 1;
  return pid;
}

void EnQ(int pid, q_t *q) {
  if (QisFull(q)) {
    cons_printf("Panic: queue is full, cannot EnQ!\n");
    breakpoint();
  } else {
    q->q[q->tail] = pid;
    q->tail = (q->tail + 1) % Q_SIZE;
    q->size += 1;
  }
}

program function Bzero, given a char pointer and unsigned bytes:
NUL-fill each byte starting at where the pointer points
for a number of bytes

program function MemCpy, given two char pointers as the starting
location of the source of copy, and the destination location of
the copy, and an unsigned number of bytes:
copy each byte from the starting location to the destination
for a number of bytes
