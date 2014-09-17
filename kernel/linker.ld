OUTPUT_ARCH ("i386");
OUTPUT_FORMAT ("binary");
ENTRY (entry);
phys = 0x00100000;

SECTIONS
{
	.text phys : AT (phys)
	{
		code_start = .;
		*(.text)
		*(.rodata)
		. = ALIGN (4096);
	}

	.data : AT (phys + (data_start - code_start))
	{
		data_start = .;
		*(.data)
		. = ALIGN (4096);
	}

	.bss : AT (phys + (bss_start - code_start))
	{
		bss_start = .;
		*(.bss)
		. = ALIGN (4096);
	}
	bss_end = .;
}
