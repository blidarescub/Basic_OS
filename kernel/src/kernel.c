// Basic Operating System.
// The C part of the kernel.

#include <screen.h>

// The C kernel main.
void kernel_main (void)
{
	init_screen ();
	clear_screen ();
	puts ("Hello World");
}
