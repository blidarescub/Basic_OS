// Basic Operating System.
// The IDT.

#ifndef IDT_H
#define IDT_H

#include <types.h>

typedef struct
{
	u16	routineAddr_low;
	u16	segSelector;
	u8	reserved;
	u8	type_and_attributes;
	u16	routineAddr_high;
} __attribute__ ((packed)) idt_entry;

typedef struct
{
	u16	size;
	u32	address;
} __attribute__ ((packed)) idt_pointer;

/* idt.c */
void setup_idt (void);
void set_idt_entry (int, u32);
void exc_handler (regs_t *);

/* kernel_ll.asm */
extern void load_idt (void);
extern void halt (void);

#endif /* !IDT_H */
