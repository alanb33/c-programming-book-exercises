/*
    atof, scientific notation expansion
    see atof.c for primary code

    Alan Bailey
    May 27, 2025
    Exercise 4-2
*/

#include <stdio.h>

#define LINE_LENGTH 1000 /* max length of lines */

extern void getline(char s[], unsigned int len);
extern double atof_sci(char s[]);

int main(void) {

    char s[LINE_LENGTH];
    printf("Input:  ");
    getline(s, LINE_LENGTH);
    double result = atof_sci(s);
    printf("Output: %f\n", result);

    return 0;
}