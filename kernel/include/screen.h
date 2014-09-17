// Basic Operating System.
// Printing on the screen.

#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH	80
#define SCREEN_HEIGHT	25
#define VBUFFER_SIZE	SCREEN_WIDTH * SCREEN_HEIGHT * 2

/* screen.c */
void init_screen (void);
void clear_screen (void);
void scroll_screen (void);
void putch_at (char, int, int);
void putch (char);
void puts (const char *);

#endif /* !SCREEN_H */
