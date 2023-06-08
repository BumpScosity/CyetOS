#include "../drivers/screen/vram.h"
#include "../drivers/screen/vga.h"

#include "cmd.h"

void clear() {
    int *xy = (int*)0x99000;
    int i, j;
    for(j = 0; j < 80; j++){
        for(i = 3; i < 23; i++){
            draw_pixel(i, j, BLUE);
        }
    }
    xy[0] = 3;
}

void dir() {
    char *directory = (char*)0x80000;
    int *xy = (int*)0x99000;
    char value = *directory;
    kprintcol(&value, 0x17);
}