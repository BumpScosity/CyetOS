#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define true 1
#define false 0

typedef struct {
    char character;
    int color;
} VGA_cell;

VGA_cell vga[VGA_HEIGHT][VGA_WIDTH];

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

void move_cursor(int row, int col) {
    unsigned short position = (row * VGA_WIDTH) + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}

void write_char_NM(char c, int color, int row, int col) { // NM(No Move) means it will not move the cursor
    VGA_cell* vga_entry = &(vga[row][col]);

    vga_entry->character = c;
    vga_entry->color = color;

    // Write to VGA memory
    unsigned short offset = (row * VGA_WIDTH + col) * 2;
    char* vga_buffer = (char*)0xB8000;
    vga_buffer[offset] = c;
    vga_buffer[offset + 1] = color;
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
}

void main() {
    handle_keyboard();
    return;
}
