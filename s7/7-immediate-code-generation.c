#include <stdio.h>
#include <string.h>

#define MAX 50

int main()
{
    char expr[MAX];
    char temp = 'A';
    int i, j, len;

    printf("Enter the expression (e.g. a+b*c-d/e): ");
    scanf("%s", expr);

    len = strlen(expr);

    printf("\nIntermediate Code:\n");

    // ---------- Pass 1: Handle * and / ----------
    for (i = 0; i < len; i++) {
        if (expr[i] == '*' || expr[i] == '/') {
            j = i - 1;
            while (j >= 0 && expr[j] == ' ') j--;
            printf("%c = %c %c %c\n", temp, expr[j], expr[i], expr[i + 1]);

            expr[j]     = temp;
            expr[i]     = ' ';
            expr[i + 1] = ' ';
            temp++;     // Next temporary (B, C, D...)
        }
    }

    // ---------- Pass 2: Handle + and - ----------
    for (i = 0; i < len; i++) {
        if (expr[i] == '+' || expr[i] == '-') {
            j = i - 1;
            while (j >= 0 && expr[j] == ' ') j--;
            printf("%c = %c %c %c\n", temp, expr[j], expr[i], expr[i + 1]);

            expr[j] = temp;
            expr[i]     = ' ';
            expr[i + 1] = ' ';
            temp++;
        }
    }

    return 0;
}

/* OUTPUT:
Enter the expression (e.g. a+b*c-d/e): a+b*c/d+e

Intermediate Code:
A = b * c
B = A / d
C = a + B
D = C + e
*/
