// Basic Operating System.
// Memory Manager.

#ifndef MM_H
#define MM_H

// Error codes for "alloc_pages()".
#define ALLOC_SUCCESS       0       // Successfully allocated.
#define ALLOC_ZEROCOUNT     1       // Tried to allocate less than 0.
#define ALLOC_ALREADY       2       // Some of pages are already allocated.

// Error codes for "free_pages()".
#define FREE_SUCCESS        0       // Successfully freed.
#define FREE_ZEROCOUNT      1       // Tried to allocate less than 0.
#define FREE_ALREADY        2       // Some of pages are already free.

#include <types.h>

/* mm.c */
void push_physical_page (int);
int  pop_physical_page (void);
void init_mm (int);
int  alloc_pages (void *, int);
int  free_pages (void *);
void invlpg (void *);

/* kernel_ll.asm */
extern void halt (void);

/* paging_ll.asm */
extern u32 read_cr3 (void);

#endif /* !MM_H */
