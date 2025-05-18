/*
    Exercise 2-1

    Determine the ranges of char, short, int, and long, both signed and
    unsigned.
*/

/*
    Theory: all types have a minimum and a maximum. What happens if you
    go beyond the minimum or maximum? Let's find out...

    unsigned char 0 - 1 = 255. minimum is 0.
        it seems they overflow!

    so, will unsigned char 255 + 1 = 0?
        confirmed, it does!!

    to determine the range of integer types, I only need to track their
    minimum.
*/

#include <stdio.h>

int power(int n, int exp);
void measure_char();
void measure_short();
void measure_int();
void measure_long();

int main()
{
    measure_char();
    measure_short();
    measure_int();
    measure_long();
}

/*
    While it's tempting to go through numbers one at a time, that's not the
    most efficient route. The book mentioned that all numbers obey the law of
    modulo 2^n where n is the number of bits. 2^8 = 256!

    positive numbers start at 0, however so actual result will be 2^n - 1.

    define a starting n and n increment.

    are they any odd-bit numbers in computing? seems so...
        https://en.wikipedia.org/wiki/1-bit_computing

    An efficiency was considered by only using increments of 2 or 8 for n, but
    I can't say with confidence if that's accurate, so we'll do increments.

    define a limit.
    calculate the value of 2^n + increment. Add 1 if increment is positive.
    if value is less than limit, we've found the cap. else, set limit to new
        cap.

    We don't need to do a negative calculation, actually! If we have the cap 
    of the unsigned number, then we just have to halve that number and
    subtract zero by it to get the lower end.

    Code is repeated here because the book hasn't covered pointers yet; I
    think that I could pass the var I want to work with through pointers, but
    I'm not 100% sure at the time of writing.
*/
int power(int n, int exp) {
    if (exp == 0) {
        return 1;
    }

    for (int i = 1; i < exp; i++) {
        n = n * 2;
    }
    return n;
}

void measure_char()
{
    unsigned char c = 0;

    int limit = 0;
    int max_i = 100;    // maximum attempts, to prevent infinite loop
    short limit_found = 0;
    for (int exp = 1; (limit_found == 0) && (exp < max_i); exp++) {
        c = power(2, exp) - 1;
        limit = c;
        int overflow = c + 1;
        if (limit > overflow) {
            limit_found = 1;
        }
    }

    printf("The limit of an unsigned char is %d\n", limit);

    /*
        Now that we have the unsigned limit, add 1 back to that to find the
        true range, then cut that in half and do zero - half to find the
        unsigned limit.
    */

    int half = (limit + 1) / 2;
    int signed_pos_limit = half - 1;
    int signed_neg_limit = 0 - half;

    printf("The limits of a signed char are %d and %d\n",
        signed_neg_limit, signed_pos_limit);
}

void measure_int() {
    unsigned int ui = 0;

    int limit = 0;
    int max_i = 100;    // maximum attempts, to prevent infinite loop
    short limit_found = 0;
    for (int exp = 1; (limit_found == 0) && (exp < max_i); exp++) {
        ui = power(2, exp) - 1;
        limit = ui;
        int overflow = ui + 1;
        if (limit > overflow) {
            limit_found = 1;
        }
    }

    /*
        Now that we have the unsigned limit, add 1 back to that to find the
        true range, then cut that in half and do zero - half to find the
        unsigned limit.
    */

    printf("The limit of an unsigned int is %d\n", limit);

    int half = (limit + 1) / 2;
    int signed_pos_limit = half - 1;
    int signed_neg_limit = 0 - half;

    printf("The limits of a signed int are %d and %d\n\n",
        signed_neg_limit, signed_pos_limit);
}

void measure_long() {
    unsigned long int uli = 0;

    long long int limit = 0;
    int max_i = 100;    // maximum attempts, to prevent infinite loop
    short limit_found = 0;
    for (int exp = 1; (limit_found == 0) && (exp < max_i); exp++) {
        uli = power(2, exp) - 1;
        limit = uli;
        int overflow = uli + 1;
        if (limit > overflow) {
            limit_found = 1;
        }
    }

    /*
        Now that we have the unsigned limit, add 1 back to that to find the
        true range, then cut that in half and do zero - half to find the
        unsigned limit.
    */

    printf("The limit of an unsigned long int is %ld\n", limit);

    long half = (limit + 1) / 2;
    long signed_pos_limit = half - 1;
    long signed_neg_limit = 0 - half;

    printf("The limits of a signed short int are %ld and %ld\n\n",
        signed_neg_limit, signed_pos_limit);
}

void measure_short() {
    unsigned short int usi = 0;

    int limit = 0;
    int max_i = 100;    // maximum attempts, to prevent infinite loop
    short limit_found = 0;
    for (int exp = 1; (limit_found == 0) && (exp < max_i); exp++) {
        usi = power(2, exp) - 1;
        limit = usi;
        int overflow = usi + 1;
        if (limit > overflow) {
            limit_found = 1;
        }
    }

    /*
        Now that we have the unsigned limit, add 1 back to that to find the
        true range, then cut that in half and do zero - half to find the
        unsigned limit.
    */

    printf("The limit of an unsigned short int is %d\n", limit);

    int half = (limit + 1) / 2;
    int signed_pos_limit = half - 1;
    int signed_neg_limit = 0 - half;

    printf("The limits of a signed short int are %d and %d\n\n",
        signed_neg_limit, signed_pos_limit);
}