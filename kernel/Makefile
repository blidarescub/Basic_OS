CC = clang
CFLAGS = -Wall -m32 -c -ffreestanding -Iinclude/ -nostdlib

ASOURCES = $(wildcard src/*.asm)
AOBJECTS = $(ASOURCES:.asm=.o)
CSOURCES = $(wildcard src/*.c)
COBJECTS = $(CSOURCES:.c=.o)
OUTPUT = ../bin/kernel.bin

ASM = nasm
AFLAGS = -f elf32

LN = ld
LFLAGS = -T linker.ld -o $(OUTPUT) $(AOBJECTS) $(COBJECTS)

all: build

build: $(AOBJECTS) $(COBJECTS)
	$(LN) $(LFLAGS)
	@../disk.sh ../

%.o: %.asm
	$(ASM) $(AFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(AOBJECTS) $(COBJECTS) $(OUTPUT)
