// Basic Operating System.
// Exceptions and IRQs handlers.

#include <handlers.h>
#include <screen.h>
#include <string.h>
#include <inoutb.h>
#include <types.h>

// IRQ handlers.
void *irq_handlers[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

// Exceptions handler.
void excs_handler (regs_exc_t *regs)
{
    const char *msg[32] =
    {
        "Divide By Zero",
        "Debug",
        "Non-maskable Interrupt",
        "Breakpoint",
        "Overflow",
        "Bound Range Exceeded",
        "Invalid Opcode",
        "Device Not Available",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Invalid TSS",
        "Segment Not Present",
        "Stack-Segment Fault",
        "General Protection Fault",
        "Page Fault",
        "Reserved",
        "x87 Floating-Point",
        "Alignment Check",
        "Machine Check",
        "SIMD Floating-Point",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Security",
        "Reserved",
    };

    puts (msg[regs->num]);
    puts (" Exception was occurred.\n");

    if (regs->num == 14)
    {
        char str[32];
        puts ("Error code: ");
        puts (itoa (regs->err_code, str, 2));puts ("\n");
    }

    halt ();
}

// IRQs handler.
void irqs_handler (regs_irq_t *regs)
{
    // Get a handler.
    void (*handler) (regs_irq_t *) = irq_handlers[regs->num];

    // Is there a handler?
    if (handler)
        handler (regs); // If there is, call it.

    // Send EOI (End Of Interrupt) signal to the PIC(s).
    if (regs->num >= 8)
    {
        outb (0xA0, 0x20);
    }
    outb (0x20, 0x20);
}

// Set an IRQ handler.
void set_irq_handler (int irq_num, void (*handler) (regs_irq_t *))
{
    irq_handlers[irq_num] = handler;
}

// Unset an IRQ handler.
void unset_irq_handler (int irq_num)
{
    irq_handlers[irq_num] = 0;
}
