#include "input.h"
#include "vga.h"
#include "core.h"

int shift_handler(unsigned char key) {
    bool ret = true;
    switch(key) {
        case 0x2A:
        ret = true; break;
        case 0x36:
        ret = true; break;

        case 0xAA:
        ret = false; break;
        case 0xB6:
        ret = false; break;

        default:
        ret = false; break;
    }
    return ret;
}