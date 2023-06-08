#include "vram.h"
#include "vga.h"

void draw_pixel(const int x, const int y, const int color) {
    unsigned short offset = (x * VGA_WIDTH + y) * 2;
    char* vga_buffer = (char*)0xB8000;
    vga_buffer[offset] = ' ';
    vga_buffer[offset + 1] = color;
}