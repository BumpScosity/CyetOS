#include "../../memory/dynamic.h"
#include "../screen/vga.h"
#include "../screen/vram.h"
#include "../../shell/cmd.h"
#include "../../lib/lib.h"
#include "../../core/prog.h"

#include "keys.h"

void left_arrow(int *pos) {
    int *rc = kget("rc");
    if (rc[1] > 3) { // make sure there is a character to move back to
        rc[1]--;
        move_cursor(rc[0], rc[1]);
        (*pos)--;
    }
}

void right_arrow(int *pos) {
    int *rc = kget("rc");
    if (rc[1] < VGA_WIDTH - 1) { // make sure there is a character to move back to
        rc[1]++;
        move_cursor(rc[0], rc[1]);
        (*pos)++;
    }
}

void enter(char line[256]) {
    int *xy = kget("xy");
    int *rc = kget("rc");
    for (int i = 1; i < 79; i++) {
        draw_pixel(23, i, 0x07);
    }
    int x = xy[0];
    rc[1] = 3;
    xy[1] = 1;
    xy[0] = 23;
    kprint("> ");
    xy[0] = x;
    move_cursor(rc[0], rc[1]);
    parse(line);
}

void ascii(unsigned char key, int shift, const char ascii_map[], char line[256], int *pos) {
    int *xy = kget("xy");
    int *rc = kget("rc");

    int x = xy[0];
    int y = xy[1];
    xy[0] = rc[0];
    xy[1] = rc[1];
    char ascii = ascii_map[key];
    if (ascii && ascii != ' ') {
        if (shift) {
            kPrintChar(upper(ascii));
            line[*pos] = upper(ascii);
            (*pos)++;
            rc[1]++;
        }
        else if (!shift) {
            kPrintChar(ascii);
            line[*pos] = ascii;
            (*pos)++;
            rc[1]++;
        }
    }
    else if (ascii && ascii == ' ') {
        kPrintChar(' ');
        line[*pos] = ' ';
        (*pos)++;
        rc[1]++;
    }

    move_cursor(rc[0], rc[1]);

    xy[0] = x;
    xy[1] = y;
}