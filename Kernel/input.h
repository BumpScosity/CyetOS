#ifndef INPUT_H
#define INPUT_H

#include "core.h"

void handle_backspace(int *row, int *col, int color);
void handle_character(const char key, int *row, int *col, int color, bool shift, char *ascii_map, int ascii_map_size);
void handle_enter(int *row, int *col);
void handle_left_arrow(int *col);
void handle_right_arrow(int *col);
void handle_up_arrow(int *row);
void handle_down_arrow(int *row);

#endif // INPUT_H
