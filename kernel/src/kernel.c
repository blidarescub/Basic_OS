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

    char str[32];
    int *memory_map = (int *) mb_info->mmap_addr;

    puts ("flags = 0x");
    puts (itoa (mb_info->flags, str, 16));
    puts ("\n");

    int *size = memory_map - 4;
    int *base_addr_low = memory_map;
    int *base_addr_high = memory_map + 4;
    int *length_low = memory_map + 8;
    int *length_high = memory_map + 12;
    int *type = memory_map + 16;

    puts ("-4  | size = ");
    puts (itoa (*size, str, 10));
    puts ("\n");
    puts (" 0  | base_addr_low = 0x");
    puts (itoa (*base_addr_low, str, 16));
    puts ("\n");
    puts (" 4  | base_addr_high = 0x");
    puts (itoa (*base_addr_high, str, 16));
    puts (" 8  | length_low = ");
    puts (itoa (*length_low, str, 10));
    puts ("\n");
    puts (" 12 | length_high = ");
    puts (itoa (*length_high, str, 10));
    puts ("\n");
    puts (" 16 | type = ");
    puts (itoa (*type, str, 10));
    puts ("\n");
}
