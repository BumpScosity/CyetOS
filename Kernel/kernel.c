#include "core.h"
#include "vga.h"
#include "input.h"

char upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    } else {
        return c;
    }
}

void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

void main() {
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
            shift_key(key);
            if (key == 0x0E) { // check for backspace key scancode
                if (col > 0) { // make sure there is a character to delete
                    col--; // move back to the previous column
                    write_char_NM(' ', color, row, col); // overwrite the previous character with a space
                    move_cursor(row, col);
                }
            }
            else if (key == 0x4B) { // check for left arrow key scancode
                if (col > 0) { // make sure there is a character to move back to
                    col--;
                    move_cursor(row, col);
                }
            }
            else if (key == 0x1C) { // check for the enter key scancode
                row++;
                col = 0;
                move_cursor(row, col);
            }
            else if (key == 0x4D) { // check for right arrow key scancode
                if (col < VGA_WIDTH - 1) { // make sure there is a character to move forward to
                    col++;
                    move_cursor(row, col);
                }
            }
            else if (key < ascii_map_size && key != 0x03) {
                char ascii = ascii_map[key];
                if (ascii && ascii != ' ') {
                    if (shift) {
                        write_char_NM(upper(ascii), color, row, col);
                        col++; // move to the next column
                    }
                    else if (!shift) {
                        write_char_NM(ascii, color, row, col);
                        col++; // move to the next column
                    }
                }
                else if (ascii && ascii == ' ') {
                    col++;
                    write_char_NM(' ', color, row, col);
                    move_cursor(row, col);
                }
            }
        }
    }

    return;
}
