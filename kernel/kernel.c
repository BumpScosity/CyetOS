#include "../drivers/keyboard/keyboard.h"
#include "../drivers/floppy/floppy.h"
#include "../drivers/keyboard/keys.h"
#include "../drivers/screen/vram.h"
#include "../drivers/screen/vga.h"
#include "../memory/dynamic.h"
#include "../shell/cmd.h"
#include "../core/prog.h"
#include "../lib/lib.h"

#include "../filesystem/filesystem.h"

// Pickle jars say eat 1/5th of a pickle, who the hell eats 1/5th of a pickle?

void main() {
    int *xy = kget("xy");

    unsigned char key;
    xy[0] = 0;
    xy[1] = 0;
    int x, y;

    for(y = 0; y < 80; y++){
        for(x = 0; x < 25; x++){
            draw_pixel(x, y, 0x99);
        }
    }
    x = 0;
    for(y = 0; y < 80; y++){
        draw_pixel(x, y, 0xFF);
    }
    x = 23;
    title("ENTRY");

    kprintLC("Welcome to OnyxOs!", 2, 1, 0x9F);
    kprintLC("Hit F5 to enter the shell at any time.", 4, 1, 0x9F);
    kprintLC("You can as well hit F6 to return to this menu at any time.", 5, 1, 0x9F);

    meminfo();
    driveinfo();
    drivetest();

    kprintLC("Waiting for floppy drivers to initialize... ", 22, 1, 0x9F);

    x = 0;
    for(y = 0; y < 80; y++){
        draw_pixel(x, y, 0xFF);
    }
    x = 23;
    title("ENTRY");
    void driveinfo();

    // Initialize the floppy disk driver
    int result = floppy_init();
    if (result != 0) {
        kprintLC("Waiting for floppy drivers to initialize... ERROR, please shutdown the computer", 22, 1, 0x9F);
        return;
    }

    while (1) {
        key = getch();
        if (key == F5) {
            break;
        }
    }
    shell();
    return;
}
                                                        
