// Basic Operating System.
// Memory Manager.

#ifndef MM_H
#define MM_H

/*
 * Based on http://www.osdever.net/tutorials/view/cottontail-memory-management-a-system-for-allocation-deallocation-accounting/.
 */

/* mm.c */
void init_mm (void);
void *mm_alloc_pages (int);
void mm_mark_as_used (int);
void mm_mark_as_free (int);

/* kernel_ll.asm */
extern void halt (void);

#endif /* !MM_H */
