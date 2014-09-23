Basic Operating System.
=======================

**Status:** 1.1 in development.<br>
**Version:** 1.0.1.

This is the **Basic OS**. The purpose of this OS is shown in the title: &laquo;Create a base for operating systems&raquo;. 
It will contain the following things:

```
* GDT.
* IDT.
* Exceptions handler, IRQs handler.
* Keyboard handler.
* PIT (timer) handler.
* Memory allocations.
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

Run in the Bochs: `$ ./run.sh` or `$ ./run.sh bochs`
Run in the QEMU: `$ ./run.sh qemu`

## Installing an emulator.

### Bochs.

```
$ sudo apt-get install bochs bochs-sdl
```

### QEMU.

```
$ sudo apt-get install qemu-system-i386
```

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
