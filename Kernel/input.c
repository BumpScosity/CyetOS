#include "input.h"
#include "vga.h"
#include "core.h"

void shift_key(unsigned char key, int shift) {
    if (key == 0x2A || key == 0x36) { // shift key pressed
            shift = true;
        }
    else if (key == 0xAA || key == 0xB6) { // shift key released
        shift = false;
    }
}