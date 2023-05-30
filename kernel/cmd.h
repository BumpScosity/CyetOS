#ifndef CMD_H
#define CMD_H

#include "kernel.h"

typedef struct {
    int line_num;
    char line[VGA_WIDTH];
} cmds;

void parse(cmds lines[VGA_HEIGHT], int *row, int *col);


#endif // CMD_H