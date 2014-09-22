// Basic Operating System.
// The C part of the kernel.

#include <screen.h>
#include <idt.h>
#include <keyboard.h>

// The C kernel main.
void kernel_main (void)
{
	init_screen ();
	clear_screen ();

	setup_idt ();
	init_keyboard_handler ();

	puts ("Hello World");
}
