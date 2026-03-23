// priority scheduling
#include <stdio.h>

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main() {
  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  int priority[n], p[n], bt[n], wt[n], tat[n], total_wt = 0, total_tat = 0;
  printf("Enter bt of each process\n");
  for (int i = 0; i < n; i++) {
    printf("bt, priority of p%d = ", i + 1);
    scanf("%d%d", &bt[i], &priority[i]);
    p[i] = i + 1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (priority[j] > priority[j + 1]) {
        swap(&priority[j], &priority[j + 1]);
        swap(&bt[j], &bt[j + 1]);
        swap(&p[j], &p[j + 1]);
      }
    }
  }

  wt[0] = 0;
  for (int i = 1; i < n; i++) {
    wt[i] = wt[i - 1] + bt[i - 1];
    total_wt += wt[i];
  }
  for (int i = 0; i < n; i++) {
    tat[i] = wt[i] + bt[i];
    total_tat += tat[i];
  }

  printf("\nprocess priority bt wt tat\n");
  for (int i = 0; i < n; i++) {
    printf("%7d %8d %2d %2d %3d\n", p[i], priority[i], bt[i], wt[i], tat[i]);
  }
  printf("avg wt is %.2f\n", (float)total_wt / n);
  printf("avg tat is %.2f\n", (float)total_tat / n);
  return 0;
}

/*
Enter number of processes: 4
Enter bt of each process
bt, priority of p1 = 3 5
bt, priority of p2 = 2 3
bt, priority of p3 = 2 2
bt, priority of p4 = 5 1

process priority bt wt tat
      4        1  5  0   5
      3        2  2  5   7
      2        3  2  7   9
      1        5  3  9  12
avg wt is 5.25
avg tat is 8.25

*/
