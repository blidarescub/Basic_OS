// Basic Operating System.
// Memory Manager.

#ifndef MM_H
#define MM_H

// Error codes for "map_page()" and "map_pages()".
#define MAP_SUCCESS			0		// The virtual page(s) was successfully
                                    // mapped.

// Error codes for "alloc_pages()".
#define ALLOC_SUCCESS       0       // Successfully allocated.
#define ALLOC_ZEROCOUNT     1       // Tried to allocate less than 0.
#define ALLOC_ALREADY       2       // Some of pages are already allocated.

// Error codes for "free_pages()".
#define FREE_SUCCESS        0       // Successfully freed.
#define FREE_ZEROCOUNT      1       // Tried to allocate less than 0.

#include <types.h>

/* mm.c */
    /* Mapping. */
    int map_page (int, int);
    int map_pages (int, int, int);

    /* Page directories and page tables. */
    void switch_page_directory (void *);
    u32 *create_page_table (int);

    /* Physical memory manager. */
    void push_physical_page (int);
    int  pop_physical_page (void);

    /* Virtual memory manager. */
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
