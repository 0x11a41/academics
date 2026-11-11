%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
\n                     { return 0; }
[ \t\r]                {}
.                      { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
