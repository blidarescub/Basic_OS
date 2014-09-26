// Basic Operating System.
// The C part of the kernel.

#include <screen.h>
#include <string.h>
#include <idt.h>
#include <keyboard.h>
#include <timer.h>
#include <paging.h>
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

	puts ("Hello World");
}
