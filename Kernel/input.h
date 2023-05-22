#ifndef INPUT_H
#define INPUT_H

#include "core.h"

void handle_backspace(Cursor_Position *cursor, int color);
void handle_character(const char key, Cursor_Position *cursor, int color, bool shift, char *ascii_map, int ascii_map_size);
void handle_enter(Cursor_Position *cursor);
void handle_left_arrow(Cursor_Position *cursor);
void handle_right_arrow(Cursor_Position *cursor);
void handle_up_arrow(Cursor_Position *cursor);
void handle_down_arrow(Cursor_Position *cursor);

#endif // INPUT_H
