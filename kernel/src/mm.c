// Basic Operating System.
// Memory Manager.

#include <mm.h>
#include <screen.h>
#include <string.h>
#include <types.h>
#include <stdint.h>

// The stack (the stack of free physical pages) pointer.
uint32_t *stack_ptr;
uint32_t *initial_stack_ptr;

// Map a virtual page to a physical one.
int map_page (uint32_t virtual, uint32_t physical)
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
    uint32_t *page_dir_addr = (uint32_t *) read_cr3 ();
    uint32_t *page_dir_entry_addr = page_dir_addr + (virtual >> 22);

    // Calculate the address of a page table that contains an entry for the
    // specified virtual page.
    uint32_t *page_table_addr = (uint32_t *) (*page_dir_entry_addr >> 12 << 12);

    // Is the page table not present?
    if ((uint32_t) *page_table_addr == 0)
    {
        // TODO: Create a new page table, create an entry in the page
        // directory for it (also call invlpg()), and something else.
        puts ("The page table is not present.");
        halt ();
    }

    // Calculate the address of that entry.
    uint32_t *page_table_entry_addr = page_table_addr + ((virtual >> 12) & 0x3FF);
    const uint32_t page_table_entry = *page_table_entry_addr; // Just a copy.

    // Change the page table entry.
    *page_table_entry_addr = (uint32_t) (physical | (page_table_entry & 0xFFF));

    // Remove the page table from the TLB.
    invlpg (virtual);

    return MAP_SUCCESS;
}

// Map virtual pages to physical ones.
int map_pages (uint32_t virtual, uint32_t physical, size_t count)
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
void push_physical_page (uint32_t address)
{
    stack_ptr -= 4;
    *stack_ptr = address;
}

// Pop an address of the free physical page from the stack.
uint32_t pop_physical_page (void)
{
    if (stack_ptr == initial_stack_ptr)
    {
        puts ("No free physical pages left.\n");
        puts ("Halting.");
        halt ();
    }
    uint32_t address = *stack_ptr;
    stack_ptr += 4;

    return address;
}

// Initialize the memory manager.
void init_mm (mb_info_t *mb_info)
{
    /*int physical_memory_size = mb_info->mem_upper;*/ // not used
    /*int lower_memory_size = mb_info->mem_lower * 1024;*/ // not used

    // Is there a memory map provided by bootloader?
    if (!(mb_info->flags & 0x40)) // 6th bit not set?
    {
        puts ("Sorry, but the bootloader didn't provide the kernel with a");
        puts (" memory map.\n");
        puts ("Halting.");
        halt ();
    }

    char str[32];
    puts ("mmap_addr = 0x");
    puts (itoa (mb_info->mmap_addr, str, 16));
    puts (", mmap_length = 0x");
    puts (itoa (mb_info->mmap_length, str, 16));
    puts ("\n");

    // We need 128 KB of RAM to store the stack of free pages.
    // Since we consider only low 32 bits of addresses below, the maximum
    // value of free physical memory is 4 GB, or 1024*1024 pages.
    stack_ptr = (uint32_t *) 0x20000;

    // Loop through the memory map and print all the regions.
    uint32_t i; // Current entry of the memory map.
    i = mb_info->mmap_addr;
    while (i < (mb_info->mmap_addr + mb_info->mmap_length))
    {
        uint32_t *size = (uint32_t *) i; // Size of the entry.
        uint32_t *base_addr_low = (uint32_t *) (i + 4); // Bits 0..31 of the
        // start of the region.
//      uint32_t *base_addr_high = (uint32_t *) (i + 8); // Bits 32..63 of the
        // start of the region.
        uint32_t *length_low = (uint32_t *) (i + 12); // Bits 0..31 of the
        // length of the region.
//      uint32_t *length_high = (uint32_t *) (i + 16); // Bits 32..63 of the
        // length of the region.
        uint32_t *type = (uint32_t *) (i + 20); // Type of the region.

        puts (" size = 0x");
        puts (itoa (*size, str, 16));
        puts (", start = 0x");
        puts (itoa (*base_addr_low, str, 16));
        puts (", end = 0x");
        puts (itoa (*base_addr_low + *length_low, str, 16));
        puts (", type = ");
        if (*type == 1) // Free?
        {
            puts ("free");
            // Loop through the region and push addresses of pages onto the
            // stack.
            int j;
            for (j = *base_addr_low; j < (*base_addr_low + *length_low);
                    j += 4096)
            {
                push_physical_page (j);
            }
        }
        else
            puts ("reserved");
        puts ("\n");

        i += *size + 4; // +4 since the `size' field is at offset 0, not -4.
    }
}

// Allocate virtual pages.
int alloc_pages (void *start_at, size_t count)
{
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
        invlpg ((uint32_t) i);
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
        invlpg ((uint32_t) i);
    }

    return FREE_SUCCESS;
}

// Remove a page from the TLB (Translation Lookaside Buffer).
inline void invlpg (uint32_t page_addr)
{
    asm volatile ("invlpg (%0)" : : "b" (page_addr) : "memory");
}
