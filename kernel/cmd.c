#include "cmd.h"
#include "lib.h"
#include "vga.h"

void parse(cmds lines[VGA_HEIGHT], int *row, int *col) {
    char cmd[VGA_WIDTH-2];

    for (int i = 2; i < 80; i++) {
        cmd[i] = lines[*row-1].line[i];
    }

    write_string(cmd, 0x07, row, col, lines[*row]);

    (*row)++;
    write_string("> ", 0x07, row, col, lines[*row-1]);
}