CC = i386-elf-gcc
LD = i386-elf-ld

build:
    $(call build_os)

define build_os
    $(call build_kernel)
    grub-mkrescue -o os.iso isofiles/
endef

define build_kernel
    nasm -f elf kernel/kernel_entry.asm -o bin/kernel_entry.o
    nasm -f elf kernel/disk.asm -o isofiles/boot/disk.elf
    $(CC) -nostdlib -nodefaultlibs -ffreestanding -m32 -g -c kernel/lib.c -o bin/lib.o
    $(CC) -nostdlib -nodefaultlibs -ffreestanding -m32 -g -c kernel/vga.c -o bin/vga.o
    $(CC) -nostdlib -nodefaultlibs -ffreestanding -m32 -g -c kernel/cmd.c -o bin/cmd.o
    $(LD) -melf_386 -o bin/extra.o bin/lib.o bin/vga.o bin/cmd.o
    $(CC) -nostdlib -nodefaultlibs -ffreestanding -m32 -g -c kernel/kernel.c -o bin/kernel.o
    $(LD) -melf_i386 -o isofiles/boot/kernel.elf -Ttext 0x7ef0 bin/kernel_entry.o bin/kernel.o bin/extra.o

    rm bin/kernel_entry.o
    rm bin/kernel.o
    rm bin/extra.o
    rm bin/cmd.o
    rm bin/lib.o
    rm bin/vga.o
endef