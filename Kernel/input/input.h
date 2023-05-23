#ifndef INPUT_H
#define INPUT_H

void handle_characters(int *row, int *col, int color,
 int shift, unsigned char key, const char *ascii_map, const int ascii_map_size);
void handle_backspace(int *row, int *col, int color);

#endif // INPUT_H
