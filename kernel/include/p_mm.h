// Basic Operating System.
// Physical Memory Manager.

#ifndef MM_H
#define MM_H

/*
 * Based on http://www.osdever.net/tutorials/view/cottontail-memory-management-a-system-for-allocation-deallocation-accounting/.
 */

/* p_mm.c */
void *p_mm_alloc_pages (int);
void p_mm_dalloc_pages (void *, int);
void p_mm_mark_as_used (int);
void p_mm_mark_as_free (int);

/* kernel_ll.asm */
extern void halt (void);

#endif /* !MM_H */
