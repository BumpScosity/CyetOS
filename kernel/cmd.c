#include "cmd.h"
#include "lib.h"
#include "vga.h"

void parse(cmds lines[VGA_HEIGHT], int *row, int *col) {
    (*row)++;
    char *cmd = lines[*row].line;
    cmd++;
    cmd++;

    switch (*cmd) {
        case 'h':
            break;
        default:
            break;
    }

    (*row)++;
    write_string("> ", 0x07, row, col, lines[*row]);
    write_char(*cmd, 0x07, row, col, lines[*row]);
}