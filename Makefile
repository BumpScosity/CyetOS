AA = nasm
CC = gcc
LL = ld
QQ = qemu-system-x86_64
V = vim

QQF1 = -k en-us -drive format=raw,
QQF2 = ,index=0,if=floppy,  -m 256M

F1 = -f bin -o
F2 = -f elf -o
F3 = -fno-pic -m32 -ffreestanding -c
F4 = -m elf_i386 -o

BIN = Binaries
KER = Kernel
ASM = Assembly

program:
	$(AA) "$(ASM)/boot.asm" $(F1) "$(BIN)/boot.bin"
	$(AA) "$(ASM)/kernel_entry.asm" $(F2) "$(BIN)/kernel_entry.o"
	$(AA) "$(ASM)/zeroes.asm" $(F1) "$(BIN)/zeroes.bin"
	$(CC) $(F3) "$(KER)/kernel.c" -o "$(BIN)/kernel.o"
	$(CC) $(F3) "$(KER)/lib.c" -o "$(BIN)/lib.o"
	$(CC) $(F3) "$(KER)/vga.c" -o "$(BIN)/vga.o"
	$(LL) $(F4) "$(BIN)/full_kernel.bin" -Ttext 0x1000 "$(BIN)/kernel_entry.o" "$(BIN)/kernel.o" "$(BIN)/lib.o" "$(BIN)/vga.o" --oformat binary
	cat "$(BIN)/boot.bin" "$(BIN)/full_kernel.bin" "$(BIN)/zeroes.bin"  > "$(BIN)/OS.bin"

kernel:
	rm kernel.c
	$(V) kernel.c

boot:
	rm boot.asm
	$(V) boot.asm

start:
	$(QQ) $(QQF1)file="$(BIN)/OS.bin"$(QQF2)