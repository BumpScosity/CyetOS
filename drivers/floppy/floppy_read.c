#include "internal.h"
#include "floppy.h"

/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#The_Proper_Way_to_issue_a_command
 */
unsigned char floppy_read_data() {

    int i; // do timeout, 60 seconds
    for(i = 0; i < 600; i++) {
        sleep(1); // sleep 10 ms
        if(0x80 & inb(FLOPPY_MAIN_STATUS_REGISTER)) {
            return inb(FLOPPY_DATA_FIFO);
        }
    }
    kprint("floppy_read_data: timeout");
    return 0; // not reached
}

// Floppy Commands


int floppy_read(int drive, uint32_t lba, void* address, uint16_t count){
    initFloppyDMA((uint32_t) address, count);

    drive_select(drive);

    uint16_t cyl;
    uint16_t head;
    uint16_t sector;
    lba_2_chs(lba, &cyl, &head, &sector);

    int EOT = 19;

    uint8_t st0;
    uint8_t st1;
    uint8_t st2;
    int cylOut;
    int headOut;
    int sectOut;


    for(int i = 0; i < 20; i++){

        prepare_for_floppyDMA_read();

        floppy_rw_command(drive, head, cyl, sector, EOT, &st0, &st1, &st2, &headOut, &cylOut, &sectOut, FLOPPY_READ_DATA);

        int error = 0;

        if(st0 >> 6 == 2){error = 1;}
        if(st1 & 0x80) {error = 1;}
        if(st0 & 0x08) {error = 1;}
        if(st0 >> 6 == 3){error = 1;}
        if(st1 & 0x20) {error = 1;}
        if(st1 & 0x10) {error = 1;}
        if(st1 & 0x04) {error = 1;}
        if((st1|st2) & 0x01) {error = 1;}
        if(st2 & 0x40) {error = 1;}
        if(st2 & 0x20) {error = 1;}
        if(st2 & 0x10) {error = 1;}
        if(st2 & 0x04) {error = 1;}
        if(st2 & 0x02) {error = 1;}
        if(st1 & 0x02) {error = 2;}
        if(!error){
            return 0;
        }
        if(error > 1){
            return -2;
        }

    }
    return -1;

}