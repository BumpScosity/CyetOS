#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef struct {
    char character;
    int color;
} VGA_cell;

void move_cursor(int row, int col);
void write_char(char c, int color, int row, int col);

#endif  // VGA_H
