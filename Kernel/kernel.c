#include "core.h"
#include "keyboard.h"

void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

void main() {
    CursorPosition cursor = {0, 0};
    handle_keyboard(&cursor);
    return;
}
