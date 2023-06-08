# This needs to be ran twice at first >-< (Forgot about this, but just keep doing yourself, kiddo)

CC = i386-elf-gcc
LD = i386-elf-ld
OBJ = i386-elf-objcopy
VM = qemu-system-x86_64
KEY = drivers/keyboard
SC = drivers/screen

FLAGS = -Wno-implicit-function-declaration -nostdlib -nodefaultlibs -ffreestanding -m32 -g -c
LDPRIORITY = ./bin/kernel_entry.o ./bin/kernel.o ./bin/cmd.o ./bin/vga.o

build:
	$(call build_os)

clean: 
	@echo clealing...
	rm -rf bin
	mkdir bin

define build_os
    $(call build_kernel)
    nasm boot/boot.asm -o bin/boot.bin -i boot
    cat bin/boot.bin bin/kernel.bin > bin/os.bin
    qemu-img create bin/os.img 1440k
    dd if=bin/os.bin of=bin/os.img conv=notrunc
    $(VM) -drive file=bin/os.img,format=raw -m 128M
endef

define build_drivers
    $(CC) $(FLAGS) $(KEY)/input.c -o bin/input.o
    $(CC) $(FLAGS) $(KEY)/keyboard.c -o bin/keyboard.o
    $(CC) $(FLAGS) $(KEY)/keys.c -o bin/keys.o

    $(CC) $(FLAGS) $(SC)/vga.c -o bin/vga.o
    $(CC) $(FLAGS) $(SC)/vram.c -o bin/vram.o
endef

define build_shell
    $(CC) $(FLAGS) shell/cmd.c -o bin/cmd.o
    $(CC) $(FLAGS) shell/echo.c -o bin/echo.o
    $(CC) $(FLAGS) shell/help.c -o bin/help.o
    $(CC) $(FLAGS) shell/power.c -o bin/power.o
    $(CC) $(FLAGS) shell/misc.c -o bin/misc.o
endef

define build_lib
    $(CC) $(FLAGS) lib/lib.c -o bin/lib.o
    $(CC) $(FLAGS) lib/asm.c -o bin/asm.o
    $(CC) $(FLAGS) lib/string.c -o bin/string.o
endef

define build_core
    $(CC) $(FLAGS) core/prog.c -o bin/prog.o
    $(CC) $(FLAGS) core/menu.c -o bin/menu.o
    $(CC) $(FLAGS) core/entry.c -o bin/entry.o
endef

define build_kernel
    nasm -f elf kernel/kernel_entry.asm -o bin/kernel_entry.o
    $(call build_drivers)
    $(call build_shell)
    $(call build_core)
    $(call build_lib)
    $(CC) $(FLAGS) memory/mem.c -o bin/mem.o
    $(CC) $(FLAGS) kernel/kernel.c -o bin/kernel.o
    $(LD) -o bin/kernel.elf -Ttext 0x7ef0 $(LDPRIORITY) $(shell find ./bin -name "*.o" ! -name "kernel_entry.o" ! -name "kernel.o" ! -name "cmd.o" ! -name "vga.o") --oformat elf32-i386
    $(OBJ) -O binary bin/kernel.elf bin/kernel.bin
endef
