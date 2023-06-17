#pragma once

#include "../../lib/typedef.h"
#include "../../kernel/port_io.h"

#include "ISA_DMA.h"

enum FloppyRegisters
{
    FLOPPY_STATUS_REGISTER_A                = 0x3F0, // read-only
    FLOPPY_FLOPPY_STATUS_REGISTER_B         = 0x3F1, // read-only
    FLOPPY_DIGITAL_OUTPUT_REGISTER          = 0x3F2,
    FLOPPY_TAPE_DRIVE_REGISTER              = 0x3F3,
    FLOPPY_MAIN_STATUS_REGISTER             = 0x3F4, // read-only
    FLOPPY_DATARATE_SELECT_REGISTER         = 0x3F4, // write-only
    FLOPPY_DATA_FIFO                        = 0x3F5,
    FLOPPY_DIGITAL_INPUT_REGISTER           = 0x3F7, // read-only
    FLOPPY_CONFIGURATION_CONTROL_REGISTER   = 0x3F7  // write-only
};


enum FloppyCommands
{
    FLOPPY_READ_TRACK =                 2,	// generates IRQ6
    FLOPPY_SPECIFY =                    3,      // * set drive parameters
    FLOPPY_SENSE_DRIVE_STATUS =         4,
    FLOPPY_WRITE_DATA =                 5,      // * write to the disk
    FLOPPY_READ_DATA =                  6,      // * read from the disk
    FLOPPY_RECALIBRATE =                7,      // * seek to cylinder 0
    FLOPPY_SENSE_INTERRUPT =            8,      // * ack IRQ6, get status of last command
    FLOPPY_WRITE_DELETED_DATA =         9,
    FLOPPY_READ_ID =                    10,	// generates IRQ6
    FLOPPY_READ_DELETED_DATA =          12,
    FLOPPY_FORMAT_TRACK =               13,     // *
    FLOPPY_DUMPREG =                    14,
    FLOPPY_SEEK =                       15,     // * seek both heads to cylinder X
    FLOPPY_VERSION =                    16,	// * used during initialization, once
    FLOPPY_SCAN_EQUAL =                 17,
    FLOPPY_PERPENDICULAR_MODE =         18,	// * used during initialization, once, maybe
    FLOPPY_CONFIGURE =                  19,     // * set controller parameters
    FLOPPY_LOCK =                       20,     // * protect controller params from a reset
    FLOPPY_VERIFY =                     22,
    FLOPPY_SCAN_LOW_OR_EQUAL =          25,
    FLOPPY_SCAN_HIGH_OR_EQUAL =         29
};


enum FLOPPYSpeeds{
    KB500 = 0,
    MB1 = 3
};

unsigned int floppy_detect_drives();
int floppy_init();
int floppy_read(int drive, uint32_t lba, void* address, uint16_t count);
int floppy_write(int drive, uint32_t lba, void* address, uint16_t count);