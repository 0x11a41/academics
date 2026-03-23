// DISTANCE VECTOR ROUTING
#include <stdio.h>

#define MAX 10
#define INF 999

int cost[MAX][MAX];
int via[MAX][MAX];
int nodes;

int main() {
    int i, j, k;
    int updated;

    printf("Enter number of nodes:\n");
    scanf("%d", &nodes);

    printf("\nEnter routing cost matrix:\n");
    for(i = 0; i < nodes; i++) {
        for(j = 0; j < nodes; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    for(i = 0; i < nodes; i++)
        for(j = 0; j < nodes; j++)
            via[i][j] = j;

    do {
        updated = 0;
        for(i = 0; i < nodes; i++) {
            for(j = 0; j < nodes; j++) {
                for(k = 0; k < nodes; k++) {
                    if(cost[i][j] + cost[j][k] < cost[i][k]) {
                        cost[i][k] = cost[i][j] + cost[j][k];
                        via[i][k] = via[i][j];
                        updated = 1;
                    }
                }
            }
        }
    } while(updated);

    for(i = 0; i < nodes; i++) {
        printf("\nRouting table for router %c\n", i + 'A');
        for(j = 0; j < nodes; j++) {
            printf("To %c : Cost = %d via %c\n",
                    j + 'A',
                    cost[i][j],
                    via[i][j] + 'A');
        }
    }

    return 0;
}
