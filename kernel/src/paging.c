// Basic Operating System.
// Paging.

#include <paging.h>
#include <types.h>

// Initialize paging.
void init_paging (void)
{
    u32 *page_directory = (u32 *) 0x9C000;
    u32 *page_table = (u32 *) 0x9D000;

    // Fill in the first page table.
    int address = 0; // The physical address of a page.
    int i;
    for (i = 0; i < 1024; ++i, address += 4096)
    {
        int page = address & ~(0xFFF);
        page_table[i] = page | 3; // End with 011 (supervisor level,
        // read and write access, the page is present).
    }

    // Fill in the page directory.
    page_directory[0] = (u32) page_table | 3; // End with 011 (supervisor level,
    // read and write access, the page table is present).

    // Fill in the rest of the page directory.
    for (i = 1; i < 1024; ++i)
    {
        page_directory[i] = 0;
    }

    // Load the page directory and enable paging!
    write_cr3 ((u32) page_directory); // Put the address of the page directory
    // into the CR3 register.
    write_cr0 ((u32) (read_cr0 () | 0x80000000)); // Set the Paging bit
    // (bit 31) in the CR0 register.

    // Update the segment registers.
    update_segregs ();
}
