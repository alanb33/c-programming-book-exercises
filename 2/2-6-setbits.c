/*
    setbits.c

    Author: Alan Bailey
    Date: May 22, 2025
    Exercise 2-6

    The function setbits(x,p,n,y) that returns x with the n bits that begin
    at position p set to the rightmost n bits of y, leaving other bits
    unchanged.
*/

/*
    Pre-coding plan:

    So, given a binary number x of arbitary value...

    bit position    76543210
    binary (x)      01101011

    get the n bits that begin at position p.

    let's say p = 6 and n = 4. we need to get the 4 bits that begin at
    position 6, which are:

    bit pos     7|6543|210
    binary (x)  0|1101|011

    so, what are the isolation options?
        it only matters if we can return the bits, so 1101000 != 1101.
        the bits must be right-shifted.

        x >> 3 (7 - 4?)
        00001101

    What if there are one bits to the left of the desired bit range?
        00011101

    ~0 >> 4 == 00001111
    00011101 & 00001111 = 00001101

    Thus, (x >> 7 - n) & (~0 >> n)

    but wait, what if we need to get the 3 bits at position 4? 
        p = 4, n = 3

        (x >> 7 - 3) = (x >> 4) kills the four digits.
        p = 6, n = 4, >> = 3.
        p = 4, n = 3, >> = 2.
        shift ... p-n+1?

        (x >> p - n + 1) & (~0 >> n)

    Now, the selected bits are isolated.

    Next part: set those bits into the rightmost n bits of y.

    First part is easy. y << n. This will make room for the bits that we need
    to insert.

    The second bit is harder. How do we set those bits without affecting the
    rest of the bits? ...I think we just need to OR X in.

    (y << n) | x

    So... final formula?
        (y << n) | ((x >> p - n + 1) & (~0 >> n))
*/

#include <stdint.h>
#include <stdio.h>

uint8_t setbits(uint8_t x, uint8_t p, uint8_t n, uint8_t y) {
    return (y << n) | ((x >> p - n + 1) & ~(~0 << n));
}

int main(void) {
    uint8_t x = 60;     // 0b00111100
    uint8_t y = 48;     // 0b00110000
    uint8_t p = 3;      // 0011[1100]
    uint8_t n = 2;      // 0011[11]00

    // The expected output is 0b11000011, or 195.

    uint8_t output = setbits(x, p, n, y);

    printf("The resulting shift is %u\n", output);
    return 0;
}

/*
    Post code examination:

    Formula #1: (y << n) | ((x >> p - n + 1) & (~0 >> n));
    In:
        x = 60  (0b00111100)
        y = 48  (0b00110000)
        p = 3   (0011[1100])
        n = 2   (0011[11]00)

    Expected: selection of 0b11, or 3. Where did things go wrong?
    The actual result was 15, or 0b1111. This tells me that the shift was
    too short, and I do see that the masking is only shifting by n... which
    means ~0 >> n is actualy 00111111. oops! that's not the right mask.

    The right mask is 00000011. Can most easily achieve that by taking
    ~0 << n (11111100) and then one's complementing that (00000011)

    thus, the final part should actually be:

    ~(~0 << n)

    Formula #2: (y << n) | ((x >> p - n + 1) & ~(~0 << n));

        In:
        x = 60  (0b00111100)
        y = 48  (0b00110000)
        p = 3   (0011[1100])
        n = 2   (0011[11]00)

    Expected: Select of 0b11, or 3. The final result should be 0b11000011
    or 195.

    Result: 195. I got it! Excellent jackpot!

    Let's do some further tests... I'll just change y.

    Test #2: y = 255 0b11111111
    After the shift, y should be shifted to the left 2, 11111100, but then
    00000011 is inserted, resulted in 0b11111111, or 255.

    Result: 1023. Huh?
    Turns out that's right... 1111111111.

    What happened here? I was returning the value as an unsigned int, so it was
    able to contain a few more bits. The solution was to return it as a smaller
    type, and while I could opt for unsigned char, I think I want more precise
    control over the data that I'm getting. To that end, I've imported stdint.h
    and used uint8_t in many places instead of more generic int types. -A
*/