// Basic Operating System.
// Definitions of basic types.

#ifndef TYPES_H
#define TYPES_H

#define NULL 0

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
	u32 flags;

	u32 mem_lower;
	u32 mem_upper;

	u32 boot_device;

	u32 cmdline;

	u32 mods_count;
	u32 mods_addr;

	u32 syms1;
	u32 syms2;
	u32 syms3;
	u32 syms4;

	u32 mmap_length;
	u32 mmap_addr;

	u32 drives_length;
	u32 drives_addr;

	u32 config_table;

	u32 bootloader_name;

	u32 apm_table;

	u32 vbe_control_info;
	u32 vbe_mode_info;
	u32 vbe_mode;
	u32 vbe_interface_seg;
	u32 vbe_interface_off;
	u32 vbe_interface_len;
} __attribute__ ((packed)) mb_info_t;

#endif /* !TYPES_H */
