/*
    invert.c

    Author: Alan Bailey
    Date: May 22, 2025
    Exercise 2-7

    Write a function invert(x,p,n) that returns x with the n bits that begin
    at position p inverted, leaving the others unchanged.
*/

/*
        Pre-code plan

    So, as before in 2-6, we need to isolate the bits we want to invert,
    invert them, and then invert them back into their original position,
    leaving the other bits unchanged.

    So, one problem at a time. Let's isolate the n bits at position p
    within x.

    (p - n + 1) = the right shift of X. p = 5 && n = 2? >> 4!

    Now that the bits are isolated on the right side, zero out the rest
    of the bits. To do that, we have to AND zeroes into all other bits.
    The easiest way to do that is ~(~0 << n)

    (x >> (p - n + 1)) & ~(~0 << n)

    with the above, we have the bits isolated. now, we could flip it all
    and then AND them again, but what if we could invoke that AND only once?
    
    ~(x >> (p - n + 1)) & ~(~0 << n)

    With this, we invert the bits BEFORE we AND it out, so we only need to
    do one invocation of AND.

    Now, what we have are the isolated, inverted n bits from position p of x.
    The next step is to insert them back in.

    Idea #1: Left-shift the inverted bits into position and then OR the rest
    of the bits... but how do we prevent our inverted bits from hitting the
    OR? We just need an OR mask... we can't use an OR mask calculated from
    our inverted bits because there might be a mixture of 1s and 0s.

    We can make the OR mask from our variables p and n. It needs to be n
    long and in position p. The OR mask must be ones for the original bits
    and zeroes for the inverted bits. Thus...

    1. ~(1 << n)    This will get us something like 00001111 in n = 4

    to move the bits into position, its current position is known by n.
    it needs to move left to reach p. If n is 2 and p is 6, it must be 
    left-shifted by 3! p - n - 1 = 3!

    Finally, invert that to get our OR mask.

    76543210
    00001111    step 1: ~(1 << n)
    01111000    step 2: << (p - n - 1)
    10000111    step 3: ~

    Now we have our OR mask!!! now uh... how do we use it?

    Idea #2: Turns out, we can't just OR it onto x. The real answer is to
    take that OR mask and use it as an AND mask.

    x & (AND mask) == x with the selected bits zeroed.
    now, we just OR the inverted bits onto x!

    x | (inverted bits)

    complete!
*/

#include <stdint.h>
#include <stdio.h>

uint8_t invert(uint8_t x, uint8_t p, uint8_t n);

int main(void) {
    uint8_t x = 55; // 0b00110111
    uint8_t p = 6;  // 0b0[0110111]
    uint8_t n = 3;  // 0b0[011]0111

    uint8_t inverted = invert(x, p, n);
    uint8_t expected = 0b01000111;
    // Expecting a result of 0b01000111, or 71.

    printf("The inverted result is %u\n", inverted);

    if (inverted != expected) {
        return 1;
    }

    return 0;
}

/*
    uint8_t invert(x, p, n)

    Given a number x, bit position p, and bit length 4, invert the n
    bits at position p.
*/
uint8_t invert(uint8_t x, uint8_t p, uint8_t n) {
    // The amount of bit movement necessary for left and right shifts.
    uint8_t shift_formula = p - n + 1;

    // Isolation and inversion of the selected bits in a single formula.
    uint8_t isolated_inverted = ~(x >> shift_formula) & ~(~0 << n);

    // Creation and positioning of an AND mask for the inverted bits.
    uint8_t and_mask = ~(~(~0 << n) << shift_formula);

    // Return the original x with the AND mask applied and the inverted bits
    // OR'd into it.
    return (x & and_mask) | (isolated_inverted << shift_formula);
}

/*
        Post-execution test #1

    The expected result was 0b01000111, 71.
    The actual result was 0b00100111, 39.

    At first glance, the inverted bits weren't left-shifted enough. Let's
    revisit that thought process from earlier:

    p=6, n=4
    6 - 4 = 2 - 1 = 1... that's not 3! Whoops!
    6 - 4 = 2 + 1 = 3. That's the answer!

    76543210    (bitpos)
    00001111    step 1: ~(1 << n)
    01111000    step 2: << (p - n - 1)
    10000111    step 3: ~

    So, we should just have to flip that shift from (p-n-1) to (p-n+1).

        Post-execution test #2
        (Following and_mask formula change)

    The expected result was 0b01000111, 71.
    The actual result was   0b00000111... 7.

    What's going on here? Time to insert some debug statements...

    After some examination, it was discovered that the formula to calculate
    isolated_inverted was incorrect. It seems that I had written the formula
    incorrectly despite correctly deducing it in the pre-plan. Whoops! I 
    blame not wearing my glasses and the total mind scramble that is working
    with bits.

        Post-execution test #3
        (Following corrected isolation formula)

    The expected result was 0b01000111, 71.
    The actual result was   0b01000111, 71!

    Following this success, let's try some arbitrary other tests.

        Final test #1

    Expected, 181. Actual, 53. x = 173, p = 4, n = 2.
        What went wrong?

        Final test #2

    Expected, 31. Actual, 31. x = 55, p = 6, n = 3.
        Why was this correct?

    It seems that p = 5 or lower gives the wrong answer.
    Why?

    Expected: 149 (0b10010101)
    Actual:   21  (0b00010101)

        The real answer

    The and_mask formula was defined thusly:

        ~(~(1 << n) << shift_formula);

    The problem? It's the 1! I erroneously assumed that 1 == ~0. That's
    very incorrect! 255 == ~0!!

    The corrected formula is:

        ~(~(~0 << n) << shift_formula);

    What an adventure. -A
*/