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
