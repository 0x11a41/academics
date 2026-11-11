%{
#include <stdio.h>

int yylex();
void yyerror(const char *s);

int valid;
%}

%token ID

%%
start: ID { valid = 1; }
%%

void yyerror(const char *s) {
    printf("Error msg: %s\n", s);
    valid = 0;
}

int main() {
    printf("Enter variable name: ");
    yyparse();
    if (valid) {
        printf("Valid variable name\n");
    } else {
        printf("Invalid variable name\n");
    }
    return 0;
}
