#include "cmd.h"
#include "lib.h"
#include "vga.h"

void parse(cmds lines[VGA_HEIGHT], int *row, int *col) {
    char *cmd = lines[*row-1].line;
    cmd++; cmd++;

    switch (*cmd) {
        case 'h':
            cmd++;
            if (*cmd == 'e') {cmd++; if (*cmd == 'l') {cmd++; if (*cmd == 'p') {
                write_string_NM("Balls", 0x07, row, col, lines[*row-1]);
                move_cursor(*row, *col);
            }}}

        default:
            break;
    }

    (*row)++;
    write_string("> ", 0x07, row, col, lines[*row-1]);
}