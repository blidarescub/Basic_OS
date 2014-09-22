#!/bin/bash

# Usage: ./run.sh [emulator]
# Emulators:
#   bochs
#   qemu
#   .. or another (if you add the code to run it).
# Examples:
#  ./run.sh		# Equal to ./run.sh bochs
#  ./run.sh qemu

default=bochs
current=

if [ "$1" = "" ]; then
	current=$default
else
	current=$1
fi

if [ "$current" = "bochs" ]; then
	bochs -f bochs_config.txt
elif [ "$current" = "qemu" ]; then
	qemu-system-i386 -fda disk/myos.img -boot a
fi
