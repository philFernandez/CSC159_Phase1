// misc.h, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)
#include "kernel.h"

#ifndef __MISC__
#define __MISC__


int QisEmpty(q_t*);

int QisFull(q_t*);

int DeQ(q_t*);

void EnQ(int, q_t*);

void Bzero(char*, unsigned);

void MemCpy(char*, char*, unsigned);

#endif

