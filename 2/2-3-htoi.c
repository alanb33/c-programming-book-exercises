/*
    htoi.c

    Author: Alan Bailey,
    Date: May 20, 2025
    Exercise 2-3

    Given a string in the format 0xNNNNNNNN, where N is one or more hex
    digits in the range of 0 to F, convert to integer equivalent. 0x/0X are
    an optional component and it should work with the following:

    0x12345678      outputs 305419896
    0x1234          outputs 4660
    1234            outputs 4660

    Note to self - hex is like binary and read right to left. Like octal as
    well, the value is calculated by value^place, starting at 0.
*/

/*
    Abstract

    POSTMORTEM NOTE: The abstract was not fully accurate to the resulting
        program, but at least provided a useful starting point. -A

    vars
        ending_index    the index to stop reading at. default 0.
        max_length      the maxiumum length of the string. default 8.
        exp             the exponent to calculate hex with. default 0.
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
        b. Get the product of value * pow(base, exp). Sum into product.
        c. Decrement index and increment exp.
        d. If index < ending_index, we're done!
*/

#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN     10  /* Max length of string */
#define HEX_BASE    16

#define DO_TESTS    0   /* 1 to run tests, 0 otherwise */

void get_line(char s[]);
unsigned long calculate_hex(char s[]);
int calculate_value(char c);
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
        printf("The value of the provided hex is %lu.\n", calculate_hex(s));
    } else {
        printf("The specified string is invalid as a hexidecimal input. It "
            "must be presented in the format of: \n\n\t[0x]NNNNNNNN\n\nWhere "
            "0x is optional and NNNNNNNN is 1 to 8 hexadecimal digits in the "
            "range of 0-9 and A-F, case-insensitive.\n");
    }

    return 0;
};

/*
    int calculate_hex(char s[])

    From a given hexadecimal string in the format NNNNNNNN or 0xNNNNNNNN where
    N is any hexademical value, 0-9/A-F, case-insensitive, calculate the 
    equivalent decimal value.

    Input s is expected to be validated before calculation. validate_hex(s)
    should be run before the execute of calculate_hex(s).

    Returns the decimal value of the hex input.
*/
unsigned long calculate_hex(char s[]) {
    int end_i = 0;
    if (s[1] == 'x' || s[1] == 'X') {
        end_i = 2;          // We have a 0x preface, so move the end_i
    }

    size_t len = strlen(s);
    int i = len - 1;  // Get the "starting" index at the end of s
    int exp = 0;
    unsigned long value = 0;
    while (i >= end_i) {
        long decimal = calculate_value(s[i]) * pow(16, exp);
        value = value + decimal;
        ++exp;
        --i;
    }

    return value;
}

/*
    int calculate_value(char c)

    Given a valid hexademical digit c, return its decimal value.

    This function expects to receive valid hexes and performs no validation on
    its own. Expected order of operations is to receive a hex string, then 
    validate that hex string, before calling calculate_hex, which calls 
    calculate_value on its own. Calculate value can return a value without the
    assistance of calculate_hex, but input should be validated before it's
    passed to this function.

    PS: Has the book touched switches yet? Not sure -- I'm aware of them from
    other languages, though. -A
*/
int calculate_value(char c) {
    int value = -1;

    if (c >= '0' && c <= '9') {
        value = (c - '0');
    }

    // a's place is 97, and hex a value is 10, so c - 'a' + 10.
    if (c >= 'a' && c <= 'f') {
        value = (c - 'a' + 10);
    }

    // As above, but A is value 65, so we need a different case to handle it.
    if (c >= 'A' && c <= 'F') {
        value = (c - 'A' + 10);
    }

    return value;
}


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
    // TODO: Research how to determine differences between Win and Linux env

    int failure = 0;
    int test_count = 0;

    /*                          HEX INPUT VALIDATION SECTION                  */

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

    /*                          HEX VALUE VALIDATION SECTION                  */

    // We only need to test valid hexes here.
    char hexes[HEX_BASE] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
        'B', 'C', 'D', 'E', 'F'};

    for (int i = 0; i < HEX_BASE; i++) {
        int result = calculate_value(hexes[i]);
        if (result != i) {
            // Special failure case with formatting. oops!
            printf("Test failure: %c does not equal %d, but instead %d.\n", 
                hexes[i], i, result);
            ++failure;
        }
        ++test_count;
    }

    char hexes_lower[HEX_BASE - 10] = {'a', 'b', 'c', 'd', 'e', 'f'};

    for (int i = 0; i < HEX_BASE - 10; i++) {
        int expected = i + 10;
        int result = calculate_value(hexes_lower[i]);
        if (result != expected) {
            // Special failure case with formatting. oops!
            printf("Test failure: %c does not equal %d, but instead %d.\n", 
                hexes_lower[i], expected, result);
            ++failure;
        }
        ++test_count;
    }

    // Full hex strings
    // Edges
    if (calculate_hex("0xFFFFFFFF") != 4294967295) {
        failure = fail_test("Test failure: 0xFFFFFFFF does not equate to 4294967295\n", failure);
    }
    ++test_count;

    if (calculate_hex("0x0") != 0) {
        failure = fail_test("Test failure: 0x0 does not equate to 0\n", failure);
    }
    ++test_count;

    // Arbitrary
    if (calculate_hex("0x0A9D") != 2717) {
        failure = fail_test("Test failure: 0x0A9D does not equate to 2717\n", failure);
    }
    ++test_count;

    // yum yum
    if (calculate_hex("0xDEADBEEF") != 3735928559) {
        failure = fail_test("Test failure: 0x0 does not equate to 3735928559\n", failure);
    }
    ++test_count;

    if (calculate_hex("0x1010DaB0") != 269540016) {
        failure = fail_test("Test failure: 0x1010DaB0 does not equate to 269540016\n", failure);
    }
    ++test_count;

    if (calculate_hex("7302D9C") != 120597916) {
        failure = fail_test("Test failure: 7302D9C does not equate to 120597916\n", failure);
    }
    ++test_count;


    // Test results

    if (failure > 0) {
        printf("%d tests of %d tests failed.\n", failure, test_count);
        return 1;
    }

    printf("All %d tests passed successfully. "
        "Proceeding with normal operation.\n", test_count);
    return 0;
}