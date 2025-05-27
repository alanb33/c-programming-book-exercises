/*
    atof.c
    Based on atof on page 65 of The C Handbook, 2nd Edition

    Alan Bailey
    May 27, 2025
    Exercise 4-2

    Extend atof to handle scientific notation of the form:
        123.45e-6
    where a floating-point number may be followed by e or E an an optionally
    signed exponent.
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>

/*
    atof_sci

    Original atof structure is attributed to B. Kernighan and D. Ritchie.

    Expnaded by A. Bailey with commentary and to allow for the usage of
    scientific notation inputs.
*/
double atof_sci(char s[]) {
    double val, power;
    int i, sign;

    // Skip white space
    for (i = 0; isspace(s[i]); i++)
        ;

    // Determine sign
    sign = (s[i] == '-') ? -1 : 1;
    
    // Skip sign character if present
    if (s[i] == '+' || s[i] == '-')
        i++;

    // While we have digits, turn the chars into their numeric value.
    for (val = 0.0; isdigit(s[i]) ; i++)
        val = 10.0 * val + (s[i] - '0');

    // Skip period separator
    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    /*
        Expansion begins here; originally was return sign * val / power.
    */
    double expanded = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        // Beware of malformed entry; e with no following
        if (s[i] == '\0') {
            return expanded;
        } else {
            // Determine sign and advance
            int exp_sign = s[i] == '-' ? -1 : 1;
            if (s[i] == '-' || s[i] == '+') {
                i++;
            }

            // The atoi of the scientific notation will be our exponent
            double exp_power = 0.0;
            for (; isdigit(s[i]) ; i++) {
                exp_power = 10.0 * exp_power + (s[i] - '0');
            }

            // Finally; confirm we actually operated on a number.
            if (exp_power != 0.0) {
                double multiplier = pow(10, (exp_sign * exp_power));
                return expanded * multiplier;
            } else {
                return expanded;
            }
        }

    } else {
        // No scientific notation
        return expanded;
    }

    /*
        123.456 example
        val = 123456.0
        power = 1000.0
        sign = 1

        sign * val / power
        1 * 123456.0 = 123456.0 / 1000.0 = 123.456
    */
    return sign * val / power;
}