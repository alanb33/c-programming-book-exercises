#include <stdio.h>

/*
    getline.c

    Fill a char with user input. Terminates on newline and EOF.
*/
void getline(char s[], unsigned int len) {
    int c;
    unsigned int i;
    for (i = 0; i < len && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }

    s[i] = '\0';
}