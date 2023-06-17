#include "../screen/vga.h"
#include "../screen/vram.h"
#include "../../lib/lib.h"
#include "../../shell/cmd.h"
#include "../../core/prog.h"
#include "../../memory/dynamic.h"

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
    int *rc = kget("rc");

    unsigned char key;
    int shift = false;
    char line[256];
    int pos = 0;

    rc[0] = 23;
    rc[1] = 3;
    move_cursor(rc[0], rc[1]);

    while (1) {
        key = getch();
        switch(key) {
            case F6:
                entry();
            case BACKSPACE:
            if (rc[1] > 3) { // make sure there is a character to delete
                rc[1]--; // move back to the previous column
                unsigned short offset = (rc[0] * VGA_WIDTH + rc[1]) * 2;
                char* vga_buffer = (char*)0xB8000;
                vga_buffer[offset] = ' ';
                vga_buffer[offset + 1] = 0x07;
                move_cursor(rc[0], rc[1]);
                pos--;
                line[pos] = ' ';
            }
            break;

            case LEFT_ARROW:
            left_arrow(&pos);
            break;
            case RIGHT_ARROW:
            right_arrow(&pos);
            break;

            case ENTER:
            enter(line);
            pos = 0;
            for (int i = 0; i < 80; i++) {
                line[i] = ' ';
            }
            break;

            case SHIFT_LEFT_HOLD:
            shift = true;
            break;
            case SHIFT_RIGHT_HOLD:
            shift = true;
            break;

            case SHIFT_LEFT_RELEASE:
            shift = false;
            break;
            case SHIFT_RIGHT_RELEASE:
            shift = false;
            break;

            default:
            if (key < ascii_map_size) {
                ascii(key, shift, ascii_map, line, &pos);
            }
            break;
        }
    }
}