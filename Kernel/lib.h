#ifndef LIB_H
#define LIB_H

typedef struct {
    char character;
    int color;
} VGA_cell;

char upper(char c);
void outb(unsigned short port, unsigned char value);

#endif // LIB_H 