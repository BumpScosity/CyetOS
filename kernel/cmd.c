#include "cmd.h"
#include "lib.h"
#include "vga.h"

void parse(cmds lines[VGA_HEIGHT], int *row, int *col) {
    char *cmd = lines[*row].line;
    cmd++;
    cmd++;

    (*row)++;

    switch (*cmd) {
        case 'h':
            cmd++;
            write_char('1', 0x07, row, col, lines[*row]);
            if (*cmd == 'e') {
                cmd++;
                write_char('2', 0x07, row, col, lines[*row]);
                if (*cmd == 'l') {
                    cmd++;
                    write_char('3', 0x07, row, col, lines[*row]);
                    if (*cmd == 'p') {
                        write_string("Test", 0x07, row, col, lines[*row]);
                    }
                }
            }
        default:
            write_string("> ", 0x07, row, col, lines[*row]);
            break;
    }
}