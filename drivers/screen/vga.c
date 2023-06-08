#include "../../lib/lib.h"
#include "../../shell/cmd.h"

#include "vga.h"

char toStringRes[128];

void move_cursor(int row, int col) {
    unsigned short position = (row * VGA_WIDTH) + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}

void kPrintChar(const char s) {
    int *xy = (int*)0x99000;

    unsigned short offset = (xy[0] * VGA_WIDTH + xy[1]) * 2;
    char* vga_buffer = (char*)0xB8000;
    vga_buffer[offset] = s;
    vga_buffer[offset + 1] = 0x07;

    xy[1]++;
}

void kPrintCharCol(const char s, const int c) {
    int *xy = (int*)0x99000;

    unsigned short offset = (xy[0] * VGA_WIDTH + xy[1]) * 2;
    char* vga_buffer = (char*)0xB8000;
    vga_buffer[offset] = s;
    vga_buffer[offset + 1] = c;

    xy[1]++;
}

void kprint(const char *s) {
    int *xy = (int*)0x99000;
    xy[1] = 1;
    
    while (*s != '\0') {
        kPrintChar(*s);
        s++;
    }

    xy[0]++;
}

void kprintloc(const char *s, int x, int y) {
    int *xy = (int*)0x99000;
    
    while (*s != '\0') {
        unsigned short offset = (x * VGA_WIDTH + y) * 2;
        char* vga_buffer = (char*)0xB8000;
        vga_buffer[offset] = *s;
        vga_buffer[offset + 1] = 0x07;
        s++;
        y++;
    }
}

void kprintLC(const char *s, int x, int y, const int c) {
    int *xy = (int*)0x99000;
    
    while (*s != '\0') {
        unsigned short offset = (x * VGA_WIDTH + y) * 2;
        char* vga_buffer = (char*)0xB8000;
        vga_buffer[offset] = *s;
        vga_buffer[offset + 1] = c;
        s++;
        y++;
    }
}

void kprintcol(const char *s, const int c) {
    int *xy = (int*)0x99000;
    xy[1] = 1;
    
    while (*s != '\0') {
        kPrintCharCol(*s, c);
        s++;
    }

    xy[0]++;
    xy[1] = 1;
}