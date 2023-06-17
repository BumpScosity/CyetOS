#include "internal.h"
#include "floppy.h"

/*
 * https://forum.osdev.org/viewtopic.php?t=13538
 */
unsigned int floppy_detect_drives() {
    outb(0x70, 0x10);
    unsigned drives = inb(0x71);
    return drives;
}

/*
 * https://wiki.osdev.org/CMOS#Register_0x10
 * https://forum.osdev.org/viewtopic.php?t=13538
 */
uint8_t get_drive_type() {
    // ask CMOS for floppy drive type
    outb(0x70, 0x10);
    uint8_t drives = inb(0x71);
    if(drives >> 4 == 0){
        return drives & 0xf;
    }
    return drives >> 4;
}

/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#Drive_Selection
 */
void drive_select(int drive){
    outb(FLOPPY_CONFIGURATION_CONTROL_REGISTER, 0); // This is usually correct, even tho it changes if not using 1.44Mb drive.
    specify();

    // Select drive in DOR and turn on its motor
    uint8_t DOR = inb(FLOPPY_DIGITAL_OUTPUT_REGISTER);
    // turn off all motors | select drive | turn on drive's motor
    DOR = (DOR & 0xC) | (drive | (1 << (4 + drive)));
    outb(FLOPPY_DIGITAL_OUTPUT_REGISTER, DOR);
}