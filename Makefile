AA = nasm
CC = gcc
LL = ld
QQ = qemu-system-x86_64

QQF1 = -k en-us -drive format=raw,
QQF2 = ,index=0,if=floppy,  -m 256M

F1 = -f bin -o
F2 = -f elf -o
F3 = -fno-pic -m32 -ffreestanding -c
F4 = -m elf_i386 -o

BIN = Binaries
KER = Kernel
ASM = Assembly

kernel_objects = "$(BIN)/kernel_entry.o" "$(BIN)/kernel.o" "$(BIN)/vga.o" "$(BIN)/keyboard.o" "$(BIN)/lib.o" "$(BIN)/input.o"

program:
	$(AA) "$(ASM)/boot.asm" $(F1) "$(BIN)/boot.bin"
	$(AA) "$(ASM)/kernel_entry.asm" $(F2) "$(BIN)/kernel_entry.o"
	$(AA) "$(ASM)/zeroes.asm" $(F1) "$(BIN)/zeroes.bin"
	$(CC) $(F3) "$(KER)/kernel.c" -o "$(BIN)/kernel.o"
	$(CC) $(F3) "$(KER)/vga.c" -o "$(BIN)/vga.o"
	$(CC) $(F3) "$(KER)/keyboard.c" -o "$(BIN)/keyboard.o"
	$(CC) $(F3) "$(KER)/lib.c" -o "$(BIN)/lib.o"
	$(CC) $(F3) "$(KER)/input.c" -o "$(BIN)/input.o"
	$(LL) $(F4) "$(BIN)/full_kernel.bin" -Ttext 0x1000 $(kernel_objects) --oformat binary
	cat "$(BIN)/boot.bin" "$(BIN)/full_kernel.bin" "$(BIN)/zeroes.bin"  > "$(BIN)/OS.bin"

start:
	$(QQ) $(QQF1)file="$(BIN)/OS.bin"$(QQF2)