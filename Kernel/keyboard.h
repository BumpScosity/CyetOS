#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "core.h"

void handle_key_press(unsigned char key, Cursor_Position *cursor, int color, int shift, char *ascii_map, int ascii_map_size);
void handle_keyboard(Cursor_Position *cursor);

#endif // KEYBOARD_H
