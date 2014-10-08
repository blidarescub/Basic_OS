#!/bin/bash

# This script runs the specified (and supported) emulator.
# "Supported" means that the code to start that emulator is written here.

DEFAULT=qemu                        # Default emulator/VM.
CURRENT=$DEFAULT                    # Emulator/VM to run.

VBOX_VM_NAME="Basic OS"             # Place here the name of the virtual
                                    # machine in which you want to run the
                                    # Basic OS.

# Did the user specify what emulator/VM to start?
if [ ! "$1" = '' ]; then
	CURRENT=$1	            		# Select the specified emulator/VM.
fi

# Run the emulator/VM.
if [ "$CURRENT" = bochs ]; then		# User wants to run the OS in Bochs?

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

elif [ "$CURRENT" = qemu ]; then	# User wants to run the OS in QEMU?

	# Is it installed?
	if test $CURRENT; then
		# Yes.

		qemu-system-i386\
			-cdrom disk/myos.iso\
			-boot cd\
			-rtc base=localtime,clock=host,driftfix=slew\
            -curses
	else
		# No.
		echo -n "The \`qemu-system-i386\` package is not installed "
		echo "on your system."
		echo "Run the following command to install it:"
		echo "$ sudo apt-get install qemu-system"
		exit 1
	fi

elif [ "$CURRENT" = virtualbox ]; then	# User wants to run the OS in VBox?

	vm_name=$VBOX_VM_NAME

	# Is it installed?
	if test $CURRENT; then
		# Yes.
		if ! virtualbox --startvm "$vm_name"; then
			echo "The \`virtualbox\` command has returned 1."
			echo -n "Maybe you didn't specify the name of the"
			echo "virtual machine in which you want to run"
			echo "the Basic OS:"
			echo -n " > open the file 'run.sh' and set the "
			echo "VBOX_VM_NAME variable."
		fi
	else
		# No.
		echo -n "The \`virtualbox\` package is not installed on your"
		echo "system."
		echo "Run the following command to install it:"
		echo "$ sudo apt-get install virtualbox"
	fi

fi
