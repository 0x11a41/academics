#include <stdio.h>

int main() {
  int n;
  printf("enter number of nodes: ");
  scanf("%d", &n);
  int cost[n][n], via[n][n];

  printf("\nEnter routing cost matrix:\n");
  for(int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &cost[i][j]);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      via[i][j] = j;
    }
  }

  int updated = 0;
  do {
    updated = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          if (cost[i][j] + cost[j][k] < cost[i][k]) {
            cost[i][k] = cost[i][j] + cost[j][k];
            via[i][k] = via[i][j];
            updated = 1;
          }
        }
      }
    }
  } while(updated);

  for (int i = 0; i < n; i++) {
    printf("\nRouting table for router %c\n", i + 'A');
    for (int j = 0; j < n; j++) {
      printf("cost[%c --> %c] = %d, via %c\n", i + 'A', j + 'A', cost[i][j], via[i][j] + 'A');
    }
  }

  return 0;
}
