#ifndef KERNEL_H
#define KERNEL_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef struct {
    char character;
    int color;
} VGA_cell;

#endif // KERNEL_H