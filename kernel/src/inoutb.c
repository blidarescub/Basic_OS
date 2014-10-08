// Basic Operating System.
// in() and outb().

#include <types.h>

// Get a byte from the port.
u8 inb (u16 port)
{
    u8 rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "Nd" (port));
    return rv;
}

// Send the byte to the port.
void outb (u16 port, u8 val)
{
    asm volatile ("outb %0, %1" : : "a" (val), "Nd" (port));
}
