The goal.
=========

The goal of the **Basic OS** is to give the community a base for other OSes.

What is left?
=============

Here is a TODO list for the version **1.0**.

- [x] Basic files (`Makefile`, `linker.ld` and `start.asm`).
- [x] The GDT (`kernel_ll.asm`).
- [x] Calling the C function (from `kernel_ll.asm` to `kernel.c`).
- [x] The IDT (`idt.c`).
- [x] The ISRs for the Exceptions (`kernel_ll.asm`).
- [x] The ISRs for the two important IRQs.
	- [x] The Keyboard ISR and handler (`isrs.asm`, `idt.c` and `keyboard.c`.
	- [x] The PIT (timer) ISR and handler.
