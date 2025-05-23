/*
    bitcount.c

    Author: Alan Bailey
    Date: May 23, 2025

    In a two's complement number system, x &= (x-1) deletes the rightmost
    1-bit in x. Why's that?

    The two's complement representation is achieved via taking the binary
    representation, with a leading bit representing sign (0 is positive).

    A positive 255 is 0b11111111. Its sign bit is 0, so it's actually
    0b011111111.

    Invert the digits, then add 1.

    0b100000001.

    The MSB is negative, so in this case, -256. Add the rest of the bits
    positively and you get the result -255. It's the two's complement
    representation!

    So, let's assume that we have 0b000000000, "positive" 0. Flip those
    bits and subtract 1 to get 0b111111110. -256 + 255 = -1.
    
    x &= (x-1) will delete the rightmost bit because (x-1) creates an AND
    mask that allows all digits but the rightmost!

    So, can we refine the following formula?

    int bitcount(unsigned x)
    {
        int b;

        for (b = 0; x != 0; x >>= 1)
            if (x & 01) // that's octal 1... just 1
                b++;
        return b;
    }
*/

/*
        Pre-code plan

    Let's step through this step by step.

    We are given the unsigned integer x.
    Start at b = 0, where b represents the number of 1-bits...
    if x != 0 (it will become zero from right-shifts), we terminate.
    Else...
        if (x & 01), which means, if x & 1 is non-zero afterward,
            increment b.
        right-shift x by 1 and continue.
    at termination, return b.

    How do we make this more efficient? 
    1. declare b (necessary to return)
    2. b = 0
    [3. check x != 0
    [4. check x & 01 > 0
    [5. b++ if so
    [6. x >>= 1, jump to 3
    7. return b

    So, if LSB = 0 immediately, that's 4 operations.
    If LSB >= 1, that's 3 + 4*LSB operations.

    1. declare b
    2. b = 0
    [3. check x != 0
    [4. b++ if so
    [5. x &= x-1, jumpt o 3
    6. return b

    We've improved from 3 + 4*LSB to 3 + 3*LSB.

    But what about b?

    1. declare b = 0
    [2. check if x != 0
    [3. b++ if so
    [4. x &= x-1, jump to 2
    5. return b

    We've improved from 3 + 3*LSB to 2 + 3*LSB!

    However; do operation counts really work like that...? -A
*/

#include <stdint.h>
#include <stdio.h>

int bitcount(uint8_t x);

int main(void) {
    printf("1-bits in 0b00111111: %d (expected 6)\n",
        bitcount(0b00111111));
    printf("1-bits in 0b00110011: %d (expected 4)\n",
        bitcount(0b00110011));
    printf("1-bits in 0b11000: %d (expected 2)\n",
        bitcount(0b11000));
    return 0;
}

/*
    Return the number of 1-bits in x.
*/
int bitcount(uint8_t x) {
    int b = 0;
    while (x != 0) {
        b++;
        x &= x - 1;
    }
    return b;
}