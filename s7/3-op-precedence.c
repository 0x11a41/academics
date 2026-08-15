/* DESCRIPTION
check weather the given grammar is operator grammar or not.
terminal symbols: { id, +, -, $, (, ), *, / }
GRAMMAR: E-> (E) | E*E | E/E | E+E | E-E | i
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define LIM 64

#define ANSI_RESET   "\x1b[0m"
#define ANSI_BOLD    "\x1b[1m"
#define ANSI_GREEN   "\x1b[32m"

int failed = 0;

struct {
    char buf[LIM];
    int i;
    int len;
} ip = {0};

char stk[LIM];
int top = -1;

void printarr(char *arr, int start, int len)
{
    for (int i = start; i < len; i++) {
        printf("%c", arr[i]);
    }
}

static inline void push(char ch)
{
    if (top >= LIM - 1) {
        failed = 1;
        fprintf(stderr, "\nSTACK OVERFLOW\n");
        exit(EXIT_FAILURE);
    }
    stk[++top] = ch;
    stk[top + 1] = '\0';
}

static inline void shift()
{
    if (ip.i >= ip.len) {
        failed = 1;
        fprintf(stderr, "\nIP OVERFLOW\n");
        exit(EXIT_FAILURE);
    }
    push(ip.buf[ip.i++]);
}

int stk_ends_with(const char *suffix)
{
    int len = strlen(suffix);
    if ((top + 1) < len) return 0;
    return strcmp(stk + (top + 1) - len, suffix) == 0;
}

int is_valid_precedence(void)
{
    if (stk_ends_with("i") || stk_ends_with("(E)")) {
        return 1;
    }

    if (stk_ends_with("E*E") || stk_ends_with("E/E")) {
        return 1;
    }

    if (stk_ends_with("E+E") || stk_ends_with("E-E")) {
        const char s = ip.buf[ip.i];
        if (s == '*' || s == '/' || s == '(') {
            return 0;
        }
        return 1;
    }

    return 0;
}

int try_reduce(void)
{
    if (!is_valid_precedence()) {
        return 0;
    }

    if (stk_ends_with("(E)")) {
        top -= 3;
        push('E');
        printf("Reduce: E->(E)\n");
        return 1;
    } 
    else if (stk_ends_with("E*E")) {
        top -= 3;     
        push('E');
        printf("Reduce: E->E*E\n");
        return 1;
    } 
    else if (stk_ends_with("E/E")) {
        top -= 3;     
        push('E');
        printf("Reduce: E->E/E\n");
        return 1;
    } 
    else if (stk_ends_with("E+E")) {
        top -= 3;     
        push('E');
        printf("Reduce: E->E+E\n");
        return 1;
    } 
    else if (stk_ends_with("E-E")) {
        top -= 3;     
        push('E');
        printf("Reduce: E->E-E\n");
        return 1;
    } 
    else if (stk_ends_with("i")) {
        stk[top] = 'E';
        printf("Reduce: E->i\n");
        return 1;
    }

    return 0;
}

void reject(void)
{
    if (failed) {
        printf("%s is not an operator grammar\n", ip.buf);
    }
}

int main()
{
    atexit(reject);

    printf("Enter rule: ");
    assert(fgets(ip.buf, sizeof(ip.buf), stdin) != NULL);

    ip.len = strlen(ip.buf);
    ip.buf[ip.len - 1] = '$';
    stk[++top] = '$';

    printf(ANSI_BOLD "STACK\tINPUT\tACTION\n" ANSI_RESET);

    while (1) {
        printarr(stk, 0, top + 1);
        printf("\t");
        printarr(ip.buf, ip.i, ip.len);
        printf("\t");
        fflush(stdout);

        if (try_reduce()) continue;

        if (strcmp(stk, "$E") == 0 && ip.buf[ip.i] == '$') {
            printf(ANSI_BOLD ANSI_GREEN "Accepted\n" ANSI_RESET);
            break;
        }
        
        shift();
        printf("Shift\n");
    }

    printf("%s is an operator grammar\n", ip.buf);
    return 0;
}

/* OUTPUT:
    Enter rule: i*i
    STACK	INPUT	ACTION
    $	    i*i$	Shift
    $i	    *i$	    Reduce: E->i
    $E	    *i$	    Shift
    $E*	    i$	    Shift
    $E*i	$	    Reduce: E->i
    $E*E	$	    Reduce: E->E*E
    $E	    $   	Accepted
    i*i$ is an operator grammar
*/
