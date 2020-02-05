// misc.h, 159

#ifndef __MISC__
#define __MISC__
#include "kernel.h"


int QisEmpty(q_t*);

int QisFull(q_t*);

int DeQ(q_t*);

void EnQ(int, q_t*);

void Bzero(char*, unsigned);

void MemCpy(char*, char*, unsigned);

#endif

