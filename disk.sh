#!/bin/bash

printf 'Requesting the root privileges... '
sudo echo 'Done.'

PREFIX=./

if [ ! "$1" = "" ]; then
	PREFIX="$1"
fi

if [ -e ${PREFIX}disk/myos.img ]; then
	rm ${PREFIX}disk/myos.img || exit 1
fi

if [ -e ${PREFIX}disk/myos ]; then
	rmdir ${PREFIX}disk/myos || exit 1
fi

printf 'Creating a temporary directory...'
mkdir ${PREFIX}disk/myos || exit 1
echo ' Done.'

printf 'Creating a disk image...'
cp ${PREFIX}disk/grub.img ${PREFIX}disk/myos.img || exit 1
echo ' Done.'

printf 'Mounting the image...'
sudo mount -t vfat ${PREFIX}disk/myos.img ${PREFIX}disk/myos || exit 1
echo ' Done.'

printf 'Copying the kernel...'
sudo cp ${PREFIX}bin/kernel.bin ${PREFIX}disk/myos/boot || exit 1
echo ' Done.'

sleep 0.1
printf 'Unmounting the image...'
sudo umount ${PREFIX}disk/myos || exit 1
echo ' Done.'

printf 'Deleting the temporary directory...'
rmdir ${PREFIX}disk/myos || exit 1
echo ' Done.'
