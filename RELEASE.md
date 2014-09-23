Basic OS 1.0.1
==============

This is a bugfix for the version **1.0**.

The bug was that the Bochs's PIT worked 10 times faster than the QEMU's PIT (as well as others').
The solution was to edit the Bochs configuration file and add `clock: sync=realtime` (commit: [97d359b](https://github.com/ExeTwezz/Basic_OS/commit/97d359b6fcb223b61cb264d927e520557ca7a137)).
