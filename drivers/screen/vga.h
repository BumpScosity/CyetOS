#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void move_cursor(int row, int col);
void kPrintChar(const char s);
void kPrintCharCol(const char s, const int c);
void kprint(const char *s);
void kprintloc(const char *s, int x, int y);
void kprintLC(const char *s, int x, int y, const int c); // LC stands for location, and color.
void kprintcol(const char *s, const int c);

#endif // VGA_H