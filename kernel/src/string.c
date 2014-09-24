// Basic Operating Sytsem.
// Functions for working with strings.

#include <string.h>

// Convert a number to a string.
char *itoa (int number, char *mem, int base)
{
	char *rc;
	char *ptr;
	char *low;

	// Check for supported base.
	if (base < 2 || base > 36)
	{
		*mem = '\0';
		return mem;
	}

	rc = ptr = mem;

	// Set '-' for negative decimals.
	if (number < 0 && base == 10)
	{
		*ptr++ = '-';
	}

	// Remember where the number starts.
	low = ptr;

	// The actual conversion.
	do
	{
		// Modulo is negative for negative number. This trick makes
		// abs() unnecessary.
		*ptr++ = "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + number % base];
		number /= base;
	} while (number);

	// Terminate the string.
	*ptr-- = '\0';

	// Invert the numbers.
	while (low < ptr)
	{
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}

	return rc;
}
