#!/bin/bash

# This scripts creates a GRUB CD-ROM disk image.

PREFIX=$1
if [ "$1" = "" ]; then
	PREFIX="./"
fi

if [ -e ${PREFIX}disk/isofiles ]; then
	rm -r ${PREFIX}disk/isofiles || exit 1
fi

printf 'Creating isofiles... '
mkdir ${PREFIX}disk/isofiles || exit 1
echo 'Done.'

printf 'Creating directories... '
mkdir -p ${PREFIX}disk/isofiles/boot/grub || exit 1
echo 'Done.'

printf 'Copying the files... '
cp ${PREFIX}disk/grub.cfg ${PREFIX}disk/isofiles/boot/grub || exit 1
cp ${PREFIX}bin/kernel.bin ${PREFIX}disk/isofiles/boot || exit 1
echo 'Done.'

printf 'Creating a CD-ROM from isofiles... '
grub-mkrescue -o ${PREFIX}disk/myos.iso ${PREFIX}disk/isofiles || exit 1
echo 'Done.'
