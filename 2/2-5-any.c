/*
    any.c

    Author: Alan Bailey
    Date: May 21, 2025
    Exercise 2-5

    The function any(s1, s2) which returns the first location in s1 where any
    character in s2 occurs, or -1 if s1 contains no characters.
*/

/*
    Plan

    1. Get a line, s1. this will be the line to check against s2.
    2. Get s2, a series of characters to search against.
    3. within any, loop over each character of s1.
        a. For each character of s1, loop over each character of s2.
        b. if s1[i] matches s2[j], then return i.
        c. if s1[i] == '\0', return -1.

    easy!
*/

#include <limits.h>
#include <stdio.h>

signed char any(char main_string[], char filter[]);
void get_line(char s[]);

int main(void) {
    char main_string[SCHAR_MAX];
    char filter[SCHAR_MAX];

    printf("Enter a string (max %d characters): ", SCHAR_MAX);
    get_line(main_string);

    printf("Enter a filter to check against (max %d characters): ", SCHAR_MAX);
    get_line(filter);

    int i = any(main_string, filter);
    if (i > -1) {
        printf("The first match is at index %d.\n", i);
    } else {
        printf("No characters in the main string match the filter "
            "[%s].\n", filter);
    }

    return 0;
}

/*
    void any(char main_string[], char filter[])

    Loops over main_string and returns the first index where any character 
    from filter appears.

    Returns -1 if no matches.

    PS: Why a signed char? The program as-is won't go over a str that's 127
    characters in length. We need to use a signed char here because it was
    specified to return -1. -A
*/
signed char any(char main_string[], char filter[]) {
    for (int i = 0; i < SCHAR_MAX
 && main_string[i] != '\0'; i++) {
        for (int j = 0; j < SCHAR_MAX
     && filter[j] != '\0'; j++) {
            if (main_string[i] == filter[j]) {
                return i;
            }
        }
    }

    return -1;
}

/*
    void get_line(char s[])

    A helper function to get a line from user input. Terminates on EOF or 
    on newline.
*/
void get_line(char s[]) {
    int c;
    int i;
    for (i = 0; i < SCHAR_MAX
 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }

    // Terminate any unused space. At worst, this just overwrites the \0.
    s[i] = '\0';
}