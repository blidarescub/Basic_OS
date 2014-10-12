// Basic Operating System.
// inb() and outb().

#ifndef INOUTB_H
#define INOUTB_H

#include <stdint.h>

/* inoutb.c */
uint8_t inb (uint16_t);
void outb (uint16_t, uint8_t);

#endif /* !INOUTB_H */
