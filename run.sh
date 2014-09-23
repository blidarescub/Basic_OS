#!/bin/bash

DEFAULT="bochs"
CURRENT="$1"

if [ "$CURRENT" = "" ]; then
	CURRENT="$DEFAULT"
fi

if [ "$CURRENT" = "bochs" ]; then
	bochs -f bochs_config.txt
elif [ "$CURRENT" = "qemu" ]; then
	qemu-system-i386 -smp 1 -m 64 -fda disk/myos.img -boot a
fi
