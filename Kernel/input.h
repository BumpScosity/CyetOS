#ifndef INPUT_H
#define INPUT_H

#include "core.h"

void handle_backspace(CursorPosition *cursor, int color);
void handle_character(char key, CursorPosition *cursor, int color, bool shift, char ascii_map[59], int ascii_map_size);
void handle_enter(CursorPosition *cursor);
void handle_left_arrow(CursorPosition *cursor);
void handle_right_arrow(CursorPosition *cursor);
void handle_up_arrow(CursorPosition *cursor);
void handle_down_arrow(CursorPosition *cursor);

#endif // INPUT_H