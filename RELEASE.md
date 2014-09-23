Basic OS 1.0
============

The version 1.0 of the **Basic OS** was released!

This version contains:

- [x] GDT.
- [x] IDT.
- [x] ISRs for the Exceptions.
- [x] ISRs for two important IRQs:
  - [x] The Keyboard ISR and handler.
  - [x] The PIT (timer) ISR and handler.

The hierarchy of the directories:

```
- bin/			The compiled kernel (kernel.bin).
- disk/			The floppy image disks.
- kernel/		The sources of the OS and the scripts to build them.
  - src/		The source files (.c, .asm).
  - include/		The header files (.h).
```
