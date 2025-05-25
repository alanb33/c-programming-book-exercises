/*
    binsearch.c
    
    Author: Alan Bailey
    Date: May 24, 2025
    Exercise 3-1

    Rewrite the binsearch function found on page 54 to use one test rather
    than two.

    The exercise also specified measuring the time difference --
    unfortunately, it seems I can't use clock(), my processor may be too fast!

    I'll revisit time complexity at a later date.
*/

/*
    int binsearch(int x, int v[], int n)

    Given a number array v of length n, find the index of x.
*/

#include <stdio.h>

#define NUM_LEN 12  /* Length of the int array to examine */

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main(void) {
    
    int x = 500;
    int v[NUM_LEN] = {1, 9, 33, 50, 99, 120, 133, 149, 170, 213, 302, 500};
    
    int index = binsearch2(x, v, NUM_LEN);

    if (index > 0) {
        printf("Item %d can be found at index %d\n", x, index);
    } else {
        printf("item %d is not within the array.\n", x);
    }
    
    return 0;
}

/*
    binsearch

    The solution provided on page 54 of Kernigan & Ritchie's book.
*/
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid + 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/*
    binsearch2

    My solution; two conditionals rather than three in exchange for
    testing the value of v[mid] in the terminator. There is one final
    test afterwards to confirm if we settled on the mid or if we just
    simply went out of range.
*/
int binsearch2(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high && x != v[mid] && mid != (low + high) / 2) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    // If we're here, either low > high (no match)  or x == v[mid], so...

    if (x == v[mid]) {
        return mid;
    }
    return -1;  // No match
}