/*
    folding.c

    Author: Alan Bailey
    Date: May 24, 2025
    Exercise 1-22

    Write a program to shorten long inputs into two or more shorter lines 
    after the the last non-blank character before the n-th column of input.
*/

/*
    Plan of approach

    Receive a line of input from the user.
    Define an arbitrary line length and feed it into a shortener function.
    
    Shortener function
        From a given line and line length n
        define a column counter as 0.
        define an iterator i to be referred to outside the loop.
        iterate through the line.
            if a non-space, non-EOF is encountered, print the character.
                define a space as ' ', \t, and \n
            if a space (' ', \t, or \n)  is encountered, do not print the
                character.
            if EOF is encountered, end the loop.
                use EOF as a conditional terminator in the loop.

            increment the column counter.
            if count is equal to n...
                print a newline
                reset counter

        if line[i] == '\0'
            insert a newline.
            this just makes the output cleaner.
*/

#include <stdio.h>

#define COLUMN_LENGTH   8   /* Max characters per column */
#define MAX_LINE        100 /* Max characters in one line */

void getline(char line[]);
void fold(char line[], int len);

int main()
{
    char line[MAX_LINE];

    /* Initialize the line with EOF to allow short-circuit parsing */
    int i = 0;
    while (i < MAX_LINE) {
        line[i] = '\0';
        ++i;
    }

    getline(line);
    fold(line, COLUMN_LENGTH);
}

/*
    void getline(char line[])

    Read the user's input and store it in the character array passed to this
    function.
*/
void getline(char line[]) {

    int c;
    int i = 0;
    while (((c = getchar()) != EOF) && (i < MAX_LINE)) {
        line[i] = c;
        ++i;
    }

    // If we are here, getchar was an EOF or i == MAX_LINE.
    // Terminate the end of the string.
    line[i - 1] = '\0';
}

/*
    void fold(char line[], int len)

    From a given line, 'fold' it after the last non-blank space in a given
    len-th column. Example:

    len = 8
    line = "Hello, world!\0"

    output:

    "Hello, w\n"
    "orld!\n"

    (copied from header plan)

    Shortener function
        From a given line and line length n
        define a column counter as 0.
        define an iterator i to be referred to outside the loop.
        iterate through the line.
            if a non-space, non-EOF is encountered, print the character.
                define a space as ' ', \t, and \n
            if a space (' ', \t, or \n)  is encountered, do not print the
                character.
            if EOF is encountered, end the loop.
                use EOF as a conditional terminator in the loop.

            increment the column counter.
            if count is equal to n...
                print a newline
                reset counter

        if line[i] == '\0'
            insert a newline.
            this just makes the output cleaner.
*/

void fold(char line[], int len)
{
    int col = 1;
    int i = 0;
    int in_word = 0;
    int blank_index = -1;   // recording where the start of blank space is
    while ((i < MAX_LINE) && (line[i] != '\0'))
    {
        /* If we encounter a non-space... */
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') 
        {
            /* If we had a blank index counter, add those blanks back. */
            if (blank_index > -1) {
                int spaces = i - blank_index;
                for (int j = 0; j < spaces; j++) {
                    putchar(' ');
                }
            }

            blank_index = -1;
            in_word = 1;

            putchar(line[i]);
        }

        /* If we encounter a space and we're in a word... */
        if ((line[i] == ' ' || line[i] == '\t' && line[i] != '\n')
            && (in_word = 1))
        {
            in_word = 0;
            if (blank_index == -1) {
                blank_index = i;
            }
        }

        ++col;
        if (col > len)
        {
            putchar('\n');
            col = 1;
        }

        ++i;    // I always forget to increment the counter!!!
    }

    // If we are here, i == MAX_LINE or line[i] == EOF.
    /*
    if (i == MAX_LINE || line[i] == EOF) {
        putchar('\n');
    }; 
    */
    /* 
        The above conditional is not actually necessary as there should be no
        case where it would need to be checked, so we only need to execute
        the body.
    */
    putchar('\n');

}