CC = i386-elf-gcc
LD = i386-elf-ld
OBJ = i386-elf-objcopy
VM = qemu-system-x86_64
KEY = kernel/keyboard

FLAGS = -nostdlib -nodefaultlibs -ffreestanding -m32 -g -c
KEYLIBS = bin/keyboard.o bin/input.o bin/keys.o
ETCLIBS = bin/lib.o bin/vga.o bin/cmd.o 
LIBS = $(ETCLIBS) $(KEYLIBS)

build:
	$(call build_os)

define build_os
    $(call build_kernel)
    nasm boot/boot.asm -o bin/boot.bin -i boot
    cat bin/boot.bin bin/kernel.bin > bin/os.bin
    qemu-img create os.img 1440k
    dd if=bin/os.bin of=os.img conv=notrunc
    $(clean)
    $(VM) -drive file=os.img,format=raw
endef

define build_keyboard
    $(CC) $(FLAGS) $(KEY)/keyboard.c -o bin/keyboard.o
    $(CC) $(FLAGS) $(KEY)/input.c -o bin/input.o

    $(CC) $(FLAGS) $(KEY)/keys.c -o bin/keys.o
endef

define build_kernel
    nasm -f elf kernel/kernel_entry.asm -o bin/kernel_entry.o
    $(call build_keyboard)
    $(CC) $(FLAGS) kernel/lib.c -o bin/lib.o
    $(CC) $(FLAGS) kernel/vga.c -o bin/vga.o
    $(CC) $(FLAGS) kernel/cmd.c -o bin/cmd.o
    $(CC) $(FLAGS) kernel/kernel.c -o bin/kernel.o
    $(LD) -melf_i386 -o bin/kernel.elf -Ttext 0x7ef0 bin/kernel_entry.o bin/kernel.o $(LIBS)
    $(OBJ) -O binary bin/kernel.elf bin/kernel.bin
endef

define clean
    rm bin/*.o
    rm bin/*.bin
    rm bin/*.elf
endef