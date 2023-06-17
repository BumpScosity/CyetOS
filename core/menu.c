#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen/vram.h"
#include "../drivers/screen/vga.h"
#include "../memory/dynamic.h"

#include "prog.h"

void shell() {
    int *xy = kget("xy");
    int *rc = kget("rc");

    int x, y;

    for(y = 0; y < 80; y++){
        for(x = 0; x < 25; x++){
            draw_pixel(x, y, BLACK);
        }
    }
    x = 0;
    for(y = 0; y < 80; y++){
        draw_pixel(x, y, 0xFF);
    }
    x = 23;
    for (y = 1; y < 79; y++) {
        draw_pixel(x, y, 0x0F);
    }

    for (int i = 55; i < 78; i++) {
        draw_pixel(2, i, BLACK);
    }
    kprintloc("dir:", 2, 50);
    kprintloc("/", 2, 55);
    title("SHELL");

    unsigned char key;
    xy[0] = 2;
    xy[1] = 1;

    rc[0] = 23;
    rc[1] = 1;

    kprintcol("Enter a command...", 0x07);

    xy[0] = rc[0];
    xy[1] = rc[1];

    kprint("> ");

    rc[1] = 3;
    
    xy[0] = 3;
    xy[1] = 1;

    rc[0] = 27;
    handle_keyboard();
}