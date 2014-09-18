Basic Operating System
======================

**Status:** in development.

This is the **Basic OS**. The purpose of this OS is shown in the title: &laquo;Create a base for operating systems&raquo;. 
It will contain the following things:

	* GDT;
	* IDT;
	* ISRs for all Exceptions;
	* ISRs for all 2 important IRQs:
		* For the PIT (timer) — Count the time from the start of the OS.
		* For the Keyboard — Store last 10 pressed keys in the buffer and allow
		                     programs to access them.
	* Memory allocation function.

Need help?
==========

If you're a beginner in the OS development, then you're not in the right place. You should read the tutorials first.
I recommend to begin at http://wiki.osdev.org/Tutorials.

If you need help with the Basic OS, you can [create an issue](https://github.com/ExeTwezz/Basic_OS/issues/new).

Authors
=======

Since it is only a base for other OSes, it is easy to write alone.

* Yuri Tretyakov ([@exetwezz](https://github.com/ExeTwezz))

License
=======

The sources of the Basic OS are published under the [MIT License](http://choosealicense.com/licenses/mit/).
