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

#define MAX_LEN     10  /* Max length of string */
#define DO_TESTS    1   /* 1 to run tests, 0 otherwise */

void get_line(char s[]);
int validate_hex(char s[]);

// Test functions
int fail_test(char reason[], int failures);
int run_tests(void);

int main(void) {
    if (DO_TESTS && run_tests()) {
        return 1;
    }

    char s[MAX_LEN];

    get_line(s);

    if (validate_hex(s) == 0) {
        printf("Hex is valid\n");
        // calculate_hex(s)
    } else {
        printf("The specified string is invalid as a hexidecimal input. It "
            "must be presented in the format of: \n\n\t[0x]NNNNNNNN\n\nWhere "
            "0x is optional and NNNNNNNN is 1 to 8 hexadecimal digits in the "
            "range of 0-9 and A-F, case-insensitive.\n");
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

    Returns 0 if valid hex, else 1 for invalid.
*/
int validate_hex(char s[]) {
    size_t len = strlen(s);

    int min_len = 3;
    int max_len = 10;
    int end_i = 0;

    // Shorten if we don't have a 0x/0X start
    if (!(s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))) {
        max_len = 8;
        min_len = 1;
    } else {
        // Else, set end index to after the 0x/0X
        end_i = 2;
    }

    // Now that max length is confirmed, check length
    if (len > max_len || len < min_len) {
        return 1;
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
            return 1;
        }
    }

    return 0;
}

int fail_test(char reason[], int failures) {
    printf("%s", reason);
    return failures + 1;
}

int run_tests(void) {
    /*
        This isn't part of the challenge. However, I wanted to write up some
        test cases for validating hexes. I don't know how to write my own 
        header files just yet, so I can't extract this into a separate file,
        and it's possible that test suite stuff does exist in C that I'm just
        unaware of at this point.

        In any case, here are some test cases. The function will return 0 if
        all is well and 1 if any test case failed. -A
    */
    printf("Running test suite.\n");

    int failure = 0;
    int test_count = 0;

    /*          INVALID HEX LENGTH           */
    /*          With 0x header               */
    // Too long
    if (validate_hex("0x123456789") == 0) {
        failure = fail_test("Test failure: Invalid length (too long) with header was accepted.\n", failure);
    }
    ++test_count;

    // Valid length with 0x header
    if (validate_hex("0x12345678") == 1) {
        failure = fail_test("Test failure: Valid length (8) with header was not accepted.\n", failure);
    }
    ++test_count;

    // Too short
    if (validate_hex("0x") == 0) {
        failure = fail_test("Test failure: Invalid length (too short) with header was accepted.\n", failure);
    }
    ++test_count;

    /*          Without 0x header           */
    if (validate_hex("123456789") == 0) {
        failure = fail_test("Test failure: Invalid length (too long) with header was accepted.\n", failure);
    }
    ++test_count;

    // Valid length with 0x header
    if (validate_hex("12345678") == 1) {
        failure = fail_test("Test failure: Valid length (8) with header was not accepted.\n", failure);
    }
    ++test_count;

    // Too short
    if (validate_hex("") == 0) {
        failure = fail_test("Test failure: Invalid length (too short) with header was accepted.\n", failure);
    }
    ++test_count;

    /*  INVALID CHARACTERS  */
    // Invalid hex codes
    if (validate_hex("0xABCDEFGH") == 0) {
        failure = fail_test("Test failure: Invalid hex characters were accepted.\n", failure);
    }
    ++test_count;

    // Invalid header 1, invalid first character
    if (validate_hex("Ox12345678") == 0) {
        failure = fail_test("Test failure: Invalid header characters were accepted, type 1.\n", failure);
    }
    ++test_count;

    // Invalid header 2, invalid second character
    if (validate_hex("0C12345678") == 0) {
        failure = fail_test("Test failure: Invalid header characters were accepted, type 2.\n", failure);
    }
    ++test_count;

    // Tests that should return valid
    // Test 1, full length, full range
    if (validate_hex("0x1234CDEF") == 1) {
        failure = fail_test("Test failure: Case 1: Full range was not accepted.\n", failure);
    }
    ++test_count;

    // Test 2, non-max length, full range
    if (validate_hex("0x1F") == 1) {
        failure = fail_test("Test failure: Case 2: Short, full range was not accepted.\n", failure);
    }
    ++test_count;

    // Test 3, short entry
    if (validate_hex("0x0") == 1) {
        failure = fail_test("Test failure: Case 3: Single character was not accepted.\n", failure);
    }
    ++test_count;

    // Test 4, zero entry
    if (validate_hex("0x00000000") == 1) {
        failure = fail_test("Test failure: Case 4: Full zero was not accepted.\n", failure);
    }
    ++test_count;

    // Test 5, mixed case, no header
    if (validate_hex("de4dBE3F") == 1) {
        failure = fail_test("Test failure: Case 5: Mixed case + header was not accepted.\n", failure);
    }
    ++test_count;
  
    // Test 6, mixed case, header
    if (validate_hex("1DAD2dad") == 1) {
        failure = fail_test("Test failure: Case 6: Mixed case, no header was not accepted.\n", failure);
    }
    ++test_count;
  

    if (failure > 0) {
        printf("%d tests of %d tests failed.\n", failure, test_count);
        return 1;
    }

    printf("All %d tests passed successfully. "
        "Proceeding with normal operation.\n", test_count);
    return 0;
}