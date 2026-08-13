#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_RESET "\x1b[0m"
#define ANSI_DIM   "\x1b[2m"
#define ANSI_BOLD  "\x1b[1m"
#define ANSI_RED   "\x1b[31m"
#define ANSI_BLUE  "\x1b[34m"

typedef enum {
    TOK_INVALID,
    TOK_KEYWORD,
    TOK_LITERAL,
    TOK_PUNCTUATION,
    TOK_IDENTIFIER,    
    TOK_OPERATOR,
} TokType;

void print_toktype(TokType type)
{
    switch (type) {
        case TOK_KEYWORD:     printf("KEYWORD"); break;
        case TOK_INVALID:     printf("INVALID"); break;
        case TOK_OPERATOR:    printf("OPERATOR"); break;
        case TOK_LITERAL:     printf("LITERAL"); break;
        case TOK_PUNCTUATION: printf("PUNCTUATION"); break;
        case TOK_IDENTIFIER:  printf("IDENTIFIER"); break;
    }
}

struct {
    int i;
    char *buf;
    int len;
} lex;

typedef struct {
    char *ref;
    int len;
} Lexeme;

typedef struct {
    TokType type;
    char *s;
    Lexeme lexeme;
} Token;

void print_token(const Token *tok)
{
    printf("( ");
    printf(ANSI_BLUE);
    for (int i = 0; i < tok->lexeme.len; i++) {
        printf("%c", tok->lexeme.ref[i]);
    }
    printf(ANSI_RESET);
    printf(ANSI_DIM "::" ANSI_RESET);
    print_toktype(tok->type);
    printf(" )\n");
}

void lexer_skip_ws()
{
    while (lex.i < lex.len && isspace(lex.buf[lex.i])) lex.i++;
}

void lexer_skip_comment()
{
    lexer_skip_ws();
    char curr = lex.buf[lex.i];
    char next = lex.buf[lex.i + 1];
    if (curr == '/') {
        if (next == '/') {
            while (lex.i < lex.len && lex.buf[lex.i++] != '\n');   
        } else if (next == '*') {
            while (lex.i < lex.len && lex.buf[lex.i++] != '/');
        }
    }
}

void lexer_skip_macro()
{
    lexer_skip_ws();
    if (lex.buf[lex.i] != '#') return;
    while (lex.i < lex.len && lex.buf[lex.i++] != '\n');
}

const char *KEYWORDS[] = {
    "unsigned", "void",   "volatile", "while",
    "inline",   "int",    "long",     "register", "restrict", "return",   "short",
    "signed",   "sizeof", "static",   "struct",   "switch",   "typedef",  "union",
    "double",   "else",   "enum",     "extern",   "float",    "for",      "goto",    "if",
    "auto",     "break",  "case",     "char",     "const",    "continue", "default", "do",
};

int is_keyword(Lexeme *s)
{
    for (int i = 0; i < (int)(sizeof(KEYWORDS) / sizeof(char*)); i++) {
        int is_equal = ((int)strlen(KEYWORDS[i]) == s->len);
        for (int j = 0; is_equal && j < s->len; j++) {
            is_equal = (s->ref[j] == KEYWORDS[i][j]);
        }
        if (is_equal) return 1;
    }
    return 0;
}

static inline int is_alnumscore(int ch) { return ch == '_' || isalnum(ch); }
static inline int is_op(int c) { return c != EOF && strchr("+-*/%=!&|^~<>?:", c) != NULL; }
static inline int is_punct(int c) { return c != EOF && strchr(";?:(){}[].,", c) != NULL; }

Lexeme lexer_advance(int(*validate)(int))
{
    Lexeme s = { .ref = lex.buf + lex.i , .len = 0 };
    while (lex.i < lex.len && validate(lex.buf[lex.i])) {
        s.len++;
        lex.i++;
    }
    return s;
}

Lexeme lexer_advance_literal()
{
    Lexeme s = { .ref = lex.buf + lex.i , .len = 1 };
    char caret = lex.buf[lex.i++];
    if (caret == '"') {
        while (lex.i < lex.len && lex.buf[lex.i] != '"') { lex.i++; s.len++; }
    } else if (caret == '\'') {
        while (lex.i < lex.len && lex.buf[lex.i] != '\'') { lex.i++; s.len++; }
    }
    s.len++;
    lex.i++;
    return s;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("\nError: didn't recive any file as input\n"
               "usage: %s <file_name.c>\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    FILE *fp = fopen(argv[1], "r");
    assert(fp != NULL);

    fseek(fp, 0, SEEK_END);
    lex.len = ftell(fp);
    rewind(fp);
    lex.buf = malloc(sizeof(char) * lex.len + 1);
    assert(lex.buf != NULL);
    if ((int)fread(lex.buf, sizeof(char), lex.len, fp) != lex.len) {
        perror("fread");
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    lex.buf[lex.len] = '\0';
    printf(ANSI_BOLD "\n[[INPUT PROGRAM]]\n" ANSI_RESET);
    printf("%s\n", lex.buf);

    printf(ANSI_BOLD "\n[[TOKENS]]\n" ANSI_RESET);

    for (lex.i = 0; lex.i < lex.len;) {
        lexer_skip_comment();
        lexer_skip_macro();
        lexer_skip_ws();

        if (lex.i >= lex.len)
            break;

        int curr = (unsigned char)lex.buf[lex.i];

        Token tok = {0};

        if (isalpha(curr) || curr == '_') {
            tok.lexeme = lexer_advance(is_alnumscore);
            tok.type = is_keyword(&tok.lexeme) ? TOK_KEYWORD : TOK_IDENTIFIER;

        } else if (isdigit(curr)) {
            tok.lexeme = lexer_advance(isdigit);
            tok.type = TOK_LITERAL;

        } else if (curr == '\'' || curr == '"') {
            tok.lexeme = lexer_advance_literal();
            tok.type = TOK_LITERAL;

        } else if (is_punct(curr)) {
            tok.lexeme = (Lexeme) { .ref = lex.buf + lex.i, .len = 1 };
            lex.i++;
            tok.type = TOK_PUNCTUATION;

        } else if (is_op(curr)) {
            tok.lexeme = lexer_advance(is_op);            
            tok.type = TOK_OPERATOR;

        } else {
            tok.type = TOK_INVALID;
            lex.i++;
        }

        print_token(&tok);
    }

    free(lex.buf);
    return 0;
}
