#ifndef INPUT_H
#define INPUT_H

#include "core.h"

void handle_backspace(int *row, int *col, int color);
void handle_left_arrow(int *row, int *col);
void handle_right_arrow(int *row, int *col);
void handle_characters(int *row, int *col, int color,
 bool shift, unsigned char key, const char *ascii_map, const int ascii_map_size);

#endif // INPUT_H
