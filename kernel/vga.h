#ifndef VGA_H
#define VGA_H

#include "cmd.h"

void move_cursor(int row, int col);
void write_char_NM(char c, int color, int *row, int *col, cmds lines);
void write_char(char c, int color, int *row, int *col, cmds lines);
void write_string(const char* str, int color, int *row, int *col, cmds lines[VGA_HEIGHT]);

#endif // VGA_H