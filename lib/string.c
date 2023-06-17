#include "lib.h"
#include "typedef.h"

int strncmp(const char* str1, const char* str2, unsigned int num) {
    for (unsigned int i = 0; i < num; i++) {
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
        if (str1[i] == '\0')
            return 0;
    }
    return 0;
}

char* strcpy(char* dest, const char* src) {
    char* original_dest = dest;  // Store the original destination pointer

    // Copy characters from source to destination until the null terminator is encountered
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    // Append null terminator at the end of the destination string
    *dest = '\0';

    return original_dest;  // Return the original destination pointer
}

size_t strlen(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void reverseString(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* intToString(int num) {
    char *str = "\0";
    int index = 0;
    int temp;

    if (num == 0) {
        str[index++] = '0';
        str[index] = '\0';
        return str;
    }

    if (num < 0) {
        str[index++] = '-';
        temp = -num;
    } else {
        temp = num;
    }

    while (temp != 0) {
        str[index++] = '0' + (temp % 10);
        temp /= 10;
    }

    str[index] = '\0';

    if (num < 0) {
        reverseString(str + 1, index - 1);
    } else {
        reverseString(str, index);
    }

    return str;
}

char* strncpy(char* dest, const char* src, size_t n) {
    char* destStart = dest;
    while (*src && n > 0) {
        *dest++ = *src++;
        n--;
    }
    while (n > 0) {
        *dest++ = '\0';
        n--;
    }
    return destStart;
}

int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;
}
