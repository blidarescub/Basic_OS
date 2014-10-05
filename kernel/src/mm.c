// Basic Operating System.
// Memory Manager.

#include <mm.h>
#include <screen.h>
#include <string.h>
#include <types.h>

// The stack (the stack of free physical pages) pointer.
int *stack_ptr;
int *initial_stack_ptr;

// Push an address of the free physical page onto the stack.
void push_physical_page (int address)
{
    stack_ptr -= 4;
    *stack_ptr = address;
}

// Pop an address of the free physical page from the stack.
int pop_physical_page (void)
{
    if (stack_ptr == initial_stack_ptr)
    {
        puts ("No free physical pages left.\n");
        puts ("Halting.");
        halt ();
    }
    int address = *stack_ptr;
    stack_ptr += 4;
    return address;
}

// Initialize the memory manager.
void init_mm (int physical_memory_size)
{
    puts ("Initializing the memory manager\n");
    int stack_size = 640;
    stack_ptr = (int *) 0x00000 + stack_size;
    initial_stack_ptr = stack_ptr;

    puts (" - Physical memory size: ");
    char str[32];
    puts (itoa (physical_memory_size / 1024 / 1024, str, 10));
    puts (" MB\n");
    puts (" - Stack of free pages starts at: 0x");
    puts (itoa ((int) stack_ptr, str, 16));
    puts ("\n");
    puts (" - Size of the stack: ");
    puts (itoa (stack_size, str, 10));
    puts (" B\n");

    puts (" - Physical pages from 0x0 to 0xA0000 are free\n");

    int i;
    for (i = 0x0; i < 0x90000; i += 4096)
    {
        push_physical_page (i);
    }
}

// Allocate virtual pages.
int alloc_pages (void *start_at, int count)
{
    if (count < 0)
    {
        return ALLOC_ZEROCOUNT;
    }

    // Get the address of the current (loaded) page directory.
    u32 cr3 = read_cr3 (); // It is stored in the CR3 register.
    u32 *page_dir = (u32 *) cr3;

    // Calculate the address of the needed page table.
    int page_dir_offset = (int) start_at >> 22; // The offset of the needed page table
    // in the page directory.
    u32 page_table = page_dir[page_dir_offset]; // Multiply the offset by 32
    // (element size) and add it to the page directory address.

    // Is the page table not present?
    if ((page_table & 1) == 0)
    {
        // TODO: Create a new page table and create an entry in the page
        // directory for it.
        puts ("The page table is not present.\n");
        halt ();
    }

    // Verify that the pages are free.
    int i;
    for (i = (int) start_at; i < (int) start_at + count * 4096; i += 4096)
    {
        // Determine a page directory and a page table for the page "page".
        u32 *page_dir_addr = (u32 *) (i >> 22); // Get the bits 22..31.
        u32 *pgtbl_entry_addr = (u32 *) (page_dir_addr + ((i >> 12) & 0x3FF));
        // Get the bits 12..21 and add them to the page directory address.

        // Is the page allocated?
        if (*pgtbl_entry_addr & 0x200)
        {
            return ALLOC_ALREADY;
        }
    }

    // Mark the pages as used if they're not used. If they're, return an error.
    for (i = (int) start_at; i < (int) start_at + count * 4096; i += 4096)
    {
        // Determine a page directory and a page table for the page "page".
        u32 *page_dir_addr = (u32 *) (i >> 22); // Get the bits 22..31.
        u32 *pgtbl_entry_addr = (u32 *) (page_dir_addr + ((i >> 12) & 0x3FF));
        // Get the bits 12..21 and add them to the page directory address.

        // The bits 9, 10, 11 of a page table entry are available.
        // In our OS, the bit 9 is a used bit,
        // the bit 10 is "block bit":
        //   0 means that the new block starts,
        //   1 means that the page is inside a block.
        *pgtbl_entry_addr |= 0x200; // 0x200 = the 9th bit

        if (i == (int) start_at) // The first allocated page?
        {
            // Set the 10th bit to 0 (a new block starts).
            *pgtbl_entry_addr &= ~(0x400); // 0x400 = the 10th bit
        }
        else
        {
            // Set the 10th bit to 1 (the page is inside of a block).
            *pgtbl_entry_addr |= 0x400; // 0x400 = the 10th bit
        }

        // Remove the page from the TLB (read: page tables cache).
        invlpg ((void *) i);
    }

    // Successfully allocated.
    return ALLOC_SUCCESS;
}

// Free virtual pages.
int free_pages (void *start_at)
{
    // Get the address of the current (loaded) page directory.
    u32 cr3 = read_cr3 (); // It is stored in the CR3 register.
    u32 *page_dir = (u32 *) cr3;

    // Calculate the address of the needed page table.
    int page_dir_offset = (int) start_at >> 22; // The offset of the needed page table
    // in the page directory.
    u32 page_table = page_dir[page_dir_offset]; // Multiply the offset by 32
    // (element size) and add it to the page directory address.

    // Is the page table not present?
    if ((page_table & 1) == 0)
    {
        // TODO: Create a new page table and create an entry in the page
        // directory for it.
        puts ("The page table is not present.\n");
        halt ();
    }

    // Determine the size of the block.
    int block_size = 0;
    int i;
    for (i = (int) start_at; ; i += 4096)
    {
        // Determine a page directory and a page table for the page "page".
        u32 *page_dir_addr = (u32 *) (i >> 22); // Get the bits 22..31.
        u32 *pgtbl_entry_addr = (u32 *) (page_dir_addr + ((i >> 12) & 0x3FF));
        // Get the bits 12..21 and add them to the page directory address.

        // The bits 9, 10, 11 of a page table entry are available.
        // In our OS, the bit 9 is a used bit,
        // the bit 10 is "block bit":
        //   0 means that the new block starts,
        //   1 means that the page is inside a block.
        if (!(*pgtbl_entry_addr & 0x400)) // 0x400 = the 10th bit
        {
            if (block_size == 0)
                ++block_size;
            else
                break;
        }
        else
        {
            ++block_size;
        }
    }

    /*
    puts ("block_size = ");
    char str[32];
    puts (itoa (block_size, str, 10));
    puts ("\n");
    halt ();
    */

    // Mark the pages as free.
    for (i = (int) start_at; i < (int) start_at + block_size * 4096; i += 4096)
    {
        // Determine a page directory and a page table for the page "page".
        u32 *page_dir_addr = (u32 *) (i >> 22); // Get the bits 22..31.
        u32 *pgtbl_entry_addr = (u32 *) (page_dir_addr + ((i >> 12) & 0x3FF));
        // Get the bits 12..21 and add them to the page directory address.

        // The bits 9, 10, 11 of a page table entry are available.
        // In our OS, the bit 9 is a used bit,
        // the bit 10 is "block bit":
        //   0 means that the new block starts,
        //   1 means that the page is inside a block.
        *pgtbl_entry_addr &= ~(0x200); // 0x200 = the 9th bit

        // Remove the page from the TLB (read: page tables cache).
        invlpg ((void *) i);
    }

    return FREE_SUCCESS;
}

// Remove a page from the TLB (Translation Lookaside Buffer).
inline void invlpg (void *m)
{
    asm volatile ("invlpg (%0)" : : "b" (m) : "memory");
}
