// Basic Operating System.
// The C part of the kernel.

#include <screen.h>
#include <string.h>

#include <idt.h>
#include <keyboard.h>
#include <timer.h>

#include <paging.h>
#include <mm.h>

#include <types.h>

// The C kernel main.
void kernel_main (mb_info_t *mb_info)
{
	init_screen ();
	clear_screen ();

	setup_idt ();
	init_keyboard_handler ();
	init_timer_handler ();

	init_paging ();
	init_mm (mb_info->mem_upper * 1024); // GRUB gives us the memory size in
	// kilobytes. We need to convert it bytes, so multiply it by 1024.

	clear_screen ();
	puts ("Hello World!\n");
	puts ("This is the *Basic OS* and I want to tell you the changes ");
	puts ("in the version 1.2!\n");
	puts (" - Memory manager (allocates and frees pages).\n");
}
