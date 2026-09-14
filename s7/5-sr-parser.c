/* shift reduce parser
GRAMMAR:
    E → (E) | E*E | E/E | E+E | E-E | i
*/

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAXSIZ 64

char stk[MAXSIZ];
int top = -1;

struct {
    char buf[MAXSIZ];
    int len;
    int curr;
} ip = {0};

char ipnxt()
{
    if (ip.curr >= ip.len) return '\0';
    char ch = ip.buf[ip.curr];
    ip.curr++;
    return ch;
}

char currip()
{
    if (ip.curr >= ip.len || ip.curr < 0) return '\0';
    return ip.buf[ip.curr];
}

void push(char ch)
{
    assert(top < MAXSIZ);
    stk[++top] = ch;
}

int peek(int offset)
{
    assert(top > -1);
    return stk[top + offset];
}

char pop()
{
    assert(top > -1);
    return stk[top--];
}

void get_input()
{
    printf("Enter input string: ");
    assert(fgets(ip.buf, sizeof(ip.buf) - 1, stdin) != NULL);
    ip.len = strlen(ip.buf);
    ip.buf[ip.len - 1] = '$';
    ip.buf[ip.len] = '\0';
    ip.curr = 0;
}

static inline int is_binary_op(char ch)
{
    return ch == '-' || ch == '+' || ch == '*' || ch == '/';
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int can_reduce()
{
    if (top >= 2 && peek(0) == ')' && peek(-1) == 'E' && peek(-2) == '(') return 1;
    if (top >= 2 && peek(0) == 'E' && is_binary_op(peek(-1)) && peek(-2) == 'E') {
        char op = peek(-1);
        char nxt = currip();
        if (nxt == '$' || nxt == ')' || precedence(op) >= precedence(nxt)) {
            return 1;
        }
    }
    if (peek(0) == 'i') return 1;
    return 0;

}

int try_reduce()
{
    if (!can_reduce()) goto NOPE;

    printf("Reduce by: ");
    if (top >= 2 && peek(0) == ')' && peek(-1) == 'E' && peek(-2) == '(') {
        pop(); pop(); pop();
        push('E');
        printf("E -> (E)\n");
        return 1;
    }

    if (top >= 2 && peek(0) == 'E' && is_binary_op(peek(-1)) && peek(-2) == 'E') {
        char op = peek(-1);
        pop(); pop(); pop();
        push('E');
        printf("E -> E%cE\n", op);
        return 1;
    }

    if (peek(0) == 'i') {
        pop();
        push('E');
        printf("E -> i\n");
        return 1;
    }

    NOPE:
        return 0;
}

int main(void)
{
    printf("GRAMMAR: \n\tE -> (E)\n\tE -> E*E\n\tE -> E/E\n\tE -> E+E\n\tE -> E-E\n\tE -> i\n");
    get_input();
    push('$');

    printf("\n%-16s %-16s %s\n", "STACK", "INPUT", "OPERATION");

    while (1) {
        for (int i = 0; i <= top; i++) { printf("%c", stk[i]); }
        printf("%*s", 16 - top, "");

        printf("%s", ip.buf + ip.curr);
        printf("%*s", 16 - ip.len + ip.curr + 1, "");

        if (top == 1 && peek(0) == 'E' && peek(-1) == '$' && currip() == '$') {
            printf("Accept\n");
            break;
        }

        if (try_reduce()) {
            continue;
        }

        if (currip() == '$') {
            printf("\nUnexpected error. end of input!\n");
            break;
        }

        push(ipnxt());
        printf("Shift\n");
    }
    return 0;
}

/* OUTPUT:
GRAMMAR:
	E -> (E)
	E -> E*E
	E -> E/E
	E -> E+E
	E -> E-E
	E -> i
Enter input string: (i)

STACK            INPUT            OPERATION
$                (i)$             Shift
$(               i)$              Shift
$(i              )$               Reduce by: E -> i
$(E              )$               Shift
$(E)             $                Reduce by: E -> (E)
$E               $                Accept
*/
