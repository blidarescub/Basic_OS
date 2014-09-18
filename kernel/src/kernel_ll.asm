; +-------------------------+
; | Basic Operating System. |
; +-------------------------+
; The low-level part of the kernel.

bits 32

; The low-level kernel main.
global kernel_ll
kernel_ll:
	cli
	call load_gdt			; Load the GDT.

	extern kernel_main		; kernel.c
	call kernel_main

	ret

; Load the GDT.
global load_gdt
load_gdt:
	lgdt [gdt.ptr]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	jmp 0x08:.done
	.done:
	ret

	; The GDT itself.
	gdt:
		.null:
			dd 0
			dd 0
		.code:
			dw 0xFFFF
			dw 0
			db 0
			db 0x9A
			db 0xCF
			db 0
		.data:
			dw 0xFFFF
			dw 0
			db 0
			db 0x92
			db 0xCF
			db 0
		.end:
		.ptr:
			dw gdt - .end - 1
			dd gdt

; Load the IDT.
global load_idt
load_idt:
	extern idt_ptr			; idt.c
	lidt [idt_ptr]
	sti
	ret

; Remap the PICs.
global remap_pics
remap_pics:
	mov ax, 0x11
	out 0x20, ax
	out 0xA0, ax

	mov ax, 0x20
	out 0x21, ax
	mov ax, 0x28
	out 0xA1, ax

	mov ax, 0x04
	out 0x21, ax
	mov ax, 0x02
	out 0xA1, ax

	mov ax, 0x01
	out 0x21, ax
	mov ax, 0x01
	out 0xA1, ax

	mov ax, 0xFD
	out 0x21, ax
	mov ax, 0xFF
	out 0xA1, ax

	ret
