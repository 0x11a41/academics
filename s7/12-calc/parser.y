%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

int result;
%}

%token NUM
%left '+' '-'
%left '*' '/' '%'

%%
start: E { result = $1; };

E: E '+' E     { $$ = $1 + $3; }
 | E '-' E     { $$ = $1 - $3; }
 | E '*' E     { $$ = $1 * $3; }
 | E '/' E     {
     if ($3 == 0) {
         yyerror("Division by zero");
         YYABORT;
     }
     $$ = $1 / $3;
   }
 | E '%' E     {
     if ($3 == 0) {
         yyerror("Modulo by zero");
         YYABORT;
     }
     $$ = $1 % $3;
   }
 | '(' E ')'   { $$ = $2; }
 | NUM         { $$ = $1; }
 ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter expression: ");
    if (yyparse() == 0) {
        printf("Result = %d\n", result);
    }
    return 0;
}
