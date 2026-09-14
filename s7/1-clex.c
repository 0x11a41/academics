// simplified lexical analyzer for C

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int is_keyword(const char *str)
{
    for (int i = 0; i < 32; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int is_operator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' ||
           c == '%' || c == '=' || c == '<' || c == '>' ||
           c == '!' || c == '&' || c == '|' || c == '^';
}

int main()
{
    char c, str[50];
    int i, n;

    FILE *f = fopen("test.c", "r");
    if (f == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    while ((c = getc(f)) != EOF) {
        if (isdigit(c)) {
            n = c - '0';
            c = getc(f);
            while (isdigit(c)) {
                n = n * 10 + (c - '0');
                c = getc(f);
            }
            printf("%d is a NUMBER\n", n);
            ungetc(c, f);
        }
        else if (isalpha(c) || c == '_') {
            i = 0;
            str[i++] = c;
            c = getc(f);
            while (isalnum(c) || c == '_') {
                str[i++] = c;
                c = getc(f);
            }
            str[i] = '\0';
            ungetc(c, f);

            if (is_keyword(str))
                printf("%s is a KEYWORD\n", str);
            else
                printf("%s is an IDENTIFIER\n", str);
        }
        else if (c == ' ' || c == '\t' || c == '\n') {
            continue;
        }
        else if (is_operator(c)) {
            i = 0;
            str[i++] = c;
            c = getc(f);

            if ((str[0] == '+' && c == '+') || (str[0] == '-' && c == '-') ||
                (str[0] == '=' && c == '=') || (str[0] == '!' && c == '=') ||
                (str[0] == '<' && c == '=') || (str[0] == '>' && c == '=') ||
                (str[0] == '&' && c == '&') || (str[0] == '|' && c == '|') ||
                (str[0] == '<' && c == '<') || (str[0] == '>' && c == '>') ||
                (str[0] == '+' && c == '=') || (str[0] == '-' && c == '=') ||
                (str[0] == '*' && c == '=') || (str[0] == '/' && c == '=')) {
                str[i++] = c;
                c = getc(f);
            }

            str[i] = '\0';
            ungetc(c, f);
            printf("%s is an OPERATOR\n", str);
        }

        else {
            printf("%c is a SPECIAL SYMBOL\n", c);
        }
    }

    fclose(f);
    return 0;
}

/* OUTPUT:
############### test.c ##############
int main()
{
    for (int i = 0; i < 10; i++) {
        printf("hello\n");
    }
    return 0;
}

int is a KEYWORD
main is an IDENTIFIER
( is a SPECIAL SYMBOL
) is a SPECIAL SYMBOL
{ is a SPECIAL SYMBOL
for is a KEYWORD
( is a SPECIAL SYMBOL
int is a KEYWORD
i is an IDENTIFIER
= is an OPERATOR
0 is a NUMBER
; is a SPECIAL SYMBOL
i is an IDENTIFIER
< is an OPERATOR
10 is a NUMBER
; is a SPECIAL SYMBOL
i is an IDENTIFIER
++ is an OPERATOR
) is a SPECIAL SYMBOL
{ is a SPECIAL SYMBOL
printf is an IDENTIFIER
( is a SPECIAL SYMBOL
" is a SPECIAL SYMBOL
hello is an IDENTIFIER
\ is a SPECIAL SYMBOL
n is an IDENTIFIER
" is a SPECIAL SYMBOL
) is a SPECIAL SYMBOL
; is a SPECIAL SYMBOL
} is a SPECIAL SYMBOL
return is a KEYWORD
0 is a NUMBER
; is a SPECIAL SYMBOL
} is a SPECIAL SYMBOL
*/
