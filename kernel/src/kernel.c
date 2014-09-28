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

	mm_mark_as_used (0);

//	puts ("Hello World!\n");

	mm_alloc_pages (4);
}
