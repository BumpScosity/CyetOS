#include "../drivers/keyboard/keyboard.h"
#include "../drivers/keyboard/keys.h"
#include "../drivers/screen/vga.h"
#include "../drivers/screen/vram.h"
#include "../memory/dynamic.h"
#include "../lib/lib.h"

#include "prog.h"

void title(const char *title) {
    int x, y;
    x = 0;
    for(y = 0; y < 80; y++){
        draw_pixel(x, y, 0xFF);
    }

    int len = strlen(title)-1;
    int i = 40 - len;
    while (*title != '\0') {
        unsigned short offset = (0 * VGA_WIDTH + i) * 2;
        char* vga_buffer = (char*)0xB8000;
        vga_buffer[offset] = *title;
        vga_buffer[offset + 1] = 0xF0;
        title++;
        i++;
    }
}

void screen1(const char *name) {
    int i, j;
    for(j = 0; j < 80; j++){
        for(i = 1; i < 25; i++){
            draw_pixel(i, j, BLACK);
        }
    }

    title(name);
}

void screen2() {
    int *xy = kget("xy");
    unsigned char key;
    while (1) {
        key = getch();
        if (key == F5) {
            title("SHELL");
            for (int i = 1; i < 79; i++) {
                draw_pixel(23, i, 0x07);
            }
            for(int j = 0; j < 80; j++){
                for(int i = 1; i < 23; i++){
                    draw_pixel(i, j, BLACK);
                }
            }
            xy[0] = 2;
            kprint("Enter a command...");
            xy[0] = 23;
            xy[1] = 1;
            kprint("> ");
            xy[1] = 1;
            xy[0] = 3;
            break;
        }
        else if (key == F6) {
            entry();
        }
    }
}