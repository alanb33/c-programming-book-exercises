/*
    Alan Bailey
    June 1, 2025
    Exercise 4-13

    Write a recursive version of reverse(s), which reverses the string s in
    place.

    See reverse_recurse.c for implementation. Utilizes a facade function.
*/

#include <stdio.h>
#include "reverse.h"

int main(void) {
    char s[LINE_LENGTH];
    printf("In:  ");
    getline(s, LINE_LENGTH);
    reverse(s);
    printf("Out: %s\n", s);
    return 0;
}