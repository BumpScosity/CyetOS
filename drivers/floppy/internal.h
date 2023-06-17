#pragma once

#include "../../lib/typedef.h"
#include "../screen/vga.h"
#include "../../lib/lib.h"

void lba_2_chs_f(int sectors_per_track, uint32_t lba, uint16_t* cyl, uint16_t* head, uint16_t* sector);
void lba_2_chs(uint32_t lba, uint16_t* cyl, uint16_t* head, uint16_t* sector);
unsigned int floppy_detect_drives();
uint8_t get_drive_type();
void floppy_write_cmd(char cmd);
void floppy_sense_interrupt(uint8_t *st0, uint8_t *cyl);
void drive_select(int drive);
void specify();
void floppy_reset(int firstTime);
void floppy_configure(int implied_seek, int FIFO, int drive_polling_mode, int threshold);
void floppy_lock();
void floppy_recalibrate(uint8_t  drive);
void floppy_rw_command(int drive, int head, int cyl, int sect, int EOT, uint8_t *st0, uint8_t *st1, uint8_t *st2,
                       int *headResult, int *cylResult, int *sectResult, int command);
unsigned char floppy_read_data();