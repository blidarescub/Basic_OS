Basic Operating System.
=======================

**Status:** 1.1 in development.<br>
**Version:** 1.0.1 (http://semver.org/).

This is the **Basic OS**. The goal of the OS is to show programmers what does
a simple OS look like (its features).

Also read [TODO.md](https://github.com/ExeTwezz/Basic_OS/blob/master/TODO.md)
to see the goal of the Basic OS and what things are implemented and what are
not yet.

Building.
=========

To get and build the Basic OS, you need the following packages to be installed:

```
* clang			# C compiler.
* nasm			# Netwide Assembler.
* binutils		# Contains `ld`, the linker.
* grub2			# Contains `grub-mkrescue`, an utility that creates GRUB .iso image.
* xorriso		# Needed for `grub-mkrescue`.
```

You must have them to continue.

## Getting the Basic OS sources.

Then you need to download the sources by downloading the
[latest release](https://github.com/ExeTwezz/Basic_OS/releases/latest)
(select `.tar.gz`).

## Building the sources.

Run these commands to unarchive and build the OS:

```
SomeDir $ tar -xzvf DOWNLOADED_ARCHIVE.tar.gz
SomeDir $ mv Basic_OS* Basic_OS
SomeDir $ cd Basic_OS
Basic_OS $ cd kernel
kernel $ make
```

Running.
========

Run in the Bochs: `$ ./run.sh` or `$ ./run.sh bochs`.
Run in the QEMU: `$ ./run.sh qemu`.

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

If you're a beginner in the OS development, I don't recommend you to begin
here. You should read the tutorials first. I recommend to begin at
http://www.osdever.net/ and http://wiki.osdev.org/Tutorials.

If you need a help with the Basic OS, you can
[create an issue](https://github.com/ExeTwezz/Basic_OS/issues/new).

License.
========

The sources of the Basic OS are published under the
[MIT License](http://choosealicense.com/licenses/mit/).
