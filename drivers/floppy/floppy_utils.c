#include "floppy.h"
#include "internal.h"

/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#Specify
 */
void specify() {
    /*
     * According to the OsDev wiki, these values should change according
     * to failed operation statistics for performance.
     * but, because no1 uses floppies, performance isn't that important
     * so, we'll just use very safe values
     */
    int SRT = 8;
    int HLT = 5;
    int HUT = 0;

    floppy_write_cmd(FLOPPY_SPECIFY);
    floppy_write_cmd(SRT << 4 | HUT);
    floppy_write_cmd(HLT << 1 | 0);


}

/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#Lock
 */
void floppy_lock(){
    floppy_write_cmd(FLOPPY_LOCK);
    floppy_read_data();
}


/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#Sense_Interrupt
 */
void floppy_sense_interrupt(uint8_t *st0, uint8_t *cyl) {
    floppy_write_cmd(FLOPPY_SENSE_INTERRUPT);

    uint8_t RQM;
    while(true){
        RQM = inb(FLOPPY_MAIN_STATUS_REGISTER) & 0x80;
        if(RQM)
            break;
    }

    *st0 = floppy_read_data();
    *cyl = floppy_read_data();

}

/*
 * https://wiki.osdev.org/Floppy_Disk_Controller#Controller_Reset
 */
void floppy_reset(int firstTime){
    uint8_t DOR = inb(FLOPPY_DIGITAL_OUTPUT_REGISTER);
    outb(FLOPPY_DIGITAL_OUTPUT_REGISTER, 0);
    sleep(10);
    outb(FLOPPY_DIGITAL_OUTPUT_REGISTER, DOR & 0x8);
    if(!firstTime){ // check if IRQs were enabled
        //irq_wait(floppy_irq);
    }
}
