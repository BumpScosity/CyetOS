#include "input.h"
#include "vga.h"

void arrow_keys(unsigned char key, int row, int col) {
    switch (key) {
        case 0x4B: // Left arrow key
            col--;
            move_cursor(row, col);

        case 0x4D: // Right arrow key
            if (col < VGA_WIDTH - 1) { // make sure there is a character to move forward to
                col++;
                move_cursor(row, col);
            }

        default:
            break;
    }
}