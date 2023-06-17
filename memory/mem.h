#pragma once

#include "../lib/typedef.h"

typedef struct {
    uint16_t lower_size;
    uint16_t upper_size;
} mem_t;

mem_t memget(void);
mem_t upper_memget(void);

void* memcpy(void* dest, const void* src, size_t size);
void* memset(void* dest, unsigned char val, size_t count);