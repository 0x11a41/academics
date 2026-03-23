// round robin
#include <stdio.h>
#include <stdbool.h>

int main() {
  printf("Enter number of processes: ");
  int n;
  scanf("%d", &n);

  int bt[n], at[n], tat[n], ct[n], wt[n], p[n], rem_bt[n];
  printf("Enter at, bt of each process\n");
  for (int i = 0; i < n; i++) {
    printf("at and bt of p%d = ", i+1);
    scanf("%d%d", &at[i], &bt[i]);
    rem_bt[i] = bt[i];
    p[i] = i + 1;
    wt[i] = tat[i] = ct[i] = 0;
  }
  printf("Enter time slice: ");
  int time_slice, time = 0, completed = 0, total_tat = 0, total_wt = 0;
  scanf("%d", &time_slice);

  printf("\np[]\tat\tbt\tct\ttat\twt\n");
  while (completed < n) {
    bool executed_in_cycle = false;
    for (int i = 0; i < n; i++) {
      if (at[i] <= time && rem_bt[i] > 0) {
        if (rem_bt[i] <= time_slice) {
          time += rem_bt[i];
          rem_bt[i] = 0;
        } else {
          time += time_slice;
          rem_bt[i] -= time_slice;
        }

        if (rem_bt[i] == 0) {
          completed++;
          ct[i] = time;
          tat[i] = ct[i] - at[i];
          wt[i] = tat[i] - bt[i];
          total_tat += tat[i];
          total_wt += wt[i];
          printf("%3d\t%2d\t%2d\t%2d\t%3d\t%2d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        }
        executed_in_cycle = true;
      }
    }
    if (!executed_in_cycle) time++;
  }

  printf("avg tat = %.2f\n", (float)total_tat / n);
  printf("avg wt = %.2f\n", (float)total_wt / n);
  return 0;
}

/*
OUTPUT:
Enter number of processes: 4
Enter at, bt of each process
at and bt of p1 = 0 5
at and bt of p2 = 1 7
at and bt of p3 = 3 4
at and bt of p4 = 5 6
Enter time slice: 3

p[]	at	bt	ct	tat	wt
  1	 0	 5	14	 14	 9
  3	 3	 4	18	 15	11
  4	 5	 6	21	 16	10
  2	 1	 7	22	 21	14
avg tat = 16.50
avg wt = 11.00
*/
