#include <stdio.h>

/*
    getline.c

    Alan Bailey

    Custom getline function that terminates on newline in addition to EOF.
*/

void getline(char s[], unsigned len) {
    int i = 0;
    int c;
    while (i < len && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }

    // Terminate string
    s[i] = '\0';
}