section .multiboot
    align 4
    dd 0x1BADB002      ; MAGIC
    dd 0x00000003      ; FLAGS
    dd -(0x1BADB002 + 0x00000003)  ; CHECKSUM

section .text
    global _start
    extern main

_start:
    mov ebx, 0        ; Set ebx to zero as required by GRUB
    call main         ; Call the main function

    jmp $