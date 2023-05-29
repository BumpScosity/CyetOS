CC = i386-elf-gcc
LD = i386-elf-ld

build:
    disk := $(wildcard os.iso)
    ifeq "$(disk)" ""
        $(call build_os)
    else
        rm os.iso
        $(call build_os)
    endif

define build_os
    $(call build_kernel)
    grub-mkrescue -o os.iso isofiles/
endef

define build_kernel
    nasm -f elf kernel/kernel_entry.asm -o bin/kernel_entry.o
    $(CC) -nostdlib -nodefaultlibs -ffreestanding -m32 -g -c kernel/kernel.c -o bin/kernel.o
    $(LD) -melf_i386 -o isofiles/boot/kernel.elf -Ttext 0x7ef0 bin/kernel_entry.o bin/kernel.o

    rm bin/kernel_entry.o
    rm bin/kernel.o
endef