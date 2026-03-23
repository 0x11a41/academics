// sjf
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
  int p[n], bt[n], wt[n], tat[n], total_wt = 0, total_tat = 0;
  printf("Enter bt of each process\n");
  for (int i = 0; i < n; i++) {
    printf("bt of p%d = ", i + 1);
    scanf("%d", &bt[i]);
    p[i] = i + 1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (bt[j] > bt[j + 1]) {
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

  printf("\nprocess bt wt tat\n");
  for (int i = 0; i < n; i++) {
    printf("%7d %2d %2d %3d\n", p[i], bt[i], wt[i], tat[i]);
  }
  printf("avg wt is %.2f\n", (float)total_wt / n);
  printf("avg tat is %.2f\n", (float)total_tat / n);
  return 0;
}

/*
Enter number of processes: 4
Enter bt of each process
bt of p1 = 5
bt of p2 = 3
bt of p3 = 7
bt of p4 = 1

process bt wt tat
      4  1  0   1
      2  3  1   4
      1  5  4   9
      3  7  9  16
avg wt is 3.50
avg tat is 7.50
*/
