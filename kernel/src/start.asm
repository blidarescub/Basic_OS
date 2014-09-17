; +-------------------------+
; | Basic Opetating System. |
; +-------------------------+

bits 32

; The entry point.
global entry
entry:
	mov esp, stack
	jmp skip_header

; The multiboot header.
; ---------------------
align 4
header:
	ALIGN_MODULES	equ 1 << 0
	MEMORY_INFO	equ 1 << 1
	AOUT_KLUDGE	equ 1 << 16

	MAGIC		equ 0x1BADB002
	FLAGS		equ ALIGN_MODULES | MEMORY_INFO | AOUT_KLUDGE
	CHECKSUM	equ -(MAGIC + FLAGS)

	dd MAGIC
	dd FLAGS
	dd CHECKSUM

	extern code_start, bss_start, bss_end
	dd header
	dd code_start
	dd bss_start
	dd bss_end
	dd entry
;----------------------

skip_header:
	extern kernel_ll		; kernel.asm
	call kernel_ll

	mov byte [0xB8000], 'P'
	mov byte [0xB8001], 0x1B

; Halt the CPU.
global halt
halt:
	cli
	hlt
	jmp halt

; The stack.
section .bss
resb 8192
stack:
