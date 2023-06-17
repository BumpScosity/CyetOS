#include "../drivers/keyboard/keyboard.h"
#include "../drivers/floppy/floppy.h"
#include "../filesystem/filesystem.h"
#include "../drivers/screen/vram.h"
#include "../drivers/screen/vga.h"
#include "../memory/dynamic.h"
#include "../memory/mem.h"
#include "../lib/lib.h"

#include "prog.h"

static const char *drive_types[8] = {
        "none",
        "360kB 5.25\"",
        "1.2MB 5.25\"",
        "720kB 3.5\"",

        "1.44MB 3.5\"",
        "2.88MB 3.5\"",
        "unknown type",
        "unknown type"
};

void drivetest() {
    // First test
    char data1[] = "First Test Message";
    int write_result1 = disk_write("TestCaseOne.TestTxt", data1, sizeof(data1) - 1);
    if (write_result1 != 0) {
        kprintLC("Disk test ", 24, 1, 0x97);
        kprintLC("Failed1", 24, strlen("Disk test ")+1, 0x9C);
        return;
    }

    char read_data1[SECTOR_SIZE * NUM_SECTORS];
    int read_result1 = disk_read("TestCaseOne.TestTxt", read_data1);
    if (read_result1 != 0) {
        kprintLC("Disk test ", 24, 1, 0x9F);
        kprintLC("Failed2", 24, strlen("Disk test ")+1, 0x9C);
        return;
    }
    if (strncmp(read_data1, "First Test Message", strlen("First Test Message")-1) != 0) {
        kprintLC("Disk test ", 24, 1, 0x9F);
        kprintLC(read_data1, 24, strlen("Disk test ")+1, 0x9C);
        return;
    }

    // Second test
    char data2[] = "Second Test Message";
    int write_result2 = disk_write("TestCaseOne.TestTxt", data2, sizeof(data2) - 1);
    if (write_result2 != 0) {
        kprintLC("Disk test ", 24, 1, 0x97);
        kprintLC("Failed", 24, strlen("Disk test ")+1, 0x9C);
        return;
    }

    char read_data2[SECTOR_SIZE * NUM_SECTORS];
    int read_result2 = disk_read("TestCaseOne.TestTxt", read_data2);
    if (read_result1 != 0) {
        kprintLC("Disk test ", 24, 1, 0x9F);
        kprintLC("Failed", 24, strlen("Disk test ")+1, 0x9C);
        return;
    }
    if (strncmp(read_data2, "Second Test Message", strlen("Second Test Message")-1) != 0) {
        kprintLC("Disk test ", 24, 1, 0x9F);
        kprintLC("Failed", 24, strlen("Disk test ")+1, 0x9C);
        return;
    }

    kprintLC("Disk test ", 24, 1, 0x9F);
    kprintLC("Passed", 24, strlen("Disk test ")+1, 0x9A);
}

void driveinfo() {
    int x, y;
    x = 17;
    y = 1;
    unsigned int drives = floppy_detect_drives();
    kprintLC("DRIVE INFO: ", x, y, 0x9F);
    x+=2;
    kprintLC("* Floppy drive 0: ", x, y, 0x9F);
    kprintLC(drive_types[drives >> 4], x, strlen("* Floppy drive 0: ")+1, 0x9F);
    x++;
    kprintLC("* Floppy drive 1: ", x, y, 0x9F);
    kprintLC(drive_types[drives & 0xf], x, strlen("* Floppy drive 1: ")+1, 0x9F);
}

void meminfo() {
    int x = 7;
    mem_t memory = memget();
    mem_t upper_memory = upper_memget();
    size_t usage = kMemUsage();

    kprintLC("MEMORY INFO:", x, 1, 0x9F);

    x = 9;

    kprintLC("* Memory allocation usage: ", x, 1, 0x9F);
    kprintLC(intToString(usage), x, sizeof("* Memory allocation usage: "), 0x9F);
    kprintLC("Bytes", x, sizeof("* Memory allocation usage: ")+strlen(intToString(usage))+1, 0x9F);

    x = 11;
    kprintLC("* Lower mem size:", x, 1, 0x9F);
    kprintLC(intToString(memory.lower_size), x, sizeof("* Lower mem size:")+1, 0x9F);
    kprintLC("KB", x, sizeof("* Lower mem size:")+strlen(intToString(memory.lower_size))+1, 0x9F);

    x = 12;
    kprintLC("* Upper mem size:", x, 1, 0x9F);
    kprintLC(intToString(memory.upper_size), x, sizeof("* Upper mem size:")+1, 0x9F);
    kprintLC("KB", x, sizeof("* Lower mem size:")+strlen(intToString(memory.upper_size))+1, 0x9F);

    x = 14;
    kprintLC("* Extended 1 mem size:", x, 1, 0x9F);
    kprintLC(intToString(upper_memory.lower_size), x, sizeof("* Extended 1 mem size:")+1, 0x9F);
    kprintLC("KB", x, sizeof("* Extended 1 mem size:")+strlen(intToString(upper_memory.lower_size))+1, 0x9F);

    x = 15;
    kprintLC("* Extended 2 mem size:", x, 1, 0x9F);
    kprintLC(intToString(upper_memory.upper_size), x, sizeof("* Extended 2 mem size:")+1, 0x9F);
    kprintLC("KB", x, sizeof("* Extended 2 mem size:")+strlen(intToString(upper_memory.upper_size))+1, 0x9F);
}

void entry() {
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

    kprintLC("Welcome to OnyxOS!", 2, 1, 0x9F);
    kprintLC("Hit F5 to enter the shell at any time.", 4, 1, 0x9F);
    kprintLC("You can as well hit F6 to return to this menu at any time.", 5, 1, 0x9F);

    meminfo();
    driveinfo();
    drivetest();

    kprintLC("Waiting for floppy drivers to initialize... Initialized", 22, 1, 0x9F);

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
