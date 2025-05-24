/*
    squeeze.c

    Author: Alan Bailey
    Date: May 20, 2025
    Exercise 2-4

    Given a string s and r, remove any characters that appear in r from s.
*/

#include <stdio.h>

#define STRING_MAX  32  /* Max chars in a string */

void get_line(char s[], char reason[]);
void squeeze(char s[], char r[]);

int main(void) {
    
    char s[STRING_MAX];
    char r[STRING_MAX];
    
    get_line(s, "Enter a string (32 characters max): ");
    get_line(r, "Enter all characters to remove from the previous string: ");
    squeeze(s, r);
    return 0;
}

void get_line(char s[], char reason[]) {

    int c;
    int i;
    printf("%s", reason);
    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }

    s[i] = '\0';
}

/*
    void squeeze(char s[], char r[])

    From the provided string s, remove all characters that appear in the 
    removal string r.

    For example: if s == "hello world" and r == "el", then the output of s
    will be "ho word".

    Procedure:

    Loop through each character of s.
    For each character c in s, loop through each character k in r.
        if c == k, we must remove c from s.
            all characters can be shifted back... is there another way?
            what if there is another string here, z?
                z has its own iterator, z_i
                if c == k... flag squeezing.
                if we are NOT squeezing, then z[z_i++] = s[i], since i
                    naturally increments at loop end.
                then we only have to write once and not shift everything back.

    finally, print z!
*/
void squeeze(char s[], char r[]) {

    char z[STRING_MAX];
    char z_i = 0;

    for (int i = 0; i < STRING_MAX && s[i] != '\0'; i++) {
        int squeezing = 0;
        for (int j = 0; j < STRING_MAX && r[j] != '\0'; j++) {
            if (s[i] == r[j]) {
                squeezing = 1;
            } 
        }
        
        if (!squeezing) {
            z[z_i++] = s[i];
        }
    }

    z[z_i] = '\0';

    printf("The squeezed line is: [%s]\n", z);
}