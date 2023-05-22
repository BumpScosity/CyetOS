#ifndef VGA_H
#define VGA_H

typedef struct {
    char character;
    int color;
} VGA_cell;

void move_cursor(int row, int col);
void write_char_NM(char c, int color, int row, int col); // NM(No Move) means it will not move the cursor

#endif // VGA_H