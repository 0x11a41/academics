/* GRAMMAR:
    E  -> T E'
    E' -> + T E' | ε
    T  -> F T'
    T' -> * F T' | ε
    F  -> ( E ) | i
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

char lookahead;

void err()
{
    printf("Syntax Error! Parsing failed.\n");
    exit(1);
}

void match(char expected)
{
    if (lookahead == expected) {
        do {
            lookahead = getchar();
        } while (lookahead == ' ');
    } else {
        err();
    }
}

void E();

void F()
{
    if (lookahead == '(') {
        match('('); E(); match(')');
    } else if (lookahead == 'i') {
        match('i');
    } else {
        err();
    }
}

void TPrime()
{
    if (lookahead == '*') {
        match('*'); F(); TPrime();
    }
}

void T()
{
    F(); TPrime();
}

void EPrime()
{
    if (lookahead == '+') {
        match('+'); T(); EPrime();
    }
}

void E()
{
    T(); EPrime();
}

int main()
{
    printf("Enter expression: ");
    lookahead = getchar();

    E();

    if (lookahead == '\n' || lookahead == EOF) {
        printf("Parsing Successful!\n");
    } else {
        err();
    }

    return 0;
}
