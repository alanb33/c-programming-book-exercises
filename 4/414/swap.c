/*
    swap.c

    Alan Bailey
    June 3, 2025
    Exercise 4-14

    Write a processor macro to interchange two operands of type t.
*/

#include <stdio.h>

// The \ at the end of the line extends the preprocessor macro to the next
#define swap(t, x, y) { \
    t = x;              \
    x = y;              \
    y = t;              \
}

int main(void) {
    int t;
    int x = 10;
    int y = 2;
    swap(t, x, y);

    float z;
    float i = 3.92;
    float j = 9.9999;
    swap(z, i, j);

    printf("x and y are now %d and %d\n", x, y);
    printf("i and j are now %f and %f\n", i, j);
    return 0;
}