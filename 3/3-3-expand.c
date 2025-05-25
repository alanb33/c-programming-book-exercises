/*
    expand.c

    Alan Bailey
    May 25, 2025

    Write a function expand(s1, s2) that expands shorthand notations like a-z
    in s1 into equivalent complete abc...xyz in s2. Allow for casts of either
    case and digits.

    Handle cases like a-b-c and a-z0-9 and -a-z.

    Arrange that a leading or trailing - is taken literally.
*/

#include <ctype.h>
#include <stdio.h>

#define MAX_LEN         256 /* max length for lines */
#define INPUT_LEN       32  /* max length for input */
#define ALPHABET_LEN    26

void expand(char input[], char output[]);
void getline(char input[]);

int main(void) {
    
    char input[MAX_LEN];
    char output[MAX_LEN];

    getline(input);
    
    printf("Input:  [%s]\n", input);
    expand(input, output);
    printf("Output: [%s]\n", output);

    return 0;
}

void getline(char input[]) {
    int c;
    int i;
    for (i = 0; i < INPUT_LEN && (c = getchar()) != EOF; i++) {
        input[i] = c;
    }

    input[i] = '\0';
}

/*
    Expands a-z, A-Z, 0-9 (and variations of) into abc...xyz, 012...789, etc.
*/
void expand(char input[], char output[]) {
    int start_i, end_i;
    int hyphenating, expanding = 0;
    int output_i = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        // Get the position of the latest character
        if (isalpha(c) || isdigit(c)) {
            if (!hyphenating) {
                start_i = i;
            } else {
                end_i = i;
                hyphenating = 0;
                expanding = 1;
            }
        }

        // Check for valid hyphen placement
        if (c == '-') {
            char c = input[start_i];
            if (start_i == i - 1 && (isalpha(c) || isdigit(c))) {
                hyphenating = 1;
            } else {
                hyphenating = 0;
            }
        }

        if (expanding) {
            // evaluate that operands are valid before we get into the loops
            char start_c = input[start_i];
            char end_c = input[end_i]; 

            // Don't evaluate if start comes after the end.
            if (start_c >= end_c) {
                expanding = 0;
            }

            // Confirm they're the same type
            if ((isalpha(start_c) && isdigit(end_c))
                || (isdigit(start_c) && isalpha(end_c))) {
                expanding = 0;
            }

            // Don't evaluate if alphabetical chars are of different types.
            if (isalpha(start_c) && isalpha(end_c)) {
                int diff = end_c - start_c;
                if (diff > ALPHABET_LEN || diff < 0) {
                    // if start is lower (65) and end (97) is upper, 32
                    // if start is upper (97) and end (65) is lower, -32.
                    expanding = 0;
                }
            }
        }

        // Do expansion if valid state
        if (expanding) {
            char start_c = input[start_i];
            char end_c = input[end_i];
            char differentiator;
            if (isalpha(start_c)) {
                if (isupper(start_c)) {
                    differentiator = 'A';
                } else {
                    differentiator = 'a';
                }
            } else {
                differentiator = '0';
            }

            int ex_start_i = start_c - differentiator;
            int ex_end_i = end_c - differentiator;

            output_i--; // Start at the hyphen position
            for (int j = ex_start_i + 1; j <= ex_end_i; j++, output_i++) {
                output[output_i] = differentiator + j;
            }

            // Watch for a case of future expansion
            if (input[end_i + 1] == '-') {
                hyphenating = 1;
                start_i = end_i;
            }

            expanding = 0;
            continue;   // early skip to avoid the end statement
        }

        // This will only evaluate if the expansion state fails.
        output[output_i] = input[i];
        output_i++;
    }

    output[output_i] = '\0';
}