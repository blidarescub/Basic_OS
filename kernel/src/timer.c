// Basic Operating System.
// The PIT (timer).

#include <timer.h>
#include <handlers.h>
#include <inoutb.h>

#include <screen.h>

// Time from the start of the OS.
int timer_ticks;
int timer_seconds;

// Set the timer handler.
void init_timer_handler (void)
{
	set_irq_handler (0, timer_handler);

	// Set the timer phase.
	int divisor = 1193180 / 100;
	outb (0x43, 0x36);
	outb (0x40, divisor & 0xFF);
	outb (0x40, (divisor >> 8) & 0xFF);
}

// The timer handler.
void timer_handler (regs_irq_t *regs)
{
	++timer_ticks;
	if (timer_ticks % 1000 == 0)
	{
		++timer_seconds;
		puts ("One second was passed.\n");
	}

}
