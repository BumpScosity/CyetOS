#include "mem.h"

mem_t memget(){                     // These values better be protected somehow... TODO
    mem_t* mem = (mem_t*)0x5000;
    return *mem;
}

mem_t upper_memget () {
    mem_t* mem = (mem_t*)0x5100;
    return *mem;
}

void* memcpy(void* dest, const void* src, size_t size) {
    unsigned char* destPtr = (unsigned char*)dest;
    const unsigned char* srcPtr = (const unsigned char*)src;

    for (size_t i = 0; i < size; i++) {
        destPtr[i] = srcPtr[i];
    }

    return dest;
}

void* memset(void* dest, unsigned char val, size_t count) { 
    /* Indicate failure */
    if (!dest)
        return NULL;

	unsigned char* destC = (unsigned char*)dest;
	int i;
	for (i = 0; i < count; i++)
		destC[i] = val;
	return dest;
}