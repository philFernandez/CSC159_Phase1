// entry.h
// prototypes those in entry.S
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

#ifndef __ENTRY__
#define __ENTRY__

#ifndef ASSEMBLER

__BEGIN_DECLS

#include "kernel.h"

void TimerEntry(void);
void GetTimeEntry(void);
void WriteEntry(void);
void ReadEntry(void);
void Loader(tf_t *);

__END_DECLS

#endif // ASSEMBLER

#endif // __ENTRY__

