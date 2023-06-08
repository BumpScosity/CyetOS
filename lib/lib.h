#ifndef LIB_H
#define LIB_H

#include "typedef.h"

char upper(char c);
void outb(unsigned short port, unsigned char value);
void outw(unsigned short port, unsigned short value);
unsigned char inb(unsigned short port);
char lower(char c);
int strncmp(const char* str1, const char* str2, unsigned int num);
char* strcpy(char* dest, const char* src);
size_t strlen(const char* str);
char* intToString(int num);
void sleep (int ticks);

#endif // LIB_H