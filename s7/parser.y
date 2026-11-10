%{
#include <stdio.h>

void yyerror(const char *s);
int yylex(void);

int valid = 1;
%}

%token ID NUM
%left '+' '-'
%left '*' '/' '%'

%%
start: S { if (valid) printf("Valid expression\n"); };
S: ID '=' E | E;
E: E '+' E | E '-' E | E '*' E | E '/' E | E '%' E | '(' E ')' | NUM | ID;
%%

void yyerror(const char *s) {
    valid = 0;
    printf("Parser error\n");
}

int main(void) {
    printf("Enter an expression");
    yyparse();
    return 0;
}
