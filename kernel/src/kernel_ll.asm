; +-------------------------+
; | Basic Operating System. |
; +-------------------------+
; The low-level part of the kernel.

bits 32

; The low-level kernel main.
global kernel_ll
kernel_ll:
    cli
    call load_gdt				; Load the GDT.

    push ebx

    extern kernel_main			; kernel.c
    call kernel_main

    call halt					; Halt the CPU.
    ret

; Halt the CPU.
global halt
halt:
    hlt
    jmp halt

; Load the GDT.
global load_gdt
load_gdt:
    lgdt [gdt.ptr]
    call update_segregs
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

; Update segment registers.
global update_segregs
update_segregs:
    push ax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:.cs
    .cs:
    pop ax
    ret

; Load the IDT.
global load_idt
load_idt:
    extern idt_ptr				; idt.c
    lidt [idt_ptr]
    sti
    ret

; Read the CR2 register.
global read_cr2
read_cr2:
    mov eax, cr2
    retn
