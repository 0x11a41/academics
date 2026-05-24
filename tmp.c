#include <stdio.h>
#include <assert.h>

int main() {
  int cost[10][10], via[10][10], nodes;
  printf("enter number of nodes: ");
  scanf("%d", &nodes);
  assert(nodes > 1);
  printf("\nEnter routing cost matrix:\n");
  for(int i = 0; i < nodes; i++) {
    for (int j = 0; j < nodes; j++) {
      scanf("%d", &cost[i][j]);
    }
  }

  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < nodes; j++) {
      via[i][j] = j;
    }
  }

  int updated = 0;
  do {
    updated = 0;
    for (int i = 0; i < nodes; i++) {
      for (int j = 0; j < nodes; ++j) {
        for (int k = 0; k < nodes; ++k) {
          if (cost[i][j] + cost[j][k] < cost[i][k]) {
            cost[i][k] = cost[i][j] + cost[j][k];
            via[i][k] = via[i][j];
            updated = 1;
          }
        }
      }
    }
  } while(updated);

  for (int i = 0; i < nodes; i++) {
    printf("\nRouting table for router %c\n", i + 'A');
    for (int j = 0; j < nodes; j++) {
      printf("cost[%c --> %c] = %d, via %c\n", i + 'A', j + 'A', cost[i][j], via[i][j] + 'A');
    }
  }

  return 0;
}
