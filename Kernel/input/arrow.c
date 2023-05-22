#include "input.h"
#include "../lib.h"
#include "../vga.h"

void handle_arrow(int *row, int *col, const char *type) {
    if (strcmp(type, "left") == 0) {(*col)--;}
    else if (strcmp(type, "right") == 0) {(*col)++;}
    move_cursor(*row, *col);
}