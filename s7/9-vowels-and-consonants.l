; vowels and consonants
%{
#include <stdio.h>
int vowels = 0;
int consonants = 0;
%}

%%

[aeiouAEIOU]        { vowels++; }
[a-zA-Z]            { consonants++; }
\n                  { return 0; }
.                   { }

%%

int main()
{
    printf("Enter a string: ");
    yylex();
    printf("Number of vowels     : %d\n", vowels);
    printf("Number of consonants : %d\n", consonants);
    return 0;
}

int yywrap()
{
    return 1;
}

; Enter a string: hello world
; Number of vowels     : 3
; Number of consonants : 7
