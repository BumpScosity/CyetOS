#include "../lib/lib.h"

// Constants
#define MAX_ENTRIES 100
#define SECTOR_SIZE 512

// Structure for storing hashtable entries
typedef struct {
    char name[32];          // Name of the entry
    uint32_t sector;        // Sector number
    uint16_t count;         // Number of sectors
} Entry;

// Global variables
Entry hashtable[MAX_ENTRIES];   // Hashtable for storing entries
uint32_t num_entries = 0;       // Number of entries in the hashtable

// Function declarations
void floppy_detect_drives();
int floppy_init();
int floppy_read(int drive, uint32_t lba, void* address, uint16_t count);
int floppy_write(int drive, uint32_t lba, void* address, uint16_t count);

// Function to read data from disk using name
int disk_read(const char* name, void* data) {
    // Find the entry in the hashtable
    for (uint32_t i = 0; i < num_entries; i++) {
        if (strcmp(hashtable[i].name, name) == 0) {
            uint32_t sector = hashtable[i].sector;
            uint16_t count = hashtable[i].count;

            // Read the data from disk
            int drive = 0;  // Assuming the first floppy drive
            return floppy_read(drive, sector, data, count);
        }
    }

    // Entry not found
    return -1;
}

// Function to write data to disk using name
int disk_write(const char* name, void* data, uint16_t count) {
    // Find the entry in the hashtable
    for (uint32_t i = 0; i < num_entries; i++) {
        if (strcmp(hashtable[i].name, name) == 0) {
            // Entry found, overwrite the existing data
            uint32_t sector = hashtable[i].sector;

            // Write the data to disk
            int drive = 0;  // Assuming the first floppy drive
            return floppy_write(drive, sector, data, count);
        }
    }

    // Entry not found, create a new entry
    if (num_entries < MAX_ENTRIES) {
        strncpy(hashtable[num_entries].name, name, sizeof(hashtable[num_entries].name) - 1);
        hashtable[num_entries].name[sizeof(hashtable[num_entries].name) - 1] = '\0';
        hashtable[num_entries].sector = num_entries;  // Assuming sequential sector allocation
        hashtable[num_entries].count = count;

        // Write the data to disk
        int drive = 0;  // Assuming the first floppy drive
        int result = floppy_write(drive, hashtable[num_entries].sector, data, count);
        if (result == 0) {
            num_entries++;  // Increment the number of entries
        }
        return result;
    }

    // Hashtable is full
    return -1;
}