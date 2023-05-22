#include "keyboard.h"
#include "core.h"
#include "input.h"

void handle_key_press(unsigned char key, int *row, int *col, int color, int shift, char *ascii_map, int ascii_map_size) {
    switch (key) {
        case 0x0E:
            handle_backspace(row, col, color);
            break;
        default:
            handle_character(key, row, col, color, shift, ascii_map, ascii_map_size);
            break;
    }
}

void handle_keyboard() {
    unsigned char key;
    char ascii_map[] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
    };
    int ascii_map_size = sizeof(ascii_map) / sizeof(ascii_map[0]);
    int color = 0x07; // set color to white on black
    int row = 0;
    int col = 0;
    int shift = false;

    while (1) {
        __asm__("inb $0x64, %0" : "=a" (key));
        if (key & 0x01) { // check bit 0 of the status byte to see if a key has been pressed
            __asm__("inb $0x60, %0" : "=a" (key));
            handle_key_press(key, &row, &col, color, shift, ascii_map, ascii_map_size);
        }
    }
}
