#include "input.h"
#include "vga.h"
#include "core.h"

int shift_key(unsigned char key) {
    bool ret = false;
    if (key == 0x2A || key == 0x36) { // shift key pressed
        ret = true;
    }
    else if (key == 0xAA || key == 0xB6) { // shift key released
        ret = false;
    }
    return ret;
}