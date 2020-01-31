// misc.c, 159

include spede.h and kernel.h

program function QisEmpty (given a pointer to a queue):
   return TRUE if queue is empty, else FALSE

program function QisFull (given a pointer to a queue):
   return TRUE if queue is full, else FALSE

program function DeQ (given a pointer to a queue):
   if empty, return NA
   get the number pointed to by the head in the queue
   move the head, alter the size
   return the number

program function EnQ (given a number and pointer to a queue):
   if the queue is full:
      cons_printf("Panic: queue is full, cannot EnQ!\n");
      go into GDB // breakpoint();

   enqueue the number to where the tail points to in the queue
   move the tail, alter the size

program function Bzero, given a char pointer and unsigned bytes:
   NUL-fill each byte starting at where the pointer points
   for a number of bytes

program function MemCpy, given two char pointers as the starting
location of the source of copy, and the destination location of
the copy, and an unsigned number of bytes:
   copy each byte from the starting location to the destination
   for a number of bytes

