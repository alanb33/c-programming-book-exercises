/*
    itob.c

    Alan Bailey
    May 26, 2025
    Exercise 3-5

    Write the function itob(n, s, b) that converts the integer n into a base b
    character representation in string s. In particular, itob(n, s, 16) 
    formats s as a hexadecimal integer in s.
*/
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 32  /* Max string length */

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void) {
    
    int n = INT_MAX;
    
    char binary[MAX_LEN];
    itob(n, binary, 2);

    char octal[MAX_LEN];
    itob(n, octal, 8);

    char decimal[MAX_LEN];
    itob(n, decimal, 10);

    char hexadecimal[MAX_LEN];
    itob(n, hexadecimal, 16);

    char base6[MAX_LEN];
    itob(n, base6, 6);

    char base12[MAX_LEN];
    itob(n, base12, 12);

    printf("Input:   %d\n", n);
    printf("base-2:  %s\n", binary);
    printf("base-8:  %s\n", octal);
    printf("base-16: %s\n", hexadecimal);
    printf("base-6:  %s\n", base6);
    printf("base-12: %s\n", base12);

    return 0;
}

void itob(int n, char s[], int b) {
    if (b == 10) {
        return;   // Don't bother with base-10 conversion, it's just n
    }

    if (b <= 1) {
        printf("Invalid base for conversion (must be greater than 1)\n");
        return;
    }

    int8_t sign = n < 0 ? -1 : 1;

    int i;
    for (i = 0; ; i++) { // No termination statement means always true
        int rem = n % (sign * b);
        n /= b;
        // Use hex if we're in a base 10+ case
        char c = rem > 9 ? rem - 10 + 'A' : rem + '0';
        s[i] = c;

        /*
            We still want to operate when n == 0, so we terminate here
            instead of in the loop header
        */
        if (n == 0) {
            i++;
            break;
        }
    }

    switch (b) {
        case 8: {   // Octal marker
            s[i] = '0';
            s[i+1] = '\0';
            break;
        }
        case 16: {  // Hex marker
            s[i] = '#';
            s[i+1] = '\0';
            break;
        }
        default: {
            s[i] = '\0';
        }
    }
    
    reverse(s);
}

void reverse(char s[]) {
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}