#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#include "core.h"

typedef struct {
    char character;
    int color;
} VGA_cell;

void move_cursor(Cursor_Position *cursor);
void write_char_NM(char c, int color, Cursor_Position *cursor); // NM(No Move) means it will not move the cursor

#endif // VGA_H