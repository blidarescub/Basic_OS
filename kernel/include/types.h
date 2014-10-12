// Basic Operating System.
// Definitions of basic types.

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

// Registers pushed in an Exception IRQ.
typedef struct
{
	u32 gs, fs, es, ds;
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32 num, err_code;
	u32 eip, cs, eflags, useresp, ss;
} __attribute__ ((packed)) regs_exc_t;

// Registers pushed in an IRQ ISR.
typedef struct
{
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32 num;
	u32 eip, cs, eflags, useresp, ss;
} __attribute__ ((packed)) regs_irq_t;

// Registers pushed in IRQ0.
typedef struct
{
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 gs, fs, es, ds;
    u32 eip, cs, eflags, useresp, ss;
} __attribute__ ((packed)) regs_irq0_t;

// Multiboot information structure.
typedef struct
{
	uint32_t flags;

	uint32_t mem_lower;
	uint32_t mem_upper;

	uint32_t boot_device;

	uint32_t cmdline;

	uint32_t mods_count;
	uint32_t mods_addr;

	uint32_t syms1;
	uint32_t syms2;
	uint32_t syms3;
	uint32_t syms4;

	uint32_t mmap_length;
	uint32_t mmap_addr;

	uint32_t drives_length;
	uint32_t drives_addr;

	uint32_t config_table;

	uint32_t bootloader_name;

	uint32_t apm_table;

	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint32_t vbe_mode;
	uint32_t vbe_interface_seg;
	uint32_t vbe_interface_off;
	uint32_t vbe_interface_len;
} __attribute__ ((packed)) mb_info_t;

#endif /* !TYPES_H */
