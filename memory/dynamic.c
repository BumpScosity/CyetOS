#include "../lib/typedef.h"
#include "../lib/lib.h"

#define MAX_NAME_LENGTH 50
#define MAX_ENTRIES 10000

typedef struct {
    char name[MAX_NAME_LENGTH];
    void* address;
    size_t size;
} NameAddressPair;

NameAddressPair nameAddressMap[MAX_ENTRIES];
size_t mapSize = 0;
unsigned char* nextAvailableAddress = (unsigned char*)0x10000;  // Starting address for allocation

void* kalloc(size_t typeSize, const char* name) {
    if (mapSize >= MAX_ENTRIES) {
        return NULL;
    }

    void* address = (void*)nextAvailableAddress;
    nextAvailableAddress += typeSize;

    nameAddressMap[mapSize].address = address;
    strncpy(nameAddressMap[mapSize].name, name, MAX_NAME_LENGTH);
    nameAddressMap[mapSize].size = typeSize;
    mapSize++;

    return address;
}

void kfree(void* address) {
    for (size_t i = 0; i < mapSize; i++) {
        if (nameAddressMap[i].address == address) {
            unsigned char* ptr = (unsigned char*)nameAddressMap[i].address;
            size_t size = nameAddressMap[i].size;
            while (size > 0) {
                *ptr++ = '\0';
                size--;
            }

            // Shift subsequent entries to fill the gap
            for (size_t j = i; j < mapSize - 1; j++) {
                nameAddressMap[j] = nameAddressMap[j + 1];
            }

            mapSize--;
            nextAvailableAddress -= nameAddressMap[i].size;
            nameAddressMap[i].size = 0;
            break;
        }
    }
}

void* kget(const char* name) {
    for (size_t i = 0; i < mapSize; i++) {
        if (strncmp(nameAddressMap[i].name, name, MAX_NAME_LENGTH) == 0) {
            return nameAddressMap[i].address;
        }
    }
    return NULL;
}

void kset(const char* name, const void* value, size_t size) {
    for (size_t i = 0; i < mapSize; i++) {
        if (strncmp(nameAddressMap[i].name, name, MAX_NAME_LENGTH) == 0) {
            unsigned char* dest = (unsigned char*)nameAddressMap[i].address;
            size_t blockSize = nameAddressMap[i].size;
            size_t copySize = (size < blockSize) ? size : blockSize;
            nameAddressMap[i].size = copySize;
            memcpy(dest, value, copySize);
            break;
        }
    }
}

size_t kMemUsage() {
    size_t totalSize = 0;
    for (size_t i = 0; i < mapSize; i++) {
        totalSize += nameAddressMap[i].size;
    }
    return totalSize;
}