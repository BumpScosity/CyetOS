#include "lib.h"

char upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    else {
        return c; // Return as-is if not an uppercase letter
    }
}

void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

char lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        // Convert uppercase letter to lowercase by adding the ASCII offset
        return c + ('a' - 'A');
    }
    else {
        return c; // Return as-is if not an uppercase letter
    }
}