#ifndef CORE_H
#define CORE_H

#define true 1
#define false 0
#define bool int

typedef struct {
    int row;
    int col;
} Cursor_Position;

void outb(unsigned short port, unsigned char value);

#endif // CORE_H 