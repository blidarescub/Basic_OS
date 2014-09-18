// Basic Operating System.
// The IDT.

#include <idt.h>
#include <isrs.h>
#include <screen.h>
#include <types.h>

idt_entry	idt[256];
idt_pointer	idt_ptr;

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

// Exception handler.
void exc_handler (regs_t *regs)
{
	const char *msg[32] =
	{
		"Divide By Zero",
		"Debug",
		"Non-maskable Interrupt",
		"Breakpoint",
		"Overflow",
		"Bound Range Exceeded",
		"Invalid Opcode",
		"Device Not Available",
		"Double Fault",
		"Coprocessor Segment Overrun",
		"Invalid TSS",
		"Segment Not Present",
		"Stack-Segment Fault",
		"General Protection Fault",
		"Page Fault",
		"Reserved",
		"x87 Floating-Point",
		"Alignment Check",
		"Machine Check",
		"SIMD Floating-Point",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Reserved",
		"Security",
		"Reserved",
	};

	if (regs->num <= 31)
	{
		init_screen ();
		clear_screen ();
		puts (msg[regs->num]);
		puts (" was occurred.");
		halt ();
	}
}