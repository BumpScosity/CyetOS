#ifndef KEYS_H
#define KEYS_H

#include "../../shell/cmd.h"
#include "../screen/vga.h"

#define BACKSPACE 0x0E
#define LEFT_ARROW 0x4B
#define RIGHT_ARROW 0x4D
#define UP_ARROW 0x48
#define DOWN_ARROW 0x50
#define ENTER 0x1C

#define SHIFT_LEFT_HOLD 0x2A
#define SHIFT_LEFT_RELEASE 0xAA

#define SHIFT_RIGHT_HOLD 0x36
#define SHIFT_RIGHT_RELEASE 0xB6

#define F5 0x3F
#define F6 0x40

void ascii(unsigned char key, int shift, const char ascii_map[], char line[256], int *pos);

void left_arrow(int *pos);
void right_arrow(int *pos);

void enter(char line[256]);

#endif // KEYS_H