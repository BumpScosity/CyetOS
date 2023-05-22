#include "input.h"
#include "vga.h"
#include "core.h"
#include "lib.h"

void handle_backspace(CursorPosition *cursor, int color) {
    if (col > 0) {
        col--;
        write_char_NM(' ', color, cursor);
        move_cursor(cursor);
    }
}

void handle_character(char key, CursorPosition *cursor, int color, bool shift, char ascii_map[59], int ascii_map_size) {
    if (key < ascii_map_size && key != 0x03) {
        char ascii = ascii_map[key];
        if (ascii && ascii != ' ') {
            if (shift) {
                write_char_NM(upper(ascii), color, cursor);
                col++;
                move_cursor(cursor);
            }
            else if (!shift) {
                write_char_NM(ascii, color, cursor);
                col++;
                move_cursor(cursor);
            }
        }
        else if (ascii && ascii == ' ') {
            col++;
            write_char_NM(' ', color, cursor);
            move_cursor(cursor);
        }
    }
}