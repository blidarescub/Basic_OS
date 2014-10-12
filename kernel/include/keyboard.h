// Basic Operating System.
// The keyboard handler.

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <structs.h>

/* keyboard.c */
void  init_keyboard_handler (void);
void  keyboard_handler (regs_irq_t *);
char  scancode2char (uint8_t);
char  getch (void);
char *gets (int);

#endif /* !KEYBOARD_H */
