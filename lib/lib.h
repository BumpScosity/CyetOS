#pragma once

#include "typedef.h"

char upper(char c);
char lower(char c);
int strncmp(const char* str1, const char* str2, unsigned int num);
char* strcpy(char* dest, const char* src);
size_t strlen(const char* str);
char* intToString(int num);
char* strncpy(char* dest, const char* src, size_t n);
int strcmp(const char* str1, const char* str2);
void* memcpy(void* dest, const void* src, size_t n);
void sleep(int ticks);