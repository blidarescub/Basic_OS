// Basic Operating System.
// Exceptions and IRQs handlers.

#include <handlers.h>
#include <screen.h>
#include <string.h>
#include <mm.h>
#include <paging.h>
#include <inoutb.h>
#include <stdint.h>
#include <structs.h>

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

    if (regs->num == 14) // Page Fault?
    {
        // Is the page table not present?
        if (!(regs->err_code & 1))
        {
            // Yeah, create the needed page table.

            // The CR2 register holds the virtual address that caused the page
            // fault.
            uint32_t vaddr = read_cr2 ();

            // Get the page table that covers the virtual address `vaddr'.
            uint32_t pt = vaddr >> 22;

            // Create the needed page table.
            create_page_table (pt);

            // Cause an update of the TLB.
            write_cr3 (read_cr3 ());
        }
        else
        {
            puts ("Page Fault Exception was occurred.\n");
            halt ();
        }
    }
    else
    {
        puts (msg[regs->num]);
        puts (" Exception was occurred.\n");
        halt ();
    }
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
void set_irq_handler (uint32_t irq_num, void (*handler) (regs_irq_t *))
{
    irq_handlers[irq_num] = handler;
}

// Unset an IRQ handler.
void unset_irq_handler (uint32_t irq_num)
{
    irq_handlers[irq_num] = 0;
}
