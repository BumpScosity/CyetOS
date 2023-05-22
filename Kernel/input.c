#include "input.h"
#include "vga.h"
#include "core.h"

int shift_key(unsigned char key) {
    switch(key) {
        case 0x2A:
        return true; break;
        case 0x36:
        return true; break;

        case 0xAA:
        return false; break;
        case 0xB6:
        return false; break;

        default:
        return false; break;
    }
}