/*#include "input.h"
#include "../vga.h"
#include "../lib.h"

void handle_characters(int *row, int *col, int color, 
 int shift, unsigned char key, const char *ascii_map, const int ascii_map_size) {
    char ascii = ascii_map[key];
    if (ascii && ascii != ' ') {
        if (shift) {
            write_char(upper(ascii), color, *row, *col);
            (*col)++; // move to the next column
            move_cursor(*row, *col);
        }
        else if (!shift) {
            write_char(ascii, color, *row, *col);
            (*col)++; // move to the next column
            move_cursor(*row, *col);
        }
    }
    else if (ascii && ascii == ' ') {
        (*col)++;
        write_char(' ', color, *row, *col);
        move_cursor(*row, *col);
    }
}*/