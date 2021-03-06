// misc.h, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#ifndef __MISC__
#define __MISC__

#include "kernel.h"

int QisEmpty(q_t*);

int QisFull(q_t*);

int DeQ(q_t*);

void EnQ(int, q_t*);

void Bzero(char*, unsigned);

void MemCpy(char*, char*, unsigned);

void StrAdd(char, char*);

void StrCpy(char*, char*);

#endif

