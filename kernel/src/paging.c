// Basic Operating System.
// Paging.

#include <paging.h>
#include <types.h>

// Initialize paging.
void init_paging (void)
{
	u32 *page_directory = (u32 *) 0x9C000;
	u32 *page_table = (u32 *) 0x9D000;

	// Fill in the Page Table: Map the first 4 MB of memory.
	int address = 0; // The physical address of a page.
	int i;
	for (i = 0; i < 1024; ++i)
	{
		page_table[i] = address | 3; // End with 011 (supervisor level,
		// read and write access, the page is present).
		address += 4096; // Next page.
	}

	// Fill in the Page Directory: Tell about the Page Table.
	page_directory[0] = (u32) page_table;
	page_directory[0] |= 3; // End with 011 (supervisor level,
	// read and write access, the page table is present).

	// Fill in the rest of the Page Directory.
	for (i = 1; i < 1024; ++i)
	{
		page_directory[i] = 0 | 2; // End with 010 (supervisor level,
		// read and write access, the page is NOT present).
	}

	// Load the Page Directory and enable paging!
	write_cr3 ((u32) page_directory); // Put the Page Directory address
	// into the CR3.
	write_cr0 ((u32) (read_cr0 () | 0x80000000)); // Set the Paging bit
	// (bit 31) of the CR0.
}
