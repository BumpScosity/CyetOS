#include "input.h"
#include "../vga.h"

void handle_arrow_left(int *row, int *col) {
    (*col)--;
    move_cursor(*row, *col);
}

void handle_arrow_right(int *row, int *col) {
    (*col)++;
    move_cursor(*row, *col);
}