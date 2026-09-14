%{
#include <stdio.h>
#include <stdlib.h>
%}

identifier  [a-zA-Z_][a-zA-Z0-9_]*

%%

#.*                                 { printf("%s --> PREPROCESSOR DIRECTIVE\n", yytext); }
"int"|"float"|"char"|"double"|"while"|"for"|"do"|"if"|"break"|"continue"|"void"|"switch"|"case"|"long"|"struct"|"const"|"typedef"|"return"|"else"|"printf"|"scanf"|"goto"|"main" {
                                      printf("%s --> KEYWORD\n", yytext);
                                    }
{identifier}\(                      { printf("%s --> FUNCTION\n", yytext); }
\{                                  { printf("%s --> BLOCK BEGINS\n", yytext); }
\}                                  { printf("%s --> BLOCK ENDS\n", yytext); }
{identifier}(\[[0-9]*\])?           { printf("%s --> IDENTIFIER\n", yytext); }
[0-9]+                              { printf("%s --> NUMBER\n", yytext); }
"="                                 { printf("%s --> ASSIGNMENT OPERATOR\n", yytext); }
"<="|">="|"<"|">"|"=="|"!="         { printf("%s --> RELATIONAL OPERATOR\n", yytext); }
"+"|"-"|"*"|"/"|"%"                 { printf("%s --> ARITHMETIC OPERATOR\n", yytext); }
";"|":"|","|"\""|"\\"|"("|")"|"'"   { printf("%s --> SPECIAL SYMBOL\n", yytext); }
"\\n"|"\\t"|"\\0"                   { printf("%s --> ESCAPE SEQUENCE\n", yytext); }
"%s"|"%d"|"%c"|"%f"|"%lf"           { printf("%s --> FORMAT SPECIFIER\n", yytext); }
[ \t\n]+                            { /* ignore whitespace */ }
.                                   { printf("%s --> UNKNOWN\n", yytext); }

%%

int main()
{
    FILE *file = fopen("test.c", "r");
    if (!file) {
        printf("Could not open file prg.c\n");
        exit(1);
    }
    yyin = file;
    yylex();
    fclose(file);
    return 0;
}

int yywrap()
{
    return 1;
}

; ################## test.c ####################
; #include <stdio.h>

; int main()
; {
;     for (int i = 0; i < 10; i++) {
;         printf("hello\n");
;     }
;     return 0;
; }

; ################# OUTPUT: ####################
; #include <stdio.h> --> PREPROCESSOR DIRECTIVE
; int --> KEYWORD
; main( --> FUNCTION
; ) --> SPECIAL SYMBOL
; { --> BLOCK BEGINS
; for --> KEYWORD
; ( --> SPECIAL SYMBOL
; int --> KEYWORD
; i --> IDENTIFIER
; = --> ASSIGNMENT OPERATOR
; 0 --> NUMBER
; ; --> SPECIAL SYMBOL
; i --> IDENTIFIER
; < --> RELATIONAL OPERATOR
; 10 --> NUMBER
; ; --> SPECIAL SYMBOL
; i --> IDENTIFIER
; + --> ARITHMETIC OPERATOR
; + --> ARITHMETIC OPERATOR
; ) --> SPECIAL SYMBOL
; { --> BLOCK BEGINS
; printf( --> FUNCTION
; " --> SPECIAL SYMBOL
; hello --> IDENTIFIER
; \n --> ESCAPE SEQUENCE
; " --> SPECIAL SYMBOL
; ) --> SPECIAL SYMBOL
; ; --> SPECIAL SYMBOL
; } --> BLOCK ENDS
; return --> KEYWORD
; 0 --> NUMBER
; ; --> SPECIAL SYMBOL
; } --> BLOCK ENDS
