// Basic Operating System.
// Exceptions and IRQs handlers.

#ifndef HANDLERS_H
#define HANDLERS_H

#include <types.h>

/* handlers.c */
void excs_handler (regs_exc_t *);
void irqs_handler (regs_irq_t *);
void set_irq_handler (int, void (*) (regs_irq_t *));
void unset_irq_handler (int);

/* kernel_ll.asm */
extern void halt (void);

#endif /* !HANDLERS_H */
