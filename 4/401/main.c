#include <stdio.h>

extern void getline(char s[], unsigned len);
extern int strindex(char s[], char t[]);

#define LINE_LENGTH 1000    /* Max string length */

int main(void) {
    printf("Input: ");
    char s[LINE_LENGTH];
    getline(s, LINE_LENGTH);

    printf("Pattern to match: ");
    char pattern[LINE_LENGTH];
    getline(pattern, LINE_LENGTH);

    printf("Pattern index %d", strindex(s, pattern));
}