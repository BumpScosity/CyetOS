#pragma once

#include "../lib/typedef.h"

void* kalloc(size_t typeSize, const char* name);
void kfree(const char *name);
void *kget(const char *name);
void kset(const char* name, const void* value, size_t size);

size_t kMemUsage();