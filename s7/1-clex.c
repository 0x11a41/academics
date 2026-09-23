#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

FILE *fp = NULL;
char buf[256];

int is_keyword(const char *s)
{
    const char *keywords[] = { "int", "return" };
    const int n = sizeof(keywords) / sizeof(char*);
    for (int i = 0; i < n; i++) {
        if (strcmp(s, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isop(char ch)
{
    char *str = "+-/*|=^&%!<>~";
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) return 1;
    }
    return 0;
}

int ispunc(char ch)
{
    char *punc = "(){}[]?:.,;";
    for (int i = 0; punc[i] != '\0'; i++) {
        if (punc[i] == ch) return 1;
    }
    return 0;
}

void advance(char ch, int (*validate)(int))
{
    assert(fp != NULL);
    int i = 0;
    while (validate(ch)) {
        buf[i++] = ch;
        ch = fgetc(fp);
    }
    buf[i] = '\0';
    fseek(fp, -1, SEEK_CUR);
}

int isnum(int ch) { return isdigit(ch) || ch == '.'; }

int main() {
    fp = fopen("input.c", "r");
    assert(fp != NULL);

    for (char ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        while (isspace(ch)) ch = fgetc(fp);
        if (ch == EOF) break;

        if (isalpha(ch) || ch == '_') {
            advance(ch, isalnum);

            printf("%s: ", buf);
            if (is_keyword(buf)) {
                printf("KEYWORD");
            } else {
                printf("IDENTIFIER");
            }
        }
        else if (isdigit(ch)) {
            advance(ch, isnum);
            printf("%s: NUMBER", buf);
        }
        else if (ch == '\'' || ch == '"') {
            char quote_type = ch;
            int i = 0;
            do {
                buf[i++] = ch;
                ch = fgetc(fp);
            } while (ch != EOF && ch != quote_type && ch != '\n');

            buf[i++] = ch;
            buf[i] = '\0';

            if (ch == '\n') {
                printf("%s: ERR! LITERAL NOT TERMINATED\n", buf);
            } else {
                printf("%s: LITERAL", buf);
            }
        }
        else if (isop(ch)) {
            printf("%c: OPERATOR", ch);
        }
        else if (ispunc(ch)) {
            printf("%c: PUNCTUATION", ch);
        }
        else {
            printf("%c: INVALID TOKEN", ch);
        }
        printf("\n");
    }

    fclose(fp);

    return 0;
}
/* input.c
int main()
{
    int i = 0;
    printf("hello world");
    return 0;
}
*/

/* OUTPUT
int: KEYWORD
main: IDENTIFIER
(: PUNCTUATION
): PUNCTUATION
{: PUNCTUATION
int: KEYWORD
i: IDENTIFIER
=: OPERATOR
0: NUMBER
;: PUNCTUATION
printf: IDENTIFIER
(: PUNCTUATION
"hello world": LITERAL
): PUNCTUATION
;: PUNCTUATION
return: KEYWORD
0: NUMBER
;: PUNCTUATION
}: PUNCTUATION
*/
