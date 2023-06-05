#ifndef KEYS_H
#define KEYS_H

#include "../cmd.h"
#include "../kernel.h"

void backspace(int *row, int *col, cmds lines[VGA_HEIGHT]);
void ascii(int *row, int *col, cmds lines[VGA_HEIGHT], unsigned char key, int shift, const char ascii_map[]);

void left_arrow(int *row, int *col);
void right_arrow(int *row, int *col);

void enter(int *row, int *col, cmds lines);

#endif // KEYS_H