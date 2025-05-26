/*
    itoa.c

    Alan Bailey
    May 25, 2025

    In a two's complement number system, the itoa definition provided in the C
    Handbook does not handle the largest negative number, defined as 
    -(2 ^ wordsize-1). Why not? And rewrite!
*/

/*
    1. So, why not? In the declaration of the function, we see the following
    few lines:

    if ((sign = n) < 0)
        n = -n;

    Assume a wordsize of 8. This means that the largest negative number is
    -128, and the largest positive number, conversely, is 127 (because 0 will
    count as one of the numbers.) There's the problem! Flipping the number
    directly works in all causes but the largest negative number because the
    largest negative number will cause an overflow error.
*/

#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STR_LEN     32

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {

    int n = INT_MIN;
    char s[STR_LEN];
    
    itoa(n, s);

    printf("The output of the itoa call using %d is %s.\n", n, s);

    return 0;
}

/*
    itoa(int n, char s[])

    Given an integer n, convert it to its string representation.

    Challenge 3-4: Ensure this works with the largest negative number!
*/
void itoa(int n, char s[]) {
    int8_t sign = n < 0 ? -1 : 1;

    int8_t i = 0;
    do {
        int value = n % (sign * 10);    // Neg modulo works on neg number
        value = value < 0 ? -value : value; // Get abs value for char addition
        s[i++] = value + '0';
    } while ((n /= 10) != 0);   // Neg number / 10 = neg number

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