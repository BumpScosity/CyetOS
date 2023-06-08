#ifndef VRAM_H
#define VRAM_H

#define BLACK 0x00
#define BLUE 0x11
#define GREEN 0x22
#define CYAN 0x33
#define RED 0x44
#define MAGENTA 0x55
#define BROWN 0x66
#define LIGHT_GRAY 0x77
#define DARK_GRAY 0x88
#define LIGHT_BLUE 0x99
#define LIGHT_GREEN 0xAA
#define LIGHT_CYAN 0xBB
#define LIGHT_RED 0xCC
#define LIGHT_MAGENTA 0xDD
#define YELLOW 0xEE
#define WHITE 0xFF


void draw_pixel(const int x, const int y, const int color);

#endif // VRAM_H