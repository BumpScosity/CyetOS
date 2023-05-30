#ifndef LIB_H
#define LIB_H

char upper(char c);
void outb(unsigned short port, unsigned char value);
int cmpchar(const char *c1, const char c2);
int cmpstr(const char* str1, const char* str2);

#endif // LIB_H