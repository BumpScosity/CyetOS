#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define true 1
#define false 0

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

void move_cursor(int offset) {
    offset /= 2;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(offset & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((offset >> 8) & 0xFF));
}

void write_char_NM(char c, int color, int offset) { // NM(No Move) means it will not move the cursor
    char* vga_buffer = (char*) 0xb8000;
    vga_buffer[offset * 2] = c;
    vga_buffer[offset * 2 + 1] = color;
}

void write_char(char c, int color, int offset) { // NM(No Move) means it will not move the cursor
    char* vga_buffer = (char*) 0xb8000;
    vga_buffer[offset * 2] = c;
    vga_buffer[offset * 2 + 1] = color;
    move_cursor((offset + 1) * 2); // move the cursor to the next character position
}

void main() {
    unsigned char key;
    char ascii_map[] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
    };
    int ascii_map_size = sizeof(ascii_map) / sizeof(ascii_map[0]);
    int color = 0x07; // set color to white on black
    int offset = 0;
    int shift;
        
    while (1) {
        __asm__("inb $0x64, %0" : "=a" (key));
        if (key & 0x01) { // check bit 0 of the status byte to see if a key has been pressed
            __asm__("inb $0x60, %0" : "=a" (key));
            if (key == 0x0E) { // check for backspace key scancode
                if (offset > 0) { // make sure there is a character to delete
                    offset--; // move the offset back by two to the previous character position
                    write_char_NM(' ', color, offset); // overwrite the previous character with a space
                    move_cursor(offset * 2 + 1);
                }
            }
            else if (key == 0x4B) { // check for left arrow key scancode
                if (offset > 0) { // make sure there is a character to move back to
                    offset--;
                    move_cursor(offset);
                }
            }
            else if (key == 0x4D) { // check for right arrow key scancode
                offset++;
                move_cursor(offset);
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
                        write_char(upper(ascii), color, offset);
                        offset++; // increment the offset by two to move to the next character position
                    }
                    else if (!shift) {
                        write_char(ascii, color, offset);
                        offset++; // increment the offset by two to move to the next character position
                    }
                }
                else if (ascii && ascii == ' ') {
                    offset++;
                    write_char_NM(' ', color, offset);
                    move_cursor(offset * 2 + 1);
                }
            }
        }
    }
    return;
}