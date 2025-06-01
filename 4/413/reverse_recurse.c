/*
    reverse_recurse.c

    Alan Bailey
    June 1, 2025
    Exercise 4-13

    Write a recursive version of reverse(s), which reverses the string s in
    place.
*/

#include <string.h>

void reverse(char s[]);
void reverse_recurse(char s[], unsigned int start, unsigned int end);

/*
    This is a facade function that removes the caller from needing to provide
    the initial start and end indices on the assumption that we want to 
    reverse the full string.
*/
void reverse(char s[]) {
    reverse_recurse(s, 0, strlen(s) - 1);
}

/*
    A recursive reversal that requires the caller to specify start and end
    indices.
*/
void reverse_recurse(char s[], unsigned int start, unsigned int end) {
    // Terminator; if the start index is >= end index, we're done.
    if (start >= end) {
        return;
    }

    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;

    reverse_recurse(s, ++start, --end);
}