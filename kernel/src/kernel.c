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
#include <memory.h>

/* Types. */
#include <stdint.h>

// The C kernel main.
void kernel_main (mb_info_t *mb_info)
{
    init_screen ();
    clear_screen ();

    setup_idt ();
    init_keyboard_handler ();
    init_timer_handler ();

    // Copy the memory map provided by GRUB.
    uint8_t mmap[mb_info->mmap_length];
    memcpy ((uint8_t *) &mmap, (uint8_t *) mb_info->mmap_addr,
            mb_info->mmap_length);
    // Note: we do this because the stack of free pages begins at 0x90000 and
    // ends at 0x0, but the memory map provided by bootloader is located below
    // 1 MB, usually at 0x100A8. So, to prevent overwriting the memory map
    // (and to be able to use it later) we copy it. `mmap' is the copy of it.

    // Descriptor of the memory map.
    mmap_t mmap_desc;
    mmap_desc.addr = (uint32_t) &mmap;
    mmap_desc.length = mb_info->mmap_length;

    init_paging ();
    init_mm (mb_info, mmap_desc);
}
