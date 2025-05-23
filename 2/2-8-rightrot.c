/*
    rightrot.c

    Alan Bailey, May 23, 2025

    The function rightrot(x,n), which returns the value of the interger x
    rotated to the right by n positions.

    This means that the n bits shifted right should wind up on the left side
    of the bit array!
*/

/*
        Pre-code plan

    This should actually be a fairly simple process.

    1. Using an AND mask, isolate the rightmost n bits.
        and_mask = ~(~0 << n)
        isolated = x & and_mask
    2. Left-shift the rightmost n bits into the leftmost position.
        Given a bit length of 8, if n is 2, needs to be shifted left by 5.
            Formula = BIT_LENGTH - n; any length of bits!
        left_shift = BIT_LENGTH - n
        left_shifted = isolated << left_shift
    3. Shift the and_mask into position and then invert it to clear the bit
        space.

        left_and_mask = ~(and_mask << left_shift)
        left_cleared = x & left_and_mask
    
    4. Finally, OR them together.
        solution = left_cleared | left_shifted 
*/

#include <stdint.h>
#include <stdio.h>

#define BIT_LENGTH  8   /* Number of bits to work with. */
#define DO_TESTS    0   /* Do success tests */

/*
    While these are using uint8_t for simplicity, they should work with bits
    of any length, in theory, though you'd need to adjust the types here.
*/
uint8_t rightrot(uint8_t x, uint8_t n);
void report_rotation(uint8_t start, uint8_t n, uint8_t expected);
void success_tests();

int main(void) {

    uint8_t start    = 0b11010111;  // 215
    uint8_t n        = 3;
    uint8_t expected = 0b11111010;  // 250

    report_rotation(start, n, expected);

    if (DO_TESTS) {
        success_tests();
    }

    return 0;
}

uint8_t rightrot(uint8_t x, uint8_t n) {
    // Craft an AND mask to only get 1 bits for n.
    uint8_t and_mask = ~(~0 << n);
    uint8_t isolated_n = x & and_mask;

    // Calculate the left-shift and then move both sets.
    uint8_t left_shift_formula = BIT_LENGTH - n;

    // The AND mask is inverted to zero out the left n bits.
    and_mask = ~(and_mask << left_shift_formula);
    isolated_n = isolated_n << left_shift_formula;

    /* 
        Finally, right-shift x by n and then OR them together to get the 
        right-rotated n bits.
    */
    return ((x >> n) & and_mask) | isolated_n;
}

void report_rotation(uint8_t start, uint8_t n, uint8_t expected) {
    
    uint8_t actual   = rightrot(start, n);

    printf("The expected number is %d and the actual result is %d.\n",
        expected, actual);

}

/*
        Post-plan attempt #1
    The expected was 250, but we got 247. 
    
    250: 0b11111010
    247: 0b11110111

    x was not right-shifted, oops! #2 will include x >> n.

        Attempt #2

    250: 0b11111010
    250: 0b11111010

    We got it! Just have to remember to also shift the original number.

        Success test #1

    n: 4
    x:        0b10100011 (163)
    expected: 0b111010   (58)
    actual:   0b111010   (58)

        Test #2

    n: 1
    x:        0b10110001 (177)
    expected: 0b11011000 (216)
    actual:   0b11011000 (216)

        Test #3

    n: 6
    x         0b11000000;  (192)
    expected: 0b11         (3)
    actual:   0b11         (3)

    Excellent! -A
*/

/*
    success_tests

    Just a few tests using some arbitrary numbers to confirm that
    operation seems to be successful.
*/
void success_tests(void) {
    uint8_t start    = 0b10100011;  // 163
    uint8_t n        = 4;
    uint8_t expected = 0b111010;  // 58

    report_rotation(start, n, expected);

    start    = 0b10110001;  // 177
    n        = 1;
    expected = 0b11011000;  // 216

    report_rotation(start, n, expected);

    start    = 0b11000000;  // 192
    n        = 6;
    expected = 0b11;        // 3

    report_rotation(start, n, expected);
}