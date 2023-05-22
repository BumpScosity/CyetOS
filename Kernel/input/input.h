#ifndef INPUT_H
#define INPUT_H

void handle_backspace(int *row, int *col, int color);
void handle_arrow_left(int *row, int *col);
void handle_arrow_right(int *row, int *col);
void handle_characters(int *row, int *col, int color,
 int shift, unsigned char key, const char *ascii_map, const int ascii_map_size);

#endif // INPUT_H
