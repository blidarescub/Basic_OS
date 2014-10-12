// Basic Operating System.
// Memory Manager.

#ifndef MM_H
#define MM_H

// Error codes for "map_page()" and "map_pages()".
#define MAP_SUCCESS			0		// The virtual page(s) was successfully
                                    // mapped.

// Error codes for "alloc_pages()".
#define ALLOC_SUCCESS       0       // Successfully allocated.
#define ALLOC_ALREADY       1       // Some of pages are already allocated.

// Error codes for "free_pages()".
#define FREE_SUCCESS        0       // Successfully freed.

#include <stdint.h>
#include <stddef.h>
#include <structs.h>

// Memory map descriptor.
typedef struct
{
    uint32_t addr;
    uint32_t length;
} __attribute__ ((packed)) mmap_t;

/* mm.c */
    /* Mapping. */
    int map_page (uint32_t, uint32_t);
    int map_pages (uint32_t, uint32_t, size_t);

    /* Page directories and page tables. */
    void      switch_page_directory (void *);
    uint32_t *create_page_table (int);

    /* Physical memory manager. */
    void     push_physical_page (uint32_t);
    uint32_t pop_physical_page (void);

    /* Virtual memory manager. */
    void init_mm (mb_info_t *, mmap_t);
    int  alloc_pages (void *, size_t);
    int  free_pages (void *);
    void invlpg (uint32_t);

/* kernel_ll.asm */
extern void halt (void);

/* paging_ll.asm */
extern uint32_t read_cr3 (void);
extern void write_cr3 (uint32_t);

#endif /* !MM_H */
