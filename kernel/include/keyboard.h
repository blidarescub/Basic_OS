// Basic Operating System.
// The keyboard handler.

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <types.h>

/* keyboard.c */
void init_keyboard_handler (void);
void keyboard_handler (regs_irq_t *);
char scancode2char (u8);
u8 getch (void);

#endif /* !KEYBOARD_H */