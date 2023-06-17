#include "internal.h"
#include "floppy.h"

/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#Configure
 */
void floppy_configure(int implied_seek, int FIFO, int drive_polling_mode, int threshold){
    floppy_write_cmd(FLOPPY_CONFIGURE);
    floppy_write_cmd(0); // IDK why this even exists, it is always 0
    floppy_write_cmd(implied_seek << 6 | !FIFO << 5 | !drive_polling_mode << 4 | threshold - 1);
    floppy_write_cmd(0); // pre-compensation value - should always be 0

}

/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#Recalibrate
 */
void floppy_recalibrate(uint8_t drive){
    floppy_write_cmd(FLOPPY_RECALIBRATE);
    floppy_write_cmd(drive);

    //irq_wait(floppy_irq);
    uint8_t st0 = 0;
    uint8_t cyl = 0;
    floppy_sense_interrupt(&st0, &cyl);

    if(!(st0 & 0x20))
        floppy_recalibrate(drive);
}