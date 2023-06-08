#include "mem.h"

mem_t memget(){                     // These values better be protected somehow... TODO
    mem_t* mem = (mem_t*)0x5000;
    return *mem;
}

mem_t upper_memget () {
    mem_t* mem = (mem_t*)0x5100;
    return *mem;
}