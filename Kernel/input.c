#include "input.h"
#include "vga.h"
#include "core.h"
#include "lib.h"

void handle_backspace(int *row, int *col, int color) {
    if ((*col) > 0) {
        (*col)--;
        write_char_NM(' ', color, *row, *col);
        move_cursor(*row, *col);
    }
}

void handle_character(const char key, int *row, int *col, int color, bool shift, char *ascii_map, int ascii_map_size) {
    if (key < ascii_map_size && key != 0x03) {
        char ascii = ascii_map[key];
        if (ascii && ascii != ' ') {
            if (shift) {
                write_char_NM(upper(ascii), color, *row, *col);
                (*col)++;
                move_cursor(*row, *col);
            }
            else if (!shift) {
                write_char_NM(ascii, color, *row, *col);
                (*col)++;
                move_cursor(*row, *col);
            }
        }
        else if (ascii && ascii == ' ') {
            (*col)++;
            write_char_NM(' ', color, *row, *col);
            move_cursor(*row, *col);
        }
    }
}