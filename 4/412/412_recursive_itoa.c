/* 
    recursive_itoa.c

    Alan Bailey
    May 30, 2025
    Exercise 4-12

    Write a recursive version of itoa that converts an integer into a string
    by calling a recursive routine.

    Extra: I modified this to work with the largest negative number as well.
        -A
*/

#include <limits.h>
#include <stdint.h>
#include <stdio.h>

void itoa_recursive(long long int n);

int main(void) {
    itoa_recursive(LLONG_MIN);
    putchar('\n');
    itoa_recursive(LONG_MIN);
    putchar('\n');
    itoa_recursive(INT_MIN);
    putchar('\n');
    itoa_recursive(CHAR_MIN);
    putchar('\n');
    return 0;
}

/*
    itoa_recursive

    Given any integer n, print its digits as characters, including the
    negative sign of the digit if it exists.

    n is a register because it's used a few times. Probably unncessary!
        -A
*/
void itoa_recursive(long long int n) {
    int8_t sign = n < 0 ? -1 : 1;

    // Preface the number with a minus if it's negative
    if (sign < 0) {
        putchar('-');
    }

    // The digit formula will get the modulo and then make it positive.
    int8_t digit = (sign * (n % (sign * 10))) + '0';
    
    // As long as n / 10 isn't 0, continue with a new n!
    if (n / 10) {
        long long int div_n = n / 10;

        /*
            div_n will only ever be negative on the first invocation of
            the function. This makes it safe to use with the largest
            negative numbers and avoids having to use a separate variable
            to track if we're on the first digit or not.
        */
        if (div_n < 0) {
            div_n = -div_n;
        }
        
        itoa_recursive(div_n);
    }
    
    // This section only runs after recursion finished
    putchar(digit);
}