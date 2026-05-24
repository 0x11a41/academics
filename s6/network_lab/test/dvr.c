#include <stdio.h>

int main()
{
  printf("Enter number of nodes: ");
  int n;
  scanf("%d", &n);
  printf("\nEnter routing cost matrix\n");
  int cost[n][n], via[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &cost[i][j]);
      via[i][j] = j;
    }
  }

 int updated;
 do {
   updated = 0;
   for (int i = 0; i < n; i++) {
     for (int j = 0; j < n; j++) {
       for (int k = 0; k < n; k++) {
         if (cost[i][k] > cost[i][j] + cost[j][k]) {
           cost[i][k] = cost[i][j] + cost[j][k];
           via[i][k] = via[i][j];
           updated = 1;
         }
       }
     }
   }
 } while (updated);

 for (int i = 0; i < n; i++) {
   printf("Routing table for router %c\n", 'A' + i);
   for (int j = 0; j < n; j++) {
     printf("To %c: cost = %d via %c\n", 'A' + j, cost[i][j], via[i][j] + 'A');
   }
 }

  return 0;
}
