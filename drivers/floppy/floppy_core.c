#include "internal.h"
#include "floppy.h"

/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#Reinitialization
 */
int floppy_init(){
    floppy_write_cmd(FLOPPY_VERSION);
    if(floppy_read_data() != 0x90)
        return -1;

    floppy_configure(true, true, false, 8);
    floppy_lock();
    floppy_reset(true);

    // floppy_recalibrate all drives
    for(int i = 0; i < 4; i++){
        floppy_recalibrate(i);
    }

    return 0;
}

void floppy_rw_command(int drive, int head, int cyl, int sect, int EOT, uint8_t *st0, uint8_t *st1, uint8_t *st2,
                       int *headResult, int *cylResult, int *sectResult, int command) {
    int MT = 0x80; // set to 0x80 to enable multi-track, or 0 to disable
    int MFM = 0x40; //set to 0x40 to enable magnetic-encoding-mode, or 0 to disable. According to the wiki this should always be on

    // Read command = MT bit | MFM bit | 0x6
    floppy_write_cmd( MFM | MT | command);

    // First parameter byte = (head number << 2) | drive number (the drive number must match the currently selected drive!)
    floppy_write_cmd((head << 2) | drive);

    // Second parameter byte = cylinder number
    floppy_write_cmd(cyl);

    // Third parameter byte = head number (yes, this is a repeat of the above value)
    floppy_write_cmd(head);

    // Fourth parameter byte = starting sector number
    floppy_write_cmd(sect);

    // Fifth parameter byte = 2 (all floppy drives use 512bytes per sector)
    floppy_write_cmd(2);

    // Sixth parameter byte = EOT (end of track, the last sector number on the track)
    floppy_write_cmd(EOT);

    // Seventh parameter byte = 0x1b (GAP1 default size)
    floppy_write_cmd(0x1b);

    // Eighth parameter byte = 0xff (all floppy drives use 512bytes per sector)
    floppy_write_cmd(0xff);

    uint8_t RQM;
    uint8_t MSR;
    while(true){
        MSR = inb(FLOPPY_MAIN_STATUS_REGISTER);
        RQM = (MSR & 0x80) > 1;
        //kprint(toString(MSR, 2));
        sleep(10);
        if(RQM)
            break;
    }

    // First result byte = st0 status register
    *st0 = floppy_read_data();

    // Second result byte = st1 status register
    *st1 = floppy_read_data();

    // Third result byte = st2 status register
    *st2 = floppy_read_data();

    // Fourth result byte = cylinder number
    *cylResult = floppy_read_data();


    // Fifth result byte = ending head number
    *headResult = floppy_read_data();

    // Sixth result byte = ending sector number
    *sectResult = floppy_read_data();

    // Seventh result byte = 2
    floppy_read_data();
}