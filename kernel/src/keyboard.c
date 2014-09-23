// Basic Operating System.
// The keyboard handler.

#include <keyboard.h>
#include <idt.h>
#include <handlers.h>
#include <inoutb.h>
#include <screen.h>
#include <types.h>

// The keyboard buffer.
char keyboard_buffer[8];
int keyboard_buffer_pos;

// Initialize the keyboard handler.
void init_keyboard_handler (void)
{
	// Set the IRQ handler.
	set_irq_handler (1, keyboard_handler);

	// Unmask the IRQ.
	unmask_irq (1);
}

// The keyboard handler itself.
void keyboard_handler (regs_irq_t *regs)
{
	// Get the scancode.
	u8 scancode = inb (0x60);

	// Convert the scancode to a char.
	char ch = scancode2char (scancode);

	if (ch == 0) // Don't print unprintable characters.
		return;

	// Place the char in the buffer.
	keyboard_buffer[keyboard_buffer_pos] = ch;
	++keyboard_buffer_pos;
	if (keyboard_buffer_pos >= 8)
		keyboard_buffer_pos = 0;

	// Print that char (optionally).
	putch (ch);
}

// Convert the scancode to a char.
char scancode2char (u8 scancode)
{
	char keymap[264] =
	{
		0,	27,	'1',	'2',
		'3',	'4',	'5',	'6',
		'7',	'8',	'9',	'0',
		'-',	'=',	'\b',	'\t',
		'q',	'w',	'e',	'r',
		't',	'y',	'u',	'i',
		'o',	'p',	'[',	']',
		'\n',	 0,	'a',	's',
		'd',	'f',	'g',	'h',
		'j',	'k',	'l',	';',
		'\'',	'`',	0,	'\\',
		'z',	'x',	'c',	'v',
		'b',	'n',	'm',	',',
		'.',	'/',	0,	'*',
		0,	' ',	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	'7',
		'8',	'9',	'-',	'4',
		'5',	'6',	'+',	'1',
		'2',	'3',	'0',	'.',
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
		0,	0,	0,	0,
	};

	return keymap[scancode];
}
