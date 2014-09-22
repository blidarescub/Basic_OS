Basic Operating System.
=======================

**Status:** in development.

This is the **Basic OS**. The purpose of this OS is shown in the title: &laquo;Create a base for operating systems&raquo;. 
It will contain the following things:

```
* GDT;
* IDT;
* ISRs for all Exceptions;
* ISRs for 2 important IRQs:
	* For the PIT (timer) — Count the time from the start of the OS.
	* For the Keyboard — Store last 10 pressed keys in the buffer and allow
	                     programs to access them.
* Memory allocation function.
```

Also read [GOAL_TODO.md](https://github.com/ExeTwezz/Basic_OS/blob/master/GOAL_TODO.md) to see the goal of the Basic OS and what things are implemented and what are not.

Building.
=========

To get and build the Basic OS, you need the following packages to be installed:

```
* git
* clang
* nasm
* binutils
```

You must have them to continue.

## Getting the Basic OS sources.

First of all, you need to download the sources:

```
SomeDir $ git clone https://github.com/exetwezz/Basic_OS
```

## Building the sources.

Run these commands to build the downloaded sources:

```
SomeDir $ cd Basic_OS
Basic_OS $ cd kernel
kernel $ make
```

Running.
========

To run the compiled Basic OS in the **Bochs**, type `./run.sh`.
To run it in the **QEMU**, type `./run.sh qemu`.

## Installing an emulator.

**Bochs:** `$ sudo apt-get install bochs bochs-sdl`<br>
**QEMU:** `$ sudo apt-get install qemu-system-i386`

Need help?
==========

If you're a beginner in the OS development, then you're not in the right place. You should read the tutorials first.
I recommend to begin at http://wiki.osdev.org/Tutorials.

If you need help with the Basic OS, you can [create an issue](https://github.com/ExeTwezz/Basic_OS/issues/new).

Authors.
========

Since it is only a base for other OSes, it is easy to write alone.

* Yuri Tretyakov ([@exetwezz](https://github.com/ExeTwezz))

License.
========

The sources of the Basic OS are published under the [MIT License](http://choosealicense.com/licenses/mit/).
