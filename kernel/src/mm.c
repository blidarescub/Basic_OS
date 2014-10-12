// Basic Operating System.
// Memory Manager.

#include <mm.h>
#include <screen.h>
#include <string.h>
#include <types.h>

// The stack (the stack of free physical pages) pointer.
int *stack_ptr;
int *stack_ptr_limit;
int *initial_stack_ptr;

// Map a virtual page to a physical one.
int map_page (int virtual, int physical)
{
    // Are the addresses 4KB-aligned?
    if (virtual & 0xFFF)
    {
        // The virtual one is not aligned, align it.
        virtual &= 0xFFFFF000;
    }
    if (physical & 0xFFF)
    {
        // The physical one is not aligned, align it.
        physical &= 0xFFFFF000;
    }

    // Get the physical address of the current page directory.
    u32 *page_dir_addr = (u32 *) read_cr3 ();
    u32 *page_dir_entry_addr = page_dir_addr + (virtual >> 22);

    // Calculate the address of a page table that contains an entry for the
    // specified virtual page.
    u32 *page_table_addr = (u32 *) (*page_dir_entry_addr >> 12 << 12);

    // Is the page table not present?
    if ((int) *page_table_addr == 0)
    {
        // TODO: Create a new page table, create an entry in the page
        // directory for it (also call invlpg()), and something else.
        puts ("The page table is not present.");
        halt ();
    }

    // Calculate the address of that entry.
    u32 *page_table_entry_addr = page_table_addr + ((virtual >> 12) & 0x3FF);
    const u32 page_table_entry = *page_table_entry_addr; // Just a copy.

    // Change the page table entry.
    *page_table_entry_addr = (u32) (physical | (page_table_entry & 0xFFF));

    // Remove the page table from the TLB.
    invlpg ((void *) virtual);

    return MAP_SUCCESS;
}

// Map virtual pages to physical ones.
int map_pages (int virtual, int physical, int count)
{
    // Are the address 4KB-aligned?
    if (virtual & 0xFFF)
    {
        // The virtual one is not aligned, align it.
        virtual &= 0xFFFFF000;
    }
    if (physical & 0xFFF)
    {
        // The physical one is not aligned, align it.
        physical &= 0xFFFFF000;
    }

    // Map the pages separately.
    int i;
    for (i = 0; i < count; ++i)
    {
        map_page (virtual + count, physical + count);
    }

    return MAP_SUCCESS;
}

// Switch a page directory.
void switch_page_directory (void *addr)
{
    write_cr3 ((u32) addr);
}

// Create a page table.
u32 *create_page_table (int num)
{
    // `num` is the number of a new page table (counting from 0).
    // Examples:
    //   create_page_table (0);
    //     - Create a page table for pages 0x0 - 0x3FF000.
    //   create_page_table (1);
    //     - Create a page table for pages 0x400000 - 0x7FF000.

    // Get the physical address of the current page directory.
    int page_dir = read_cr3 ();

    if (num < 0)
    {
        return 0;
    }
    if (num > 1023)
    {
        // The maximum value of page tables in one page directory is 1024.
        return 0;
    }

    // Request a free physical page.
    u32 *ppage = (u32 *) pop_physical_page ();
    // The new page table will be located in this physical page.

    // Convert `num` to the address of the first page that will be pushed into
    // the first entry of the new page table.
    int first = num * 4194304;

    // Fill in the page table.
    int i;
    for (i = 0; i < 1024; ++i)
    {
        int page = first + (i * 4096);

        // Fill in the entry "i".
        ppage[i] = page | 3; // End with 011 (supervisor level, read and write
        // access, the page is present).
    }

    // Update the page directory entry.
    u32 *page_dir_ptr = (u32 *) page_dir;
    page_dir_ptr[num] = (u32) ppage | 3; // End with 011 (supervisor level,
    // read and write access, the page table is present).

    // Cause an update of the TLB.
    write_cr3 (page_dir);

    return (u32 *) ppage;
}

// Push an address of the free physical page onto the stack.
void push_physical_page (int address)
{
    if (stack_ptr == stack_ptr_limit)
    {
        puts ("Reached the limit of the stack of free pages.\n");
        puts ("Halting.");
        halt ();
    }

    stack_ptr -= 4;
    *stack_ptr = address;

    // Mark the page as free.
    free_pages ((void *) address);
    // Though it's a virtual memory manager function and it interacts with the
    // virtual address space, in our OS the virtual addresses of the kernel are
    // mapped to the same physical addresses, so don't worry about this call.
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

    // Mark the page as used.
    alloc_pages ((void *) address, 1);
    // Though it's a virtual memory manager function and it interacts with the
    // virtual address space, in our OS the virtual addresses of the kernel are
    // mapped to the same physical addresses, so don't worry about this call.

    return address;
}

// Initialize the memory manager.
void init_mm (mb_info_t *mb_info)
{
    /*int physical_memory_size = mb_info->mem_upper;*/ // not used
    /*int lower_memory_size = mb_info->mem_lower * 1024;*/ // not used

    stack_ptr = (int *) 0x3000;
    stack_ptr_limit = (int *)  0x2000; // At 0x1000 - 0x2000 is a page table.
    initial_stack_ptr = stack_ptr;

    int i;
    for (i = 0x3000; i < 0x0FF000; i += 4096)
    {
        // Push the address of the free physical page onto the stack of free
        // physical pages.
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
    int page_dir_offset = (int) start_at >> 22; // The offset of the needed page
    // table in the page directory.
    u32 page_table = page_dir[page_dir_offset]; // Multiply the offset by 32
    // (element size) and add it to the page directory address.

    if (0) page_table = 0; // dead code.

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

        // Remove the page from the TLB.
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

        // Remove the page from the TLB.
        invlpg ((void *) i);
    }

    return FREE_SUCCESS;
}

// Remove a page from the TLB (Translation Lookaside Buffer).
inline void invlpg (void *page_addr)
{
    asm volatile ("invlpg (%0)" : : "b" (page_addr) : "memory");
}
