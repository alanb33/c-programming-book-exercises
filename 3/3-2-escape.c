/*
    escape.c

    Author: Alan Bailey
    Date: May 25, 2025

    Write a function escape(s,t) that converts newlines and tabs into visible
    escape sequences like \n and \t as it copies the string t to s. Use a
    switch.

    Write a function for the reverse that contexts plain-text into real 
    characters.
*/

#include <stdio.h>

#define INPUT_LEN   32  /* Max length for the input string */
#define OUTPUT_LEN  64  /* Double INPUT_LEN in the event that the INPUT_LEN 
                           may consist entirely of tabs or newlines. */

void getline(char s[]);
void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main(void) {

    char s[INPUT_LEN];
    getline(s);

    char t[OUTPUT_LEN];

    printf("Escape Input:  [%s]\n", s);
    escape(s, t);
    printf("Escape Output: [%s]\n", t);

    printf("Unescape Input:  [%s]\n", t);
    unescape(t, s);
    printf("Unescape Output: [%s]\n", s);

    return 0;
}

void getline(char s[]) {
    int c;
    int i;
    for (i = 0; i < INPUT_LEN && (c = getchar()) != EOF; i++) {
        s[i] = c;
    }
    s[i] = '\0';
}

/*
    void escape(char s[], char t[])

    From a source array s, expand all instances of \t and \n with literals
    into t.

    Eg. source line: hello  world
    output line: hello/tworld
*/
void escape(char s[], char t[]) {
    int t_i = 0;
    for (int i = 0; i < INPUT_LEN && s[i] != '\0'; i++) {
        switch (s[i]) {
            case ('\t'):
                t[t_i] = '\\';
                t[t_i + 1] = 't';
                t_i++;
                break;
            case ('\n'):
                t[t_i] = '\\';
                t[t_i + 1] = 'n';
                t_i++;
                break;
            default:
                t[t_i] = s[i];
                break;
        }
        t_i++;
    }

    // Terminate t after the for loop has ended
    t[t_i] = '\0';
}

/*
    void unescape(char s[], char t[])

    Given a string s with \t and \n characters, expand them into proper forms.

    Assume that s is length OUTPUT_LEN and t is length INPUT_LEN for a proper
    expansion length.
*/
void unescape(char s[], char t[]) {

    int t_i = 0;
    for (int i = 0; i < OUTPUT_LEN && s[i] != '\0'; i++) {
        if (s[i] == '\\') {
            switch (s[i + 1]) {
                case 't': {
                    t[t_i] = '\t';
                    i++;
                    break;
                }
                case 'n': {
                    t[t_i] = '\n';
                    i++;
                    break;
                }
            }
        } else {
            t[t_i] = s[i];
        }
        t_i++;
    }

    // Terminate t after the for loop ends
    t[t_i] = '\0';
}