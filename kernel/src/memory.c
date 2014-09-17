// Basic Operating System.
// Functions for working with the memory.

#include <memory.h>
#include <types.h>

// Copy {count} bytes from the {src} to the {dest}.
u8 *memcpy (u8 *dest, u8 *src, int count)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		dest[i] = src[i];
	}
	return dest;
}

// Set {count} bytes at the {dest} to the {val}.
u8 *memset (u8 *dest, u8 val, int count)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		dest[i] = val;
	}
	return dest;
}

// Set {count} words at the {dest} to the {val}.
u16 *memsetw (u16 *dest, u16 val, int count)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		dest[i] = val;
	}
	return dest;
}
