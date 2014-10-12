// Basic Operating System.
// Paging.

#ifndef PAGING_H
#define PAGING_H

/*
 * Page Directory (a table that holds info about Page Tables) is
 *  located from 0x9C000 to 0x9D000 (4 kB).
 * Page Tables (tables that hold info about pages itself) are
 *  located from 0x9D000 to 0x9E000 (4 kB).
 */

#include <stdint.h>

/* paging.c */
void init_paging (void);

/* paging_ll.asm */
extern uint32_t  read_cr0 (void);
extern void      write_cr0 (uint32_t);
extern uint32_t  read_cr3 (void);
extern void      write_cr3 (uint32_t);

/* kernel_ll.asm */
extern void update_segregs (void);

#endif /* !PAGING_H */
