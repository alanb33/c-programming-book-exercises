#include <stdint.h>
#include <string.h>

/*
    strindex(char s[], char t[])

    Given the string s, find any occurance of t. Return the position of the
    rightmost occurance of t in s, or -1 if there is none.
*/
int strindex(char s[], char t[]) {
    int r_match = -1;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == t[0]) {
            uint8_t matches = 0;
            for (int j = 0; j < strlen(t) && s[i+j] == t[j]; j++) {
                matches++;
                if (matches == strlen(t)) {
                    r_match = i;
                }
            }
        }
    }

    return r_match;
}