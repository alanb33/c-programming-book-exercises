/*
    entab.c

    Author: Alan Bailey
    Date: May 17, 2025
    Exercise 1-21

    Given a string with spaces, replace strings of spaces with the minimum
    number of tabs and spaces to achieve the same spacing.
*/

#include <stdio.h>

#define TABLENGTH   8   /* Number of characters in a tab */
#define MAXLENGTH   100 /* Maximum length of a line */

int parse_segment(char line[], int start_i);

int main()
{
    /* read a line from the user. */
    char line[MAXLENGTH];
    int c;
    int count = 0;
    while ((c = getchar()) != EOF && count < MAXLENGTH) {
        line[count] = c;
        ++count;
    }

    /* cap the line with an EOF -- no newlines here! */
    line[count - 1] = '\0';

    /* the actual execution! parse_line returns -1 if it's EOF. */
    int eof_enc = 0;
    for (int i = 0; eof_enc != 1; ++i) {
        i = parse_segment(line, i);
        if (i == -1) {
            eof_enc = 1;
        }
    }

    printf("The entabbed line is:\n");
    printf("%s", line);
}

/* 
    parses and modifies continuous spaces into tabs as necessary. 
    returns the index to continue at for the next invocation.
    returns -1 if EOF.
*/
int parse_segment(char line[], int start_i)
{

/* 
    how to parse?
    
    start-of-line spaces are ignorable. we only care if tracking mode is
    active when end of segment is reached.
    
    declare vars: current index, space tracking mode, tracking start index,
    space count
    
    if a space is encountered, and tracking mode is inactive, note the index
    of the space, activate tracking mode, and set space count to 1. 
    
    if a space is encountered and tracking mode is active, increment count. 
    
    once the segment ends, we'll have all the vars set that we need.
    if tracking mode is still active, then look back at the start index.
    the number of spaces is stored in the tracking_space_count.

    replace line[tracking_start_index] with \t.
    decrement space count by 1. this is the number that all following characters
        must be shifted.

    beginning at line[start_index + TABLENGTH], copy their values to
        line[start_index + TABLENGTH - space_count].

    if line[start_index + TABLENGTH] == EOF, note this and move it backwards.
        afterwards, return -1 to indicate taht we're done.
    else, return tracking_start_index + 1 to indicate that's where the next
        invocation should continue from.

*/
   
    int i = start_i;
    int tr_mode = 0;
    int tr_start_i = 0;
    int tr_space_c = 0;

    int col = 1;
    while ((i < start_i + TABLENGTH) && (line[i] != '\0')) {
        if (line[i] == ' ') {
            if (tr_mode == 0) {
                tr_mode = 1;
                tr_start_i = i;
            }
            ++tr_space_c;
        } else {
            {
                // a non-space is encountered
                if (tr_mode == 1) {
                    tr_mode = 0;
                }
            }
            
        }
        ++i;
    }

    /*
        by reaching this point, i == start_i + TABLENGTH, or line[i] == '\0'.
        in the event that \0 is within our segment, we end it here, no further
        processing or entabbing is required.
    */

    if (line[i] == '\0') {
        return -1;
    }

    /*
        otherwise, we're at the end of the segment.

        now, assuming that tracking mode is still active at the end of the
        parsed line, all variables are prepared for executing line movement.
    */
    if (tr_mode == 1) {
        line[tr_start_i] = '\t';
        --tr_space_c;
        int j = tr_start_i;
        while (line[j + tr_space_c] != '\0') {
            line[j] = line[j + tr_space_c];
            ++j;
        }

        /*
            if we reach this point, then line[j + tr_space_c] == '\0'.
            move that back too, then if line[j + 1] != '\0', return that as
            the next starting point, otherwise return -1 to indicate EOF.
        */
        line[j] = line[j + tr_space_c];
        if (line[j + 1] != '\0') {
            return j + 1;
        }
        return -1;
    } else {
        /*
            if tracking mode is inactive, then there's nothing to do at the of
            the line. just return the index of the next segment for the
            recursive call!
        */
        return start_i + TABLENGTH;
    }
}