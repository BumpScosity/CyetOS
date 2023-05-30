#include "lib.h"
#include "kernel.h"
#include "vga.h"
#include "cmd.h"

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

    cmds lines[VGA_HEIGHT];

    write_string("> ", color, &row, &col, lines[row]);

    while (1) {
        __asm__("inb $0x64, %0" : "=a" (key));
        if (key & 0x01) { // check bit 0 of the status byte to see if a key has been pressed
            __asm__("inb $0x60, %0" : "=a" (key));
            if (key == 0x0E) { // check for backspace key scancode
                if (col > 0) { // make sure there is a character to delete
                    col--; // move back to the previous column
                    write_char_NM(' ', color, &row, &col, lines[row]); // overwrite the previous character with a space
                }
            }
            else if (key == 0x4B) { // check for left arrow key scancode
                if (col > 0) { // make sure there is a character to move back to
                    col--;
                    move_cursor(row, col);
                }
            }
            else if (key == 0x4D) { // check for right arrow key scancode
                if (col < VGA_WIDTH - 1) { // make sure there is a character to move forward to
                    col++;
                    move_cursor(row, col);
                }
            }
            /*
            else if (key == 0x48) { // check for the up arrow key scancode
                if (row > 0) {
                    row--;
                    move_cursor(row, col);
                }
            }
            else if (key == 0x50) { // check for the down arrow key scancode
                if (row < VGA_HEIGHT-1) {
                    row++;
                    move_cursor(row, col);
                }
            }
            */
            else if (key == 0x1C) { // check for the enter key scancode
                row++;
                col = 0;
                parse(lines, &row-1, &col);
            }
            else if (key == 0x2A || key == 0x36) { // shift key pressed
                shift = true;
            }
            else if (key == 0xAA || key == 0xB6) { // shift key released
                shift = false;
            }
            else if (key < ascii_map_size && key != 0x03) {
                char ascii = ascii_map[key];
                if (ascii && ascii != ' ') {
                    if (shift) {
                        write_char(upper(ascii), color, &row, &col, lines[row]);
                    }
                    else if (!shift) {
                        write_char(ascii, color, &row, &col, lines[row]);
                    }
                }
                else if (ascii && ascii == ' ') {
                    write_char(' ', color, &row, &col, lines[row]);
                }
            }
        }
    }
}

void main() {
    handle_keyboard();
    return;
}
                                                        
