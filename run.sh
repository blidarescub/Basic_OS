#!/bin/bash

# This script runs the specified (and supported) emulator.
# "Supported" means that the code to start that emulator is written here.

DEFAULT=bochs				# Default emulator.
CURRENT=$DEFAULT			# Emulator to run.

# Did the user specify what emulator to start?
if [ ! "$1" = '' ]; then
	CURRENT=$1			# Select the specified emulator.
fi

# Run the emulator.
if [ "$CURRENT" = bochs ]; then		# User wants to run in the Bochs?

	# Is it installed?
	if test $CURRENT; then
		# Yes.
		bochs -f bochs_config.txt
	else
		# No.
		echo "The \`bochs' package is not installed on your system."
		echo -n "Visit http://exetwezz.8nio.com/ and read the tutorial"
		echo " how to compile Bochs"
		echo "under Ubuntu."
		exit 1
	fi

elif [ "$CURRENT" = qemu ]; then	# User wants to run in the QEMU?

	# Is it installed?
	if test $CURRENT; then
		# Yes.
		qemu-system-i386\
			-cdrom disk/myos.iso\
			-boot cd\
			-rtc base=localtime,clock=host,driftfix=slew
	else
		# No.
		echo -n "The \`qemu-system-i386\` package is not installed "
		echo "on your system."
		echo "Run the following command to install it:"
		echo "$ sudo apt-get install qemu-system"
	fi

fi
