// Basic Operating System.
// The C part of the kernel.

#include <screen.h>

#include <idt.h>
#include <keyboard.h>
#include <timer.h>

#include <paging.h>
#include <mm.h>

#include <types.h>

// The C kernel main.
void kernel_main ()
{
	init_screen ();
	clear_screen ();

	setup_idt ();
	init_keyboard_handler ();
	init_timer_handler ();

	init_paging ();
	init_mm ();

	char *str = (char *) mm_alloc_pages (1);
	str[0] = 'H';
	str[1] = 'e';
	str[2] = 'l';
	str[3] = 'l';
	str[4] = 'o';
	str[5] = ' ';
	str[6] = 'W';
	str[7] = 'o';
	str[8] = 'r';
	str[9] = 'l';
	str[10] = 'd';
	str[11] = '!';
	str[12] = 0;
	puts (str);
	puts ("\n");

	mm_dalloc_pages (str, 1);
	mm_alloc_pages (1);
}
