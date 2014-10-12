// Basic Operating System.
// Exceptions and IRQs handlers.

#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdint.h>
#include <structs.h>

/* handlers.c */
void excs_handler (regs_exc_t *);
void irqs_handler (regs_irq_t *);
void set_irq_handler (uint32_t, void (*) (regs_irq_t *));
void unset_irq_handler (uint32_t);

/* kernel_ll.asm */
extern void halt (void);
extern uint32_t read_cr2 (void);

#endif /* !HANDLERS_H */
