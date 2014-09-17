CC = clang
CFLAGS = -Wall -m32 -c -ffreestanding -Iinclude/ -nostdinc -nostdlib

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = ../bin/kernel.bin

ASM = nasm
AFLAGS = -f elf32

LN = ld
LFLAGS = -T linker.ld -o $(OUTPUT) src/start.o src/kernel_ll.o $(OBJECTS)

all: build

build: src/start.o src/kernel_ll.o $(OBJECTS)
	$(LN) $(LFLAGS)
	../disk.sh ../

src/start.o: src/start.asm
	$(ASM) $(AFLAGS) $< -o $@

src/kernel_ll.o: src/kernel.asm
	$(ASM) $(AFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(OUTPUT)
