%{
#include <stdio.h>
#include <assert.h>
%}


%%
#.* { printf("%s: Preprocessor directive\n", yytext); }
"int"|"return" { printf("%s: KEYWORD\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("%s: IDENTIFIER\n", yytext); }
[(){}\[\];:] { printf("%s: SPECIAL SYMBOL\n", yytext); }
[0-9]+ { printf("%s: CONSTANT\n", yytext); }
[ \t\n]+ {}
. { printf("%s: UNKNOWN TOKEN\n", yytext); }
%%

int main(int argc, char **argv) {
    FILE *fp = fopen(argv[1], "r");
    assert(fp != NULL);
    yyin = fp;
    yylex();
    fclose(fp);
    return 0;
}

int yywrap() {
    return 1;
}
