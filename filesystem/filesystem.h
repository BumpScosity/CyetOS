#pragma once

#include "../lib/typedef.h"

#define MAX_ENTRIES 100
#define SECTOR_SIZE 512
#define NUM_SECTORS 4

// Structure for storing hashtable entries
typedef struct {
    char name[32];          // Name of the entry
    uint32_t sector;        // Starting sector number
    uint16_t count;         // Number of sectors
} Entry;

int disk_read(const char* name, void* data);
int disk_write(const char* name, void* data, uint16_t count);