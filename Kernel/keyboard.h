#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "core.h"

void handle_key_press(unsigned char key, int row, int col, int color, bool shift, char *ascii_map, int ascii_map_size);
void handle_keyboard();

#endif // KEYBOARD_H