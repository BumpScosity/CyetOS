#include "lib.h"
#include "typedef.h"
#include "../drivers/screen/vga.h"

char upper(char c) {
    switch(c) {
        case '1':
            return '!';
        case '2':
            return '@';
        case '3':
            return '#';
        case '4':
            return '$';
        case '5':
            return '%';
        case '6':
            return '^';
        case '7':
            return '&';
        case '8':
            return '*';
        case '9':
            return '(';
        case '0':
            return ')';

        case ',':
            return '<';
        case '.':
            return '>';
        case '-':
            return '_';
        case '=':
            return '+';
        case ';':
            return ':';
        case '\\':
            return '|';
        case '\'':
            return '\"';
        case '[':
            return '{';
        case ']':
            return '}';
        case '`':
            return '~';
        case '/':
            return '?';

        default:
            if (c >= 'a' && c <= 'z') {
                return c - ('a' - 'A');
            }
    }
    return c;
}


char lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        // Convert uppercase letter to lowercase by adding the ASCII offset
        return c + ('a' - 'A');
    }
    else {
        return c; // Return as-is if not an uppercase letter
    }
}