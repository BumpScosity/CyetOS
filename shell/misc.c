#include "../drivers/screen/vram.h"
#include "../drivers/screen/vga.h"
#include "../memory/dynamic.h"

#include "cmd.h"

void clear() {
    int *xy = kget("xy");
    int i, j;
    for(j = 0; j < 80; j++){
        for(i = 3; i < 23; i++){
            draw_pixel(i, j, BLACK);
        }
    }
    xy[0] = 3;
}