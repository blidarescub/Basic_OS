// Basic Operating System.
// The keyboard handler.

#include <keyboard.h>
#include <idt.h>
#include <handlers.h>
#include <mm.h>
#include <inoutb.h>
#include <types.h>

#include <screen.h>

// The keyboard buffer.
char keyboard_buffer[8];
int keyboard_buffer_pos;

// An address of an allocated page.
int *page_addr;
// The last used address in the allocated page.
int last_used_addr;
// More info: for getting strings from user input, we need to keep somewhere
// them. So, we allocate pages for it. In one page there are 4 KB of memory.
// This variable keeps the address of the last string. Thus, we can check if
// there is enough bytes left in the page so we can store the string there.
// Warning: I think it's impossible to use gets() in userspace, since it
// returns the virtual address. Though, we can make a trick: a system call
// (a function that can be called from userspace using interrupts) can do this:
//   * Count the number of bytes required to store the string (including zero
//     byte).
//   * Allocate the calculated number of bytes (in the virtual address space
//     of a process).
//   * Return the address.
// However, it's not a full list of actions. There may be other actions between
// the 1 and 2 and between the 2 and 3 ones.

// Initialize the keyboard handler.
void init_keyboard_handler (void)
{
	// Set the IRQ handler.
	set_irq_handler (1, keyboard_handler);

	// Unmask the IRQ.
	unmask_irq (1);

	// Initialize variables.
	page_addr = 0;
	last_used_addr = 0;
}

// The keyboard handler itself.
void keyboard_handler (regs_irq_t *regs)
{
	// Get the scancode.
	u8 scancode = inb (0x60);

	// Convert the scancode to a char.
	char ch = scancode2char (scancode);

	if (ch != 0) // Zero means "do not save in the buffer".
	{
		// Update the position in the buffer.
		++keyboard_buffer_pos;
		if (keyboard_buffer_pos > 7)
			keyboard_buffer_pos = 0;

		// Place the char in the buffer.
		keyboard_buffer[keyboard_buffer_pos] = ch;
	}
}

// Convert the scancode to a char.
char scancode2char (u8 scancode)
{
	char keymap[0x54] =
	{
		 0,		27,		'1',	'2',
		'3',	'4',	'5',	'6',
		'7',	'8',	'9',	'0',
		'-',	'=',	'\b',	'\t',
		'q',	'w',	'e',	'r',
		't',	'y',	'u',	'i',
		'o',	'p',	'[',	']',
		'\n',	 0,		'a',	's',
		'd',	'f',	'g',	'h',
		'j',	'k',	'l',	';',
		'\'',	'`',	 0,		'\\',
		'z',	'x',	'c',	'v',
		'b',	'n',	'm',	',',
		'.',	'/',	 0,		'*',
		 0,		' ',	 0,		 0,
		 0,		 0,		 0,		 0,
		 0,		 0,		 0,		 0,
		 0,		 0,		 0,		'7',
		'8',	'9',	'-',	'4',
		'5',	'6',	'+',	'1',
		'2',	'3',	'0',	'.',
	};

	if (scancode > 0x53)
	{
		return 0;
	}

	if (keymap[scancode] != 0)
	{
		return keymap[scancode];
	}
	else
	{
		return 0;
	}
}

// Get a char from user input.
char getch (void)
{
	char ch;

	while (1)
	{
		if (keyboard_buffer_pos == 0)
		{
			keyboard_buffer_pos = 7;
		}
		else
		{
			--keyboard_buffer_pos;
		}

		ch = keyboard_buffer[keyboard_buffer_pos];

		if (ch != 0) // Is there a character?
		{
			keyboard_buffer[keyboard_buffer_pos] = 0;

			putch (ch);

			if (keyboard_buffer_pos == 0)
				keyboard_buffer_pos = 7;
			else
				--keyboard_buffer_pos;
			break;
		}
	}

	return ch;
}

// Get a string (characters until ENTER) from user input.
char *gets (int max_length)
{
	if (page_addr == 0) // A page is not allocated (the first call of this
						// function)?
	{
		page_addr = (int *) pop_physical_page ();
		last_used_addr = 0;
	}

	// Not enough bytes left?
	if (last_used_addr > 4096 || (4096 - last_used_addr) < max_length)
	{
		// Alocate a new page.
		page_addr = (int *) pop_physical_page ();

		// Reset the last used address.
		last_used_addr = 0;
	}

	// If we're here, then there are enough bytes in the page "page_addr" to
	// store our string.

	// A pointer to the string.
	char *str = (char *) (page_addr + last_used_addr);

	// Read a string and write to the "str".
	int i;
	int enter = 0; // Was ENTER printed?
	for (i = 0; i < max_length - 1; ++i) // -1 to store zero byte.
	{
		char ch = getch ();

		if (ch == '\n') // ENTER was pressed?
		{
			enter = 1;
			break; // Exit from the loop.
		}

		str[i] = ch;
	}

	if (enter == 0)
		putch ('\n');

	str[i] = 0; // Write a zero byte (end of string).

	// Update the last used address.
	last_used_addr += i;

	// Return the pointer.
	return str;
}
