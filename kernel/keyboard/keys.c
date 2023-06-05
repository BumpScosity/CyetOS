#include "../vga.h"
#include "../cmd.h"
#include "../kernel.h"

#include "keys.h"

void backspace(int *col, int *row, cmds lines[VGA_HEIGHT]) {
    if (col > 0) { // make sure there is a character to delete
        col--; // move back to the previous column
        write_char_NM(' ', 0x07, row, col, lines[*row]); // overwrite the previous character with a space
    }
}

void left_arrow(int *row, int *col) {
    if (*col > 0) { // make sure there is a character to move back to
        (*col)--;
        move_cursor(*row, *col);
    }
}

void right_arrow(int *row, int *col) {
    if (*col > VGA_WIDTH - 1) { // make sure there is a character to move back to
        (*col)++;
        move_cursor(*row, *col);
    }
}

void enter(int *row, int *col, cmds lines) {
    *col = 0;
    parse(&lines, row, col);
}

void ascii(int *row, int *col, cmds lines[VGA_HEIGHT], unsigned char key, int shift, const char ascii_map[]) {
    char ascii = ascii_map[key];
    if (ascii && ascii != ' ') {
        if (shift) {
            write_char(upper(ascii), 0x07, row, col, lines[*row]);
        }
        else if (!shift) {
            write_char(ascii, 0x07, row, col, lines[*row]);
        }
    }
    else if (ascii && ascii == ' ') {
        write_char(' ', 0x07, row, col, lines[*row]);
    }
}


/*  
            else if (key == 0x48) { // check for the up arrow key scancode
                if (row > 0) {
                    row--;
                    move_cursor(row, col);
                }
            }
            else if (key == 0x50) { // check for the down arrow key scancode
                if (row < VGA_HEIGHT-1) {
                    row++;
                    move_cursor(row, col);
                }
            }
            */