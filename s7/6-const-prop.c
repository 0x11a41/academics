#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_STMTS 20
#define MAX_LEN   50

char stmts[MAX_STMTS][MAX_LEN];
int n;

int is_constant(const char *s)
{
    if (*s == '-' || *s == '+') s++;
    if (!*s) return 0;
    while (*s) {
        if (!isdigit(*s)) return 0;
        s++;
    }
    return 1;
}

// Simple constant folding for expressions like "5+3", "12*4", etc.
// Returns 1 if folding succeeded and result is written into 'result'
int fold_constant_expr(const char *expr, char *result) {
    char left[20], right[20], op;
    int i = 0, j = 0;

    // Extract left operand
    if (expr[0] == '-' || expr[0] == '+') left[j++] = expr[i++];
    while (isdigit(expr[i])) left[j++] = expr[i++];
    left[j] = '\0';

    if (!is_constant(left) || expr[i] == '\0') return 0;

    op = expr[i++];
    if (op != '+' && op != '-' && op != '*' && op != '/') return 0;

    j = 0;
    if (expr[i] == '-' || expr[i] == '+') right[j++] = expr[i++];
    while (isdigit(expr[i])) right[j++] = expr[i++];
    right[j] = '\0';

    if (!is_constant(right) || expr[i] != '\0') return 0;

    int l = atoi(left);
    int r = atoi(right);
    int res;

    switch (op) {
        case '+': res = l + r; break;
        case '-': res = l - r; break;
        case '*': res = l * r; break;
        case '/': 
            if (r == 0) return 0;
            res = l / r; 
            break;
        default: return 0;
    }

    sprintf(result, "%d", res);
    return 1;
}

int main() {
    printf("Simple Constant Propagation + Folding\n");
    printf("Enter number of statements: ");
    scanf("%d", &n);
    getchar();

    printf("Enter statements (example: a=5   or   b=a+3):\n");
    for (int i = 0; i < n; i++) {
        printf("Statement %d: ", i + 1);
        assert(fgets(stmts[i], MAX_LEN, stdin) != NULL);
        stmts[i][strcspn(stmts[i], "\n")] = '\0';
    }

    for (int i = 0; i < n; i++) {
        char var = stmts[i][0];
        char *eq = strchr(stmts[i], '=');
        if (!eq) continue;

        char *rhs = eq + 1;

        char folded[20];
        if (fold_constant_expr(rhs, folded)) {
            sprintf(eq + 1, "%s", folded);
            rhs = eq + 1;
        }

        if (is_constant(rhs)) {
            char constant[20];
            strcpy(constant, rhs);

            // Replace the variable with the constant in later statements
            for (int j = i + 1; j < n; j++) {
                for (int k = 0; stmts[j][k]; k++) {
                    if (stmts[j][k] == var) {
                        // Replace single character variable with the constant string
                        // (simple version – works best when variable is a single letter)
                        char temp[MAX_LEN];
                        stmts[j][k] = '\0';
                        sprintf(temp, "%s%s%s", stmts[j], constant, stmts[j] + k + 1);
                        strcpy(stmts[j], temp);
                        break;  // only replace first occurrence for simplicity
                    }
                }
            }
        }
    }

    printf("\nStatements after constant propagation + folding:\n");
    for (int i = 0; i < n; i++) {
        if (stmts[i][0] != '\0')
            printf("%s\n", stmts[i]);
    }

    return 0;
}

/* OUTPUT:
Simple Constant Propagation + Folding
Enter number of statements: 4
Enter statements (example: a=5   or   b=a+3):
Statement 1: a=2+2
Statement 2: b=c+a
Statement 3: c=a*5
Statement 4: d=c/a

Statements after constant propagation + folding:
a=4
b=c+4
c=20
d=5
*/
