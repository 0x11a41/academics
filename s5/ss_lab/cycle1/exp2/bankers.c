// bankers algorithm
#include <stdio.h>
#include <stdbool.h>

void print_mat(int row, int col, int mat[row][col], char* name) {
  printf("\n%s:\n", name);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("%d\t", mat[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int proc, res;
  printf("Enter [number of processes], [number of shared resources]: ");
  scanf("%d %d", &proc, &res);

  int allocation[proc][res], max[proc][res], available[res], need[proc][res];

  printf("\n## Enter current allocation matrix:\n");
  for (int i = 0; i < proc; i++) {
    for (int j = 0; j < res; j++) {
      printf("P%d, R%d = ", i, j);
      scanf("%d", &allocation[i][j]);
    }
  }

  printf("\n## Enter max need of each resources:\n");
  for (int i = 0; i < proc; i++) {
    for (int j = 0; j < res; j++) {
      printf("P%d, R%d = ", i, j);
      scanf("%d", &max[i][j]);
    }
  }

  printf("\n## Enter current availability of each resource: \n");
  for (int i = 0; i < res; i++) {
    printf("R%d = ", i);
    scanf("%d", &available[i]);
  }

  // evaluating need matrix
  for (int i = 0; i < proc; i++) {
    for (int j = 0; j < res; j++) {
      need[i][j] = max[i][j] - allocation[i][j];
    }
  }

  print_mat(proc, res, need, "NEED");
  print_mat(proc, res, max, "MAX");
  print_mat(proc, res, allocation, "ALLOCATION");

  bool completed[proc], process_found;
  for (int i = 0; i < proc; i++) completed[i] = false;

  int safe_seq[proc], k = 0, pos, count, finished = 0;

  printf("\nEstimating safe sequence...\n");
  while (finished < proc) {
    process_found = false;

    for (int i = 0; i < proc; i++) {
      if (completed[i]) {
        continue;
      }
      count = 0;
      for (int j = 0; j < res && need[i][j] <= available[j]; j++) {
        count++;
      }
      if (count == res) {
        pos = i;
        process_found = true;
        break;
      } 
    }

    if (process_found == true) {
      completed[pos] = true;
      finished++;
      for (int j = 0; j < res; j++) {
        available[j] += allocation[pos][j];
      }
      safe_seq[k] = pos;
      k++;
    } else {
      printf("The system is in unsafe state.\nDeadlock can't be avoided.\n");
      return 1;
    }
  }

  printf("The system is in safe state.\nsafe sequence is :");
  for (int i = 0; i < proc; i++) {
    printf("P%d -> ", safe_seq[i]);
  }
  printf("END\n");
  return 0;
}
/*
OUTPUT
Enter [number of processes], [number of shared resources]: 2 2

## Enter current allocation matrix:
P0, R0 = 0
P0, R1 = 1
P1, R0 = 0
P1, R1 = 1

## Enter max need of each resources:
P0, R0 = 1
P0, R1 = 3
P1, R0 = 0
P1, R1 = 1

## Enter current availability of each resource: 
R0 = 3
R1 = 3

NEED:
1	2	
0	0	

MAX:
1	3	
0	1	

ALLOCATION:
0	1	
0	1	

Estimating safe sequence...
The system is in safe state.
safe sequence is :P0 -> P1 -> END
*/
