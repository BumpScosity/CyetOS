#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen/vram.h"
#include "../drivers/screen/vga.h"
#include "../memory/mem.h"
#include "../lib/lib.h"

#include "prog.h"

void meminfo() {
    int x = 9;
    mem_t memory = memget();
    mem_t upper_memory = upper_memget();

    kprintLC("Meminfo:", x, 1, 0x9F);

    x = 11;
    kprintLC("Lower mem size:", x, 1, 0x9F);
    kprintLC(intToString(memory.lower_size), x, sizeof("Lower mem size:")+1, 0x9F);
    kprintLC("KB", x, sizeof("Lower mem size:")+strlen(intToString(memory.lower_size))+1, 0x9F);

    x = 12;
    kprintLC("Upper mem size:", x, 1, 0x9F);
    kprintLC(intToString(memory.upper_size), x, sizeof("Upper mem size:")+1, 0x9F);
    kprintLC("KB", x, sizeof("Lower mem size:")+strlen(intToString(memory.upper_size))+1, 0x9F);

    x = 14;
    kprintLC("Extended 1 mem size:", x, 1, 0x9F);
    kprintLC(intToString(upper_memory.lower_size), x, sizeof("Extended 1 mem size:")+1, 0x9F);
    kprintLC("KB", x, sizeof("Extended 1 mem size:")+strlen(intToString(upper_memory.lower_size))+1, 0x9F);

    x = 15;
    kprintLC("Extended 2 mem size:", x, 1, 0x9F);
    kprintLC(intToString(upper_memory.upper_size), x, sizeof("Extended 2 mem size:")+1, 0x9F);
    kprintLC("KB", x, sizeof("Extended 2 mem size:")+strlen(intToString(upper_memory.upper_size))+1, 0x9F);
}

void time() {
    unsigned short data = 0;
    asm volatile (
        "mov %0, %%bx\n\t"
        : "=r" (data)
    );
    int x, y;
    x = 7;
    y = 1;

    int year = (data >> 9) + 1947;
    int month = (data >> 5) & 0x0F; month-=2;
    int day = ((data >> 12) & 0x1F); day--;

    kprintLC("Date: ", x, y, 0x9F);
    y = strlen("Date: ")+1;
    kprintLC(intToString(year), x, y, 0x9F);
    y = y+strlen(intToString(year));
    kprintLC("/", x, y, 0x9F);
    y++;
    kprintLC(intToString(month), x, y, 0x9F);
    y = y+strlen(intToString(month));
    kprintLC("/", x, y, 0x9F);
    y++;
    kprintLC(intToString(day), x, y, 0x9F);
}

void entry() {
    char *directory = (char*)0x90000;
    int *xy = (int*)0x99000;
    unsigned char key;
    xy[0] = 0;
    xy[1] = 0;
    strcpy(directory, "/");
    int x, y;

    for(y = 0; y < 80; y++){
        for(x = 0; x < 25; x++){
            draw_pixel(x, y, 0x9F);
        }
    }
    x = 0;
    for(y = 0; y < 80; y++){
        draw_pixel(x, y, 0xFF);
    }
    x = 23;
    title("ENTRY");

    kprintLC("Welcome to CyetOS!", 2, 1, 0x9F);
    kprintLC("Hit F5 to enter the shell at any time.", 4, 1, 0x9F);
    kprintLC("You can as well hit F6 to return to this menu at any time.", 5, 1, 0x9F);

    time();

    meminfo();

    x = 0;
    for(y = 0; y < 80; y++){
        draw_pixel(x, y, 0xFF);
    }
    x = 23;
    title("ENTRY");

    while (1) {
        key = getch();
        if (key == 0x3F) {
            break;
        }
    }
    shell();
}