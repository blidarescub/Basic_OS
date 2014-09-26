; +-------------------------+
; | Basic Operating System. |
; +-------------------------+
; Auxiliary functions for enabling paging.

bits 32

; Read the CR0 register.
global read_cr0
read_cr0:
	mov eax, cr0
	retn

; Write the CR0 register.
global write_cr0
write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0, eax
	pop ebp
	retn

; Read the CR3 register.
global read_cr3
read_cr3:
	mov eax, cr3
	retn

; Write the CR3 register.
global write_cr3
write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	retn
