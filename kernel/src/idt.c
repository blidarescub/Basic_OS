// Basic Operating System.
// The IDT.

#include <idt.h>
#include <isrs.h>
#include <screen.h>
#include <inoutb.h>
#include <stdint.h>

idt_entry	idt[256];
idt_pointer	idt_ptr;

// Remap the PICs.
void remap_pics (void)
{
    outb (0x20, 0x11);
    outb (0xA0, 0x11);

    outb (0x21, 0x20);
    outb (0xA1, 0x28);

    outb (0x21, 0x04);
    outb (0xA1, 0x02);

    outb (0x21, 0x01);
    outb (0xA1, 0x01);

    outb (0x21, 0xFF);
    outb (0xA1, 0xFF);
}

// Initialize and load the IDT.
void setup_idt (void)
{
    idt_ptr.size = (sizeof (idt_entry) * 256) - 1;
    idt_ptr.address = (uint32_t) &idt;

    set_idt_entry (0, (uint32_t) &exc0);
    set_idt_entry (1, (uint32_t) &exc1);
    set_idt_entry (2, (uint32_t) &exc2);
    set_idt_entry (3, (uint32_t) &exc3);
    set_idt_entry (4, (uint32_t) &exc4);
    set_idt_entry (5, (uint32_t) &exc5);
    set_idt_entry (6, (uint32_t) &exc6);
    set_idt_entry (7, (uint32_t) &exc7);
    set_idt_entry (8, (uint32_t) &exc8);
    set_idt_entry (9, (uint32_t) &exc9);
    set_idt_entry (10, (uint32_t) &exc10);
    set_idt_entry (11, (uint32_t) &exc11);
    set_idt_entry (12, (uint32_t) &exc12);
    set_idt_entry (13, (uint32_t) &exc13);
    set_idt_entry (14, (uint32_t) &exc14);
    set_idt_entry (15, (uint32_t) &exc15);
    set_idt_entry (16, (uint32_t) &exc16);
    set_idt_entry (17, (uint32_t) &exc17);
    set_idt_entry (18, (uint32_t) &exc18);
    set_idt_entry (19, (uint32_t) &exc19);
    set_idt_entry (20, (uint32_t) &exc20);
    set_idt_entry (21, (uint32_t) &exc21);
    set_idt_entry (22, (uint32_t) &exc22);
    set_idt_entry (23, (uint32_t) &exc23);
    set_idt_entry (24, (uint32_t) &exc24);
    set_idt_entry (25, (uint32_t) &exc25);
    set_idt_entry (26, (uint32_t) &exc26);
    set_idt_entry (27, (uint32_t) &exc27);
    set_idt_entry (28, (uint32_t) &exc28);
    set_idt_entry (29, (uint32_t) &exc29);
    set_idt_entry (30, (uint32_t) &exc30);
    set_idt_entry (31, (uint32_t) &exc31);

    remap_pics ();
    set_idt_entry (32, (uint32_t) &irq0);
    set_idt_entry (33, (uint32_t) &irq1);
    set_idt_entry (34, (uint32_t) &irq2);
    set_idt_entry (35, (uint32_t) &irq3);
    set_idt_entry (36, (uint32_t) &irq4);
    set_idt_entry (37, (uint32_t) &irq5);
    set_idt_entry (38, (uint32_t) &irq6);
    set_idt_entry (39, (uint32_t) &irq7);
    set_idt_entry (40, (uint32_t) &irq8);
    set_idt_entry (41, (uint32_t) &irq9);
    set_idt_entry (42, (uint32_t) &irq10);
    set_idt_entry (43, (uint32_t) &irq11);
    set_idt_entry (44, (uint32_t) &irq12);
    set_idt_entry (45, (uint32_t) &irq13);
    set_idt_entry (46, (uint32_t) &irq14);
    set_idt_entry (47, (uint32_t) &irq15);

    load_idt ();
}

// Mask an IRQ.
void mask_irq (uint16_t num)
{
    uint16_t port;
    uint8_t value;

    // Is this a Slave IRQ?
    if (num >= 8)
    {
        port = 0xA1;
        num -= 8;
    }
    else // No, Master?
    {
        port = 0x21;
    }

    value = inb (port) | (1 << num);
    outb (port, value);
}

// Unmask an IRQ.
void unmask_irq (uint16_t num)
{
    uint16_t port;
    uint8_t value;

    // Is this a Slave IRQ?
    if (num >= 8)
    {
        port = 0xA1;
        num -= 8;
    }
    else // No, Master?
    {
        port = 0x21;
    }

    value = inb (port) & ~(1 << num);
    outb (port, value);
}

// Change an IDT entry.
void set_idt_entry (uint32_t num, uint32_t routineAddr)
{
    idt[num].routineAddr_low = routineAddr & 0xFFFF;
    idt[num].segSelector = 0x08;
    idt[num].reserved = 0;
    idt[num].type_and_attributes = 0x8E;
    idt[num].routineAddr_high = (routineAddr >> 16) & 0xFFFF;
}
