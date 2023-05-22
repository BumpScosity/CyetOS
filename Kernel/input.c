#include "input.h"
#include "vga.h"

void arrow_keys(unsigned char key, int row, int col) {
    if (key == 0x4B) { // check for left arrow key scancode
        if (col > 0) { // make sure there is a character to move back to
            col--;
            move_cursor(row, col);
        }
    }
    else if (key == 0x4D) { // check for right arrow key scancode
        col++;
        move_cursor(row, col);
    }
}