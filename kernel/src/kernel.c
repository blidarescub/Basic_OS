// Basic Operating System.
// The C part of the kernel.

#include <screen.h>
#include <idt.h>

// The C kernel main.
void kernel_main (void)
{
	init_screen ();
	clear_screen ();

	setup_idt ();

	puts ("Hello World");
}
