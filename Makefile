AA = nasm
CC = gcc
LL = ld
QQ = qemu-system-x86_64
V = vim

QQF1 = -k en-us -drive format=raw,
QQF2 = ,index=0,if=floppy,  -m 256M

F1 = -f bin -o
F2 = -f elf -o
F3 = -fno-pic -m32 -ffreestanding -g -c
F4 = -m elf_i386 -o

BIN = Binaries

program:
	$(AA) "boot.asm" $(F1) "$(BIN)/boot.bin"
	$(AA) "kernel_entry.asm" $(F2) "$(BIN)/kernel_entry.o"
	$(CC) $(F3) "kernel.c" -o "$(BIN)/kernel.o"
	$(AA) "zeroes.asm" $(F1) "$(BIN)/zeroes.bin"
	$(LL) $(F4) "$(BIN)/full_kernel.bin" -Ttext 0x1000 "$(BIN)/kernel_entry.o" "$(BIN)/kernel.o" --oformat binary
	cat "$(BIN)/boot.bin" "$(BIN)/full_kernel.bin" "$(BIN)/zeroes.bin"  > "$(BIN)/OS.bin"

kernel:
	rm kernel.c
	$(V) kernel.c

boot:
	rm boot.asm
	$(V) boot.asm

start:
	$(QQ) $(QQF1)file="$(BIN)/OS.bin"$(QQF2)