// Basic Operating System.
// Functions for working with the memory.

#ifndef MEMORY_H
#define MEMORY_H

#include <types.h>

/* memory.c */
u8 *memcpy (u8 *, u8 *, int);
u8 *memset (u8 *, u8, int);
u16 *memsetw (u16 *, u16, int);

#endif /* !MEMORY_H */
