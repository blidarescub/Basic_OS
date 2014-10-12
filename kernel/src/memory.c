// Basic Operating System.
// Functions for working with the memory.

#include <memory.h>
#include <stdint.h>

// Copy {count} bytes from the {src} to the {dest}.
uint8_t *memcpy (uint8_t *dest, uint8_t *src, int count)
{
    int i;
    for (i = 0; i < count; ++i)
    {
        dest[i] = src[i];
    }
    return dest;
}

// Set {count} bytes at the {dest} to the {val}.
uint8_t *memset (uint8_t *dest, uint8_t val, int count)
{
    int i;
    for (i = 0; i < count; ++i)
    {
        dest[i] = val;
    }
    return dest;
}

// Set {count} words at the {dest} to the {val}.
uint16_t *memsetw (uint16_t *dest, uint16_t val, int count)
{
    int i;
    for (i = 0; i < count; ++i)
    {
        dest[i] = val;
    }
    return dest;
}
