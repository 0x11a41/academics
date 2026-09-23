#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN_LIM 16

int n;
char s[LEN_LIM][LEN_LIM];

struct expr {
    char *stmt;
    char lhs[LEN_LIM];
    struct {
        char a[LEN_LIM], op, b[LEN_LIM];
    } rhs;
};

void copy_operand(char **s, char *dest)
{
    int i;
    for (i = 0; *s && isalnum(**s); (*s)++, i++) dest[i] = **s;
    dest[i] = '\0';
}

int expr_create(char *s, struct expr *e)
{
    e->stmt = s;
    copy_operand(&s, e->lhs);

    if (*s != '=') return 0;
    s++;

    copy_operand(&s, e->rhs.a);

    e->rhs.op = *s;
    if (*s == '\0') {
        *e->rhs.b = '\0';
        return 1;
    }
    s++;

    copy_operand(&s, e->rhs.b);
    return 1;
}

int is_constant(const struct expr *e) { return e->rhs.op == 0; }

int isnum(const char *s)
{
    if (!s) return 0;
    while (*s != '\0') {
        if (!isdigit(*s)) return 0;
        s++;
    }
    return 1;
}

int can_fold(const struct expr *e)
{
    if (is_constant(e)) return 0;
    if (!isnum(e->rhs.a) || !isnum(e->rhs.b)) return 0;
    return 1;
}

void fold(struct expr *e)
{
    int a = atoi(e->rhs.a);
    int b = atoi(e->rhs.b);
    int r;
    switch (e->rhs.op) {
        case '+': r = a + b; break;
        case '-': r = a - b; break;
        case '/': r = a / b; break;
        case '*': r = a * b; break;
        case '%': r = a % b; break;
        default:
            printf("ERR! invalid operator found in statement: %s", e->stmt);
            return;
    }

    sprintf(e->stmt, "%s=%d", e->lhs, r);
    expr_create(e->stmt, e);
}

void propogate_constant(int stmt_id, const struct expr *e)
{
    for (int i = stmt_id + 1; i < n; i++) {
        struct expr tmp = {0};
        expr_create(s[i], &tmp);

        int flag = 0;
        if (strcmp(e->lhs, tmp.rhs.a) == 0) {
            strcpy(tmp.rhs.a, e->rhs.a);
            flag = 1;
        } else if (strcmp(e->lhs, tmp.rhs.b) == 0) {
            flag = 1;
            strcpy(tmp.rhs.b, e->rhs.a);
        }

        if (flag) {
            sprintf(tmp.stmt, "%s=%s%c%s", tmp.lhs, tmp.rhs.a, tmp.rhs.op, tmp.rhs.b);
        }
    }
}

int main()
{
    printf("Enter the number of statements: ");
    scanf("%d", &n);
    getchar();

    printf("Enter statements\n");

    for (int i = 0; i < n; ++i) {
        printf("\tS%d: ", i + 1);
        assert(fgets(s[i], LEN_LIM, stdin) != NULL);
        s[i][strlen(s[i]) - 1] = '\0';
    }

    struct expr e;
    for (int i = 0; i < n; i++) {
        e = (struct expr){0};
        if (!expr_create(s[i], &e)) {
            printf("cannot interpert expression: %s\n", s[i]);
            continue;
        };
        
        if (can_fold(&e)) fold(&e);

        if (is_constant(&e)) propogate_constant(i, &e);
    }

    printf("result\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", s[i]);
    }
    
    return 0;
}

/* OUTPUT
Enter the number of statements: 4
Enter statements
	S1: a=2+2
	S2: b=c+a
	S3: c=a*5
	S4: d=c/a
result
a=4
b=c+4
c=20
d=5
*/

