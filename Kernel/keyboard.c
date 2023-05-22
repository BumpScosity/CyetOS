#include "keyboard.h"
#include "lib.h"
#include "core.h"
#include "vga.h"
#include "input.h"

void handle_key_press(unsigned char key, int row, int col, int color, bool shift, char ascii_map[59]) {
    int ascii_map_size = sizeof(ascii_map) / sizeof(ascii_map[0]);
    switch (key) {
        case 0x0E: // Backspace
            handle_backspace(row, col, color);
            break;
        case 0x4B: // Left arrow
            handle_left_arrow(col);
            break;
        case 0x1C: // Enter
            handle_enter(row, col);
            break;
        case 0x4D: // Right arrow
            handle_right_arrow(col);
            break;
        case 0x48: // Up arrow
            handle_up_arrow(row);
            break;
        case 0x50: // Down arrow
            handle_down_arrow(row);
            break;
        default: // Other keys
            handle_character(key, row, col, color, shift, ascii_map, ascii_map_size);
            break;
    }
}


void handle_keyboard() {
    unsigned char key;
    char ascii_map[59] = {
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
            switch (key) {
                case 0x0E: // backspace key
                    if (col > 0) {
                        col--;
                        write_char_NM(' ', color, row, col);
                        move_cursor(row, col);
                    }
                    break;
                case 0x4B: // left arrow key
                    if (col > 0) {
                        col--;
                        move_cursor(row, col);
                    }
                    break;
                case 0x1C: // enter key
                    row++;
                    col = 0;
                    move_cursor(row, col);
                    break;
                case 0x4D: // right arrow key
                    if (col < VGA_WIDTH - 1) {
                        col++;
                        move_cursor(row, col);
                    }
                    break;
                case 0x48: // up arrow key
                    if (row > 0) {
                        row--;
                        move_cursor(row, col);
                    }
                    break;
                case 0x50: // down arrow key
                    if (row < VGA_HEIGHT - 1) {
                        row++;
                        move_cursor(row, col);
                    }
                    break;
                case 0x2A: // shift key pressed
                case 0x36:
                    shift = true;
                    break;
                case 0xAA: // shift key released
                case 0xB6:
                    shift = false;
                    break;
                default:
                    if (key < ascii_map_size && key != 0x03) {
                        char ascii = ascii_map[key];
                        if (ascii && ascii != ' ') {
                            if (shift) {
                                write_char_NM(upper(ascii), color, row, col);
                                col++;
                            }
                            else if (!shift) {
                                write_char_NM(ascii, color, row, col);
                                col++;
                            }
                        }
                        else if (ascii && ascii == ' ') {
                            col++;
                            write_char_NM(' ', color, row, col);
                            move_cursor(row, col);
                        }
                    }
                    break;
            }
        }
    }
}