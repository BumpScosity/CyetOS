#include "../lib.h"
#include "../kernel.h"
#include "../vga.h"
#include "../cmd.h"

#include "keyboard.h"
#include "keys.h"

const char ascii_map[] = {
    0,   0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,   0, // scan codes 0-15
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,   'a', 's', // scan codes 16-29
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,   '\\', 'z', 'x', 'c', 'v', // scan codes 30-44
    'b', 'n', 'm', ',', '.', '/', 0,   '*', 0, ' ', 0 // scan codes 45-57
};

const int ascii_map_size = sizeof(ascii_map) / sizeof(ascii_map[0]);

void handle_keyboard() {
    unsigned char key;
    int color = 0x07; // set color to white on black
    int row = 0;
    int col = 0;
    int shift = false;

    cmds lines[VGA_HEIGHT];

    write_string("> ", color, &row, &col, lines[row]);

    while (1) {
        __asm__("inb $0x64, %0" : "=a" (key));
        if (key & 0x01) { // check bit 0 of the status byte to see if a key has been pressed
            __asm__("inb $0x60, %0" : "=a" (key));
            if (key == 0x0E) {
                backspace(&row, &col, lines);
            }
            else if (key == 0x4B) {
                left_arrow(&row, &col);
            }
            else if (key == 0x4D) {
                right_arrow(&row, &col);
            }
            else if (key == 0x1C) {
                enter(&row, &col, *lines);
            }
            else if (key == 0x2A || key == 0x36) {
                shift = true;
            }
            else if (key == 0xAA || key == 0xB6) {
                shift = false;
            }
            else if (key < ascii_map_size) {
                ascii(&row, &col, lines, key, shift, ascii_map);
            }
        }
    }
}