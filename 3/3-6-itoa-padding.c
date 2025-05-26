/*
    itoa-padded.c

    Alan Bailey
    May 26, 2025
    Exercise 3-6

    This version of itoa, as copied from 3-4-itoa.c, accepts three arguments,
    where the third arumnet is a minimum field width. The converted number
    will be padded with blanks on the left if necessary to make it wide
    enough.
*/

#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STR_LEN     32

void itoa(int n, char s[], uint8_t w);
void reverse(char s[]);

int main(void) {

    int n = 255;
    char s[STR_LEN];
    uint8_t padding = 8;

    itoa(n, s, padding);

    printf("The output of the itoa call using %d and a minimum padding of %d "
        "is:\n[%s].\n", n, padding, s);

    return 0;
}

/*
    itoa(int n, char s[])

    Given an integer n, convert it to its string representation.

    Challenge 3-4: Ensure this works with the largest negative number!
*/
void itoa(int n, char s[], uint8_t w) {
    int8_t sign = n < 0 ? -1 : 1;

    int8_t i = 0;
    do {
        int value = n % (sign * 10);    // Neg modulo works on neg number
        value = value < 0 ? -value : value; // Get abs value for char addition
        s[i++] = value + '0';
    } while ((n /= 10) != 0);   // Neg number / 10 = neg number

    /*
        I wonder if I'm misunderstanding this -- we're just adding some spaces
        to do padding? I hope this is what the exercise intended. -A
    */
    uint8_t padding = w - i;
    if (padding > 0) {
        while (padding > 0) {
            s[i++] = ' ';
            padding--;
        }
    }

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';

    reverse(s);
}

void reverse(char s[]) {
    int8_t i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}