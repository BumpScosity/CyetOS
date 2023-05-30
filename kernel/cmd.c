#include "cmd.h"
#include "lib.h"
#include "vga.h"

void parse(cmds lines[VGA_HEIGHT], int *row, int *col) {
    const char *cmd = lines[*row-1].line;
    cmd++; cmd++;
    if (cmpstr(cmd, "help") == 0) {
        write_string("Help | Provides a list of commands", 0x07, row, col, lines);
    }
}