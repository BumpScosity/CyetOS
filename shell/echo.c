#include "cmd.h"
#include "../drivers/screen/vga.h"

void echo(const char *s) {
    int *xy = (int*)0x99000;

    // Find the index of the first space character
    char output[256];
    int space_index = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            space_index = i;
            break;
        }
    }

    // Extract the second string starting from the next character after the space
    if (space_index != -1) {
        int output_index = 0;
        for (int i = space_index + 1; s[i] != '\0'; i++) {
            output[output_index] = s[i];
            output_index++;
        }
        output[output_index] = '\0';
        kprint(output);
    } else {
        output[0] = '\0'; // No second string found
    }
}