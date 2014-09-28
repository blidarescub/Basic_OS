// Basic Operating System.
// The Memory Manager.

#include <mm.h>
#include <screen.h>
#include <string.h>
#include <types.h>

// The bitmap.
u32 mm_bitmap[32768];

// Initialize the MM.
void init_mm (void)
{
	// Do nothing lol.
}

// Allocate page(s).
void *mm_alloc_pages (int count)
{
	if (count < 0)
	{
		puts ("Memory Manager: Error: Trying to allocate less than 0 pages.");
		halt ();
	}

	int f_superpage = 0;
	int f_page = 0;
	int f_size = 0;

	int i;
	for (i = 0; i < 1; ++i) // Check only ONE superpage, since we've only
	// one Page Table (superpage = page table = 4 MB).
	{
		// Is the whole superpage used?
		if (mm_bitmap[i] == 0xFFFFFFFF)
		{
			continue; // Next superpage.
		}
		// Or it's free?
		else if (mm_bitmap[i] == 0x00000000)
		{
			if (f_size == 0)
			{
				f_superpage = i;
				f_page = 0;
			}
			f_size += 32;

			while (f_size > count)
				--f_size;
		}
		// Some pages are free and some are used?
		else
		{
			int j;
			for (j = 0; j < 32; ++j)
			{
				if (!(mm_bitmap[i] & (1 << j)))
				{
					if (f_size == 0)
					{
						f_superpage = i;
						f_page = j;
					}
					if (f_size == count)
						break; // Done.
					++f_size;
				}
				else
				{
					f_size = 0;
				}
			}
			// The above loop searches for a suitable sequence of
			// pages in the current superpage.
		}

		// Exit from the loop if enough pages have been found.
		if (f_size >= count)
			break;
	}

	// Not enough pages?
	if (f_size < count)
	{
		clear_screen ();
		puts ("Memory Manager: Error: Not enough pages left.");
		halt ();
	}

	char str[32];
	puts ("mm_alloc(): success.\n");
	puts ("f_size = ");
	puts (itoa (f_size, str, 10));
	puts ("\nf_superpage = ");
	puts (itoa (f_superpage, str, 10));
	puts ("\nf_page = ");
	puts (itoa (f_page, str, 10));
	halt ();
}

// Mark page as used.
void mm_mark_as_used (int page)
{
	int mb = page >> 5;
	int superpage = mb / 4;

	mm_bitmap[superpage] |= (1 << page);
}
