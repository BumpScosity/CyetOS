###
# Not that good of a build script
###

###
# NOTE, DO NOT MODIFY THE BUILD SCRIPT AT ALL
###

## Compiler
CC=i386-elf-gcc

OBJCP=i386-elf-objcopy
## Linker
LD=i386-elf-ld

SRC=$(shell pwd)
OBJS = $(patsubst %.c,bin/%.o,$(SRCS))
## Directory to write binaries to
BIN=./bin
## Compiler Flags
FLAGS = -ffreestanding -m32 -fno-exceptions -g -c

## C source files
CSRC := $(shell find ./ -name "*.c")
## C target files
CTAR := $(patsubst %.c,%.o,$(CSRC))

## Files which must be linked first, if things break just bodge it together
LDPRIORITY = bin/kernel_entry.o bin/kernel.o bin/cmd.o bin/vga.o

all: prebuild build

prebuild:	## Prebuild instructions
	clear
	rm -rf bin
	mkdir bin

build: boot $(ASMTAR) $(CTAR)
	nasm boot/boot.asm -f bin -o bin/boot.bin -i boot
	nasm kernel/kernel_entry.asm -f elf32 -o bin/kernel_entry.o
	$(LD) -o bin/kernel.elf -Ttext 0x7ef0 $(LDPRIORITY) --start-group $(filter-out $(wildcard $(LDPRIORITY)), $(wildcard **/*.o)) --end-group --oformat elf32-i386 ## If this doesn't work, well, then you fix it yourself.
	$(OBJCP) -O binary bin/kernel.elf bin/kernel.bin
	cat bin/boot.bin bin/kernel.bin > bin/os.bin
	qemu-img create os.img 1440k
	dd if=bin/os.bin of=os.img conv=notrunc
	qemu-system-x86_64 -drive format=raw,file=os.img,index=0,if=floppy -m 4G

%.o: %.c
	$(CC) $(FLAGS) -c $< -o bin/$(@F)