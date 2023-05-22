#ifndef CORE_H
#define CORE_H

#define true 1
#define false 0
#define row cursor->Row
#define col cursor->Col
#define bool int

void outb(unsigned short port, unsigned char value);

typedef struct {
    int Row;
    int Col;
} CursorPosition;

#endif // CORE_H 