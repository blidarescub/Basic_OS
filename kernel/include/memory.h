// Basic Operating System.
// Functions for working with the memory.

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

/* memory.c */
uint8_t *memcpy (uint8_t *, uint8_t *, int);
uint8_t *memset (uint8_t *, uint8_t, int);
uint16_t *memsetw (uint16_t *, uint16_t, int);

#endif /* !MEMORY_H */
