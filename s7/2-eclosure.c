/* INPUT GRAMMAR RULES
    T      := (<from> <symbol> <to>)*
    from   := 0-9
    symbol := a-z | A-Z | 0-9 | # ; # means epsilon
    to     := 0-9
*/

#include <stdio.h>
#include <string.h>

#define ANSI_RESET   "\x1b[0m"
#define ANSI_BOLD    "\x1b[1m"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define LIM 32
int adj[LIM][LIM];
int visited[LIM];

void dfs(int state, int closure[], int *closure_size)
{
    visited[state] = 1;
    closure[*closure_size] = state;
    (*closure_size)++;
    for (int i = 0; i < LIM && adj[state][i] != -1; i++) {
        int neighbor = adj[state][i];
        if (!visited[neighbor]) {
            dfs(neighbor, closure, closure_size);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    memset(adj, -1, sizeof(adj));

    int  from, to;
    char symbol;
    int max_state = -1;

    printf(ANSI_BOLD "[ STATE TRANSITIONS ]\n" ANSI_RESET);
    while (fscanf(fp, " %d %c %d", &from, &symbol, &to) == 3) {
        printf("q%d [%c]-> q%d\n", from, symbol, to);

        max_state = MAX(max_state, MAX(from, to));
        if (symbol != '#') continue;

        for (int i = 0; i < LIM; i++) {
            if (adj[from][i] == -1) {
                adj[from][i] = to;
                break;
            }
        }
    }
    fclose(fp);

    printf(ANSI_BOLD "\n[ E-CLOSURE ]\n" ANSI_RESET);
    for (int state = 0; state <= max_state; state++) {
        int closure[LIM], size = 0;
        memset(visited, 0, sizeof(visited));

        dfs(state, closure, &size);

        printf("E-Closure(q%d) := { ", state);
        for (int i = 0; i < size; i++) {
            printf("q%d ", closure[i]);
        }
        printf("}\n");
    }

    return 0;
}

/* OUTPUT:
[ STATE TRANSITIONS ]
q0 [a]-> q1
q0 [b]-> q2
q1 [#]-> q0
q2 [#]-> q1
q2 [a]-> q3
q2 [b]-> q0
q3 [a]-> q1
q3 [b]-> q2

[ E-CLOSURE ]
E-Closure(q0) := { q0 }
E-Closure(q1) := { q1 q0 }
E-Closure(q2) := { q2 q1 q0 }
E-Closure(q3) := { q3 }
*/
