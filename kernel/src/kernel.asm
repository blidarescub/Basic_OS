; +-------------------------+
; | Basic Operating System. |
; +-------------------------+
; The low-level part of the kernel.

bits 32

; The low-level kernel main.
global kernel_ll
kernel_ll:
	cli				; Disable the interrupts.
	call load_gdt			; Load the GDT.

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
