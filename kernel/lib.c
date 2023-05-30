#include "lib.h"

char upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    } else {
        return c;
    }
}

void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

int cmpchar(const char *c1, const char c2) {
    return (*c1 == c2) ? 1 : 0;
}

int cmpstr(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0; // Strings are not equal
        }
        i++;
    }
    // Check if both strings have reached the end
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0; // Strings are equal
    }
    return 1; // Strings have different lengths
}
