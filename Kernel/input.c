#include "input.h"
#include "vga.h"

void left(unsigned char key, int row, int col) {
    if (key == 0x1C) { // check for the enter key scancode
        row++;
        col = 0;
        move_cursor(row, col);
    }
}

void right(unsigned char key, int row, int col) {
    if (key == 0x4D) { // check for right arrow key scancode
        if (col < VGA_WIDTH - 1) { // make sure there is a character to move forward to
            col++;
            move_cursor(row, col);
        }
    }
}

void arrow_keys(unsigned char key, int row, int col) {
    left(key, row, col);
    right(key, row, col);
}