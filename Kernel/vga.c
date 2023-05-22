#include "vga.h"

void move_cursor(int row, int col) {
    unsigned short position = (row * VGA_WIDTH) + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}

void write_char(char c, int color, int row, int col) {
    VGA_cell* vga_entry = &(vga[row][col]);

    vga_entry->character = c;
    vga_entry->color = color;

    // Write to VGA memory
    unsigned short offset = (row * VGA_WIDTH + col) * 2;
    char* vga_buffer = (char*)0xB8000;
    vga_buffer[offset] = c;
    vga_buffer[offset + 1] = color;
}
