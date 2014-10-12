// Basic Operating System.
// in() and outb().

#include <stdint.h>

// Get a byte from the port.
uint8_t inb (uint16_t port)
{
    uint8_t rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "Nd" (port));
    return rv;
}

// Send the byte to the port.
void outb (uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a" (val), "Nd" (port));
}
