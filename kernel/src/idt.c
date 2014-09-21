// Basic Operating System.
// The IDT.

#include <idt.h>
#include <isrs.h>
#include <screen.h>
#include <inoutb.h>
#include <types.h>

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

	outb (0x21, 0x00);
	outb (0xA1, 0x00);
}

// Initialize and load the IDT.
void setup_idt (void)
{
	idt_ptr.size = (sizeof (idt_entry) * 256) - 1;
	idt_ptr.address = (u32) &idt;

	set_idt_entry (0, (u32) &exc0);
	set_idt_entry (1, (u32) &exc1);
	set_idt_entry (2, (u32) &exc2);
	set_idt_entry (3, (u32) &exc3);
	set_idt_entry (4, (u32) &exc4);
	set_idt_entry (5, (u32) &exc5);
	set_idt_entry (6, (u32) &exc6);
	set_idt_entry (7, (u32) &exc7);
	set_idt_entry (8, (u32) &exc8);
	set_idt_entry (9, (u32) &exc9);
	set_idt_entry (10, (u32) &exc10);
	set_idt_entry (11, (u32) &exc11);
	set_idt_entry (12, (u32) &exc12);
	set_idt_entry (13, (u32) &exc13);
	set_idt_entry (14, (u32) &exc14);
	set_idt_entry (15, (u32) &exc15);
	set_idt_entry (16, (u32) &exc16);
	set_idt_entry (17, (u32) &exc17);
	set_idt_entry (18, (u32) &exc18);
	set_idt_entry (19, (u32) &exc19);
	set_idt_entry (20, (u32) &exc20);
	set_idt_entry (21, (u32) &exc21);
	set_idt_entry (22, (u32) &exc22);
	set_idt_entry (23, (u32) &exc23);
	set_idt_entry (24, (u32) &exc24);
	set_idt_entry (25, (u32) &exc25);
	set_idt_entry (26, (u32) &exc26);
	set_idt_entry (27, (u32) &exc27);
	set_idt_entry (28, (u32) &exc28);
	set_idt_entry (29, (u32) &exc29);
	set_idt_entry (30, (u32) &exc30);
	set_idt_entry (31, (u32) &exc31);

	remap_pics ();
	set_idt_entry (32, (u32) &irq0);
	set_idt_entry (33, (u32) &irq1);
	set_idt_entry (34, (u32) &irq2);
	set_idt_entry (35, (u32) &irq3);
	set_idt_entry (36, (u32) &irq4);
	set_idt_entry (37, (u32) &irq5);
	set_idt_entry (38, (u32) &irq6);
	set_idt_entry (39, (u32) &irq7);
	set_idt_entry (40, (u32) &irq8);
	set_idt_entry (41, (u32) &irq9);
	set_idt_entry (42, (u32) &irq10);
	set_idt_entry (43, (u32) &irq11);
	set_idt_entry (44, (u32) &irq12);
	set_idt_entry (45, (u32) &irq13);
	set_idt_entry (46, (u32) &irq14);
	set_idt_entry (47, (u32) &irq15);

	load_idt ();
}

// Change an IDT entry.
void set_idt_entry (int num, u32 routineAddr)
{
	idt[num].routineAddr_low = routineAddr & 0xFFFF;
	idt[num].segSelector = 0x08;
	idt[num].reserved = 0;
	idt[num].type_and_attributes = 0x8E;
	idt[num].routineAddr_high = (routineAddr >> 16) & 0xFFFF;
}
