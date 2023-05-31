#include "cmd.h"
#include "lib.h"
#include "vga.h"

void parse(cmds lines[VGA_HEIGHT], int *row, int *col) {
    char *cmd = lines[*row].line;
    cmd++;
    cmd++;
    cmd++;

    (*row)++;

    switch (lower(*cmd)) {
        case 'h':
            cmd++;
            write_char('1', 0x07, row, col, lines[*row]);
        default:
            write_string("> ", 0x07, row, col, lines[*row]);
            break;
    }
}