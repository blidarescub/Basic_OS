; +-------------------------+
; | Basic Operating System. |
; +-------------------------+
; The ISRs.

bits 32

; idt.c
extern excs_handler
extern irqs_handler

; Define an ISR for an Exception without error code.
%macro ISR_EXC 1
    ; arg1 - Exception number.
    global exc%1
    exc%1:
        push byte 0				; Fake error code.
        push byte %1			; Exception number.
        pusha
        push ds
        push es
        push fs
        push gs

        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        mov eax, esp
        push eax				; An argument to the C function.
        mov eax, excs_handler
        call eax
        pop eax

        pop gs
        pop fs
        pop es
        pop ds
        popa
        add esp, 8				; Skip the two bytes pushed.
        iret
%endmacro

; Define an ISR for an Exception with error code.
%macro ISR_EXC_EC 1
    ; arg1 - Exception number.
    global exc%1
    exc%1:
        push byte %1			; Excetpion number.
        pusha
        push ds
        push es
        push fs
        push gs

        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        mov eax, esp
        push eax				; An argument to the C function.
        mov eax, excs_handler
        call eax
        pop eax

        pop gs
        pop fs
        pop es
        pop ds
        popa
        add esp, 8				; Skip the byte pushed and the error code.
        iret
%endmacro

; Define an ISR for an IRQ.
%macro ISR_IRQ 1
    ; arg1 - IRQ number.
    global irq%1
    irq%1:
        push byte %1			; IRQ number.
        pusha

        mov eax, esp
        push eax				; An argument to the C function.
        mov eax, irqs_handler
        call eax
        pop eax

        popa
        add esp, 4				; Skip the pushed IRQ number.
        iret
%endmacro

; The ISRs for the Exceptions.
ISR_EXC 0
ISR_EXC 1
ISR_EXC 2
ISR_EXC 3
ISR_EXC 4
ISR_EXC 5
ISR_EXC 6
ISR_EXC 7
ISR_EXC_EC 8
ISR_EXC 9
ISR_EXC_EC 10
ISR_EXC_EC 11
ISR_EXC_EC 12
ISR_EXC_EC 13
ISR_EXC_EC 14
ISR_EXC 15
ISR_EXC 16
ISR_EXC_EC 17
ISR_EXC 18
ISR_EXC 19
ISR_EXC 20
ISR_EXC 21
ISR_EXC 22
ISR_EXC 23
ISR_EXC 24
ISR_EXC 25
ISR_EXC 26
ISR_EXC 27
ISR_EXC 28
ISR_EXC 29
ISR_EXC_EC 30
ISR_EXC 31

; The ISRs for the IRQs.
ISR_IRQ 0
ISR_IRQ 1
ISR_IRQ 2
ISR_IRQ 3
ISR_IRQ 4
ISR_IRQ 5
ISR_IRQ 6
ISR_IRQ 7
ISR_IRQ 8
ISR_IRQ 9
ISR_IRQ 10
ISR_IRQ 11
ISR_IRQ 12
ISR_IRQ 13
ISR_IRQ 14
ISR_IRQ 15
