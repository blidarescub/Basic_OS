// Basic Operating System.
// Paging.

#ifndef PAGING_H
#define PAGING_H

/*
 * Page Directory (a table that holds info about Page Tables) is
 *  located from 0x9C000 to 0x9D000.
 * Page Table (a table that holds info about pages itself) is
 *  located from 0x9D000 to 0x9E000.
 */

#include <types.h>

/* paging.c */
void init_paging (void);

/* paging_ll.asm */
extern u32  read_cr0 (void);
extern void write_cr0 (u32);
extern u32  read_cr3 (void);
extern void write_cr3 (u32);

#endif /* !PAGING_H */
