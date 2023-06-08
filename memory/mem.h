#ifndef MEM_H
#define MEM_H

#include "../lib/typedef.h"

typedef struct {
    uint16_t lower_size;
    uint16_t upper_size;
} mem_t;

mem_t memget(void);
mem_t upper_memget(void);

#endif // MEM_H