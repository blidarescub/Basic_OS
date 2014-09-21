// Basic Operating System.
// Definitions of basic types.

#ifndef TYPES_H
#define TYPES_H

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

typedef struct
{
	u32 gs, fs, es, ds;
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32 num, err_code;
	u32 eip, cs, eflags, useresp, ss;
} __attribute__ ((packed)) regs_exc_t;

typedef struct
{
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32 num;
	u32 eip, cs, eflags, useresp, ss;
} __attribute__ ((packed)) regs_irq_t;

#endif /* !TYPES_H */
