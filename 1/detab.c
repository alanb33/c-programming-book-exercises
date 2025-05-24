/*
    detab.c

    Author: Alan Bailey
    Date: May 17, 2025
    Exercise 1-20

    given an input s, replace any occurance of \t with a fixed number of spaces.
*/

/*
    Plan

    1. read a stream of input from the user until EOF.
    2. step through the string. if \t is encountered at any point, then insert
        a fixed number of spaces.

        reading a string of input

    declare a variable to store the character to be examined, c.
    while (c != EOF)
        if c == '\t'...
            putchar(' ') a number of timed equal to the fixed length.

    print the string.
*/

/*
    tab amount calculation needs to be modified.

    declare a variable to be reset whenever it reaches 8.
    int col = 1

    with every added character, if it is not \t, increment col.
        if col reaches 8, reset to 1.
    if character is \t, then it's time to calculate the tab length required.
    TABLENGTH - col = number of spaces to append.
*/

#include <stdio.h>

#define TABLENGTH 8     /* The number of spaces in a tab stop. */

int main()
{
    int c;
    int col = 1;
    while ((c = getchar()) != EOF) {
        /* insert a number of spaces equal to the TABLENGTH - col count. */
        if (c == '\t') {
            int i = 0;
            int diff = TABLENGTH - col;
            while (i <= diff) {
                putchar(' ');
                ++i;
            }
            col = 1;
        
        } else {
            if (c == '\n') {
                // So col can increment properly
                col = 0;
            }
            putchar(c);
            /* increment and reset col count if necessary. */
            ++col;
            if (col > TABLENGTH) {
                col = 1;
            }
        };
    };
    return 0;
}