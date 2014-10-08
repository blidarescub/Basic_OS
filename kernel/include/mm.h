// Basic Operating System.
// Memory Manager.

#ifndef MM_H
#define MM_H

// Error codes for "map_page()".
#define MAP_SUCCESS			0		// The virtual page was successfully mapped.

// Error codes for "create_page_table()".
#define CPT_SUCCESS			0		// The specified page table was created.
#define CPT_ZERONUM			1		// The `num` argument is less than 0.
#define CPT_BIGNUM			2		// The `num` argument is more than 1023.

// Error codes for "alloc_pages()".
#define ALLOC_SUCCESS       0       // Successfully allocated.
#define ALLOC_ZEROCOUNT     1       // Tried to allocate less than 0.
#define ALLOC_ALREADY       2       // Some of pages are already allocated.

// Error codes for "free_pages()".
#define FREE_SUCCESS        0       // Successfully freed.
#define FREE_ZEROCOUNT      1       // Tried to allocate less than 0.

#include <types.h>

/* mm.c */
int  map_page (int, int);
int  create_page_table (int);
void push_physical_page (int);
int  pop_physical_page (void);
void init_mm (mb_info_t *);
int  alloc_pages (void *, int);
int  free_pages (void *);
void invlpg (void *);

/* kernel_ll.asm */
extern void halt (void);

/* paging_ll.asm */
extern u32 read_cr3 (void);
extern void write_cr3 (u32);

#endif /* !MM_H */
