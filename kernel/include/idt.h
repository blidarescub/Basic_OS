// Basic Operating System.
// The IDT.

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct
{
	uint16_t routineAddr_low;
	uint16_t segSelector;
	uint8_t  reserved;
	uint8_t  type_and_attributes;
	uint16_t routineAddr_high;
} __attribute__ ((packed)) idt_entry;

typedef struct
{
	uint16_t size;
	uint32_t address;
} __attribute__ ((packed)) idt_pointer;

/* idt.c */
void remap_pics (void);
void setup_idt (void);
void mask_irq (uint16_t);
void unmask_irq (uint16_t);
void set_idt_entry (uint32_t, uint32_t);

/* kernel_ll.asm */
extern void load_idt (void);
extern void halt (void);

#endif /* !IDT_H */
