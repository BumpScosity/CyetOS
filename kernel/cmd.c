#include "cmd.h"
#include "lib.h"
#include "vga.h"

void parse(cmds lines[VGA_HEIGHT], int *row, int *col) {
    char *cmd = lines[*row].line;
    cmd++;
    cmd++;

    switch (*cmd) {
        case 'h':
            cmd++;
            if (*cmd == 'e') {
                cmd++;
                if (*cmd == 'l') {
                    cmd++;
                    if (*cmd == 'p') {
                        (*row)++;
                        write_string("Test", 0x07, row, col, lines[*row]);
                    }
                }
            }
        default:
            (*row)++;
            write_string("> ", 0x07, row, col, lines[*row]);
            break;
    }
}