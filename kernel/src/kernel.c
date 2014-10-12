// Basic Operating System.
// The C part of the kernel.

/* Output to the screen. */
#include <screen.h>
#include <string.h> // Not related, but is used to convert numbers and print
// them on the screen.

/* Interrupts. */
#include <idt.h>
#include <keyboard.h>
#include <timer.h>

/* Memory. */
#include <paging.h>
#include <mm.h>

/* Other stuff. */
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
    init_mm (mb_info);
}
