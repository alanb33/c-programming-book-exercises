/*
    htoi.c

    Alan Bailey, May 19, 2025

    Given a string in the format 0xNNNNNNNN, where N is one or more hex
    digits in the range of 0 to F, convert to integer equivalent. 0x/0X are
    an optional component and it should work with the following:

    0x12345678  
    0x1234
    1234

    Note to self - hex is like binary and read right to left. Like octal as
    well, the value is calculated by value^place, starting at 0.
*/

/*
    Abstract

    vars
        ending_index    the index to stop reading at. default 0.
        max_length      the maxiumum length of the string. default 8.
        place           the exponent to use against the value. default 0.
        product         the running product of the calculation. default 0.

    1. Receive a string.
    2. Perform validation.
        a. First, ensure the string is, at minimum, 3 characters in length.
            This will ensure that we have at least one number in the event
            that it comes in the format of 0x0 rather than 000.
        b. Next, confirm if the string begins with 0x/0X. If so, move the
            ending index forward to the index afterwards. Max length
            becomes 10 from 8.
                Note: Necessary? Can just cap length to 10
                PS: Was not necessary, can even shorten with artifical \0
        c. Next, validate that all digits are hex-compatible. To do so,
            all digits must be 0-9 or A-F. Capitalization should not
            matter.
        d. While validating digits, also measure length of the string.
            When \0 or \n is encountered, finalize length. If length is
            valid, we can continue.
    3. Calculate value.
        a. Starting at the end of the string, read the value. 0-9 can be
            determined by subtracting char 0 from them. capital letters are
            calcuated with letter - 'A' + 10. lowercase letters instead use
            letter - 'a' + 10.
        b. Get the product of pow(value, place). Sum into product.
        c. Decrement index and increment place.
        d. If index < ending_index, we're done!
*/

#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 10  /* Max length of string */

void get_line(char s[]);
int validate_hex(char s[]);

int main(void) {
    char s[MAX_LEN];

    get_line(s);

    printf("The line is: %s\n", s);

    if (validate_hex(s)) {
        printf("Hex is valid\n");
        // calculate_hex(s)
    } else {
        printf("Hex is invalid\n");
    }

    return 0;
};

void get_line(char s[]) {
    /*
        If getchar encountered a newline, assume we want to end the
        string.
    */

    int c;
    int i;
    int remaining = -1;
    for (i = 0; (i < MAX_LEN) && ((c = getchar()) != EOF) && c != '\n'; i++) {
        s[i] = c;
    };

    // Early termination
    if (s[i] != '\0') {
        s[i] = '\0';
    }
}

/*
    validate_hex

    Returns 1 if valid hex, else 0 for invalid.
*/
int validate_hex(char s[]) {
    size_t len = strlen(s);

    int max_len = 10;
    int end_i = 0;

    // Shorten if we don't have a 0x/0X start
    if (!(s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))) {
        max_len = 8;
        if (len > max_len) {
            return 0;
        }
    } else {
        // Else, set end index to after the 0x/0X
        end_i = 2;
    }

    // Now that max length is confirmed, check length
    if (len > max_len) {
        return 0;
    }

    /*
        Finally, confirm all digits are valid, aka within range of 0-9 and
        case-insensitive within a-f/A-F
    */
    for (int i = len - 1; i >= end_i; --i) {
        if ((s[i] < '0' || s[i] > '9')
            && (s[i] < 'a' || s[i] > 'f')
            && (s[i] < 'A' || s[i] > 'F'))
        {
            return 0;
        }
    }

    return 1;
}
