// three address code to 8086 assembly conversion
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char a[20], ch;

    printf("Three address code: ");
    assert(fgets(a, sizeof(a), stdin) != NULL);
    a[strcspn(a, "\n")] = '\0';

    ch = a[3];

    switch (ch)
    {
        case '+':
            printf("MOV R0, %c\n", a[2]);
            printf("ADD R0, %c\n", a[4]);
            printf("MOV %c, R0\n", a[0]);
            break;

        case '-':
            printf("MOV R0, %c\n", a[2]);
            printf("SUB R0, %c\n", a[4]);
            printf("MOV %c, R0\n", a[0]);
            break;

        case '*':
            printf("MOV R0, %c\n", a[2]);
            printf("MUL R0, %c\n", a[4]);
            printf("MOV %c, R0\n", a[0]);
            break;

        case '/':
            printf("MOV R0, %c\n", a[2]);
            printf("DIV R0, %c\n", a[4]);
            printf("MOV %c, R0\n", a[0]);
            break;

        default:
            printf("INVALID\n");
    }

    return 0;
}

/*OUTPUT
Three address code: A=B+C
MOV R0, B
ADD R0, C
MOV A, R0
*/
