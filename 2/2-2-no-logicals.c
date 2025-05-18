/*
    Exercise 2-2

    Rewrite the following without AND or OR operators:

    for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;
*/

#include <stdio.h>

void get_line(char line[], int lim);

int main(void) {
    int lim = 100;
    char line[lim];
    get_line(line, lim);
    printf("The line is: %s\n", line);
    return 0;
}

/*
    To rewrite the for-loop without logical operators, the logic must
    still be tested. To do so, we should select one of the operators to
    remain as a test, and then test the others within the for-loop.

    Since evaluation moves from left to right, and the first failed
    logical operation will prevent the entire thing from running, the
    logical choice is to retain i < lim - 1 as the termination statement.

    However! That doesn't make any sense, because even if the other
    statements are triggers, the loop will never actually end until
    i == lim - 1.

    So the true answer is that we need a definitive test to cause the
    termination of the for-loop, and the body of the loop needs to do
    some work to control that state.
*/

void get_line(char line[], int lim) {
    
    int stopping = 0;
    int i;
    int c;
    for (i = 0; !stopping; ++i) {
        /*
            While the numerous if statements that cause the same result are a
            bit arbitrary, it adheres to the challenge of not using any 
            logical operators... though if that challenge should also extend
            to the body is a bit questionable. I'll do it here anyway. -A
        */
        if (i == lim - 1) {
            stopping = 1;
        };

        if ((c = getchar()) == '\n') {
            stopping = 1;
        }

        if (c == EOF) {
            stopping = 1;
        }

        if (!stopping) {
            line[i] = c;
        }
    } 
}