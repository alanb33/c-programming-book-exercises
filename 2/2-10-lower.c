/*
    lower.c

    Author: Alan Bailey
    Date: May 24, 2025
    Exercise 2-10

    Challenge 2-10: Write a function to lower uppercase letters to
    lowercase letters by using a conditional statement (?:) instead of an
    if-else statement.
*/

#include <stdio.h>

#define LINE_LEN    32  /* Max line length */

void lower(char s[]);

int main(void) {
    char s[LINE_LEN] = "HELLO WORLD";
    lower(s);
    printf("Lowercase: %s\n", s);
    return 0;
}

/*
    lower(char s[])

    Given a string s, convert any uppercase letters to lowercase. We'll use a
    conditional statement (?:) instead of an if-else.
*/

void lower(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] + 32 : s[i];
    }
}
