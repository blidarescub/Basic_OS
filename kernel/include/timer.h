// Basic Operating System.
// The PIT (timer).

#ifndef TIMER_H
#define TIMER_H

#include <handlers.h>

/* timer.c */
void init_timer_handler (void);
void timer_handler (regs_irq_t *);

#endif /* !TIMER_H */
