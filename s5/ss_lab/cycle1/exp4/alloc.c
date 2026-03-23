// first-fit, best-fit and worst fit allocation
#include <stdio.h>
#include <string.h>

void display(int p_count, int in_block[], int proc[]) {
  printf("processNo processSize blockNo\n");
  for (int i = 0; i < p_count; i++) {
    if (in_block[i] == -1) printf("%9d %11d Not allocated\n", i, proc[i]);
    else printf("%9d %11d %7d\n", i, proc[i], in_block[i]);
  }
}

int main() {
  int b_count, p_count;
  printf("Enter number of blocks, process: ");
  scanf("%d%d", &b_count, &p_count);

  int blocks[b_count], blocks_cpy[b_count], proc[p_count], in_block[p_count];
  printf("Enter size of each block\n");
  for (int i = 0; i < b_count; i++) scanf("%d", &blocks[i]);
  printf("Enter size of each process\n");
  for (int i = 0; i < p_count; i++) scanf("%d", &proc[i]);    

  printf("\nFirst fit\n");
  memcpy(blocks_cpy, blocks, sizeof(int) * b_count);
  memset(in_block, -1, sizeof(int) * p_count);
  for (int i = 0; i < p_count; i++) {
    for (int j = 0; j < b_count; j++) {
      if (blocks_cpy[j] >= proc[i] && in_block[i] == -1) {
        blocks_cpy[j] = blocks_cpy[j] - proc[i];
        in_block[i] = j;
      }
    }
  }
  display(p_count, in_block, proc);

  printf("\nBest fit\n");
  memcpy(blocks_cpy, blocks, sizeof(int) * b_count);
  memset(in_block, -1, sizeof(int) * p_count);
  for (int i = 0; i < p_count; i++) {
    int minimum_hole = 99999;
    int min_hole_pos = -1;
    for (int j = 0; j < b_count; j++) {
      if (in_block[i] != -1) break;
      int hole = blocks_cpy[j] - proc[i];
      if (hole >= 0 && hole < minimum_hole) {
        minimum_hole = hole;
        min_hole_pos = j;
      }
    }
    if (min_hole_pos != -1) {
      blocks_cpy[min_hole_pos] -= proc[i];
      in_block[i] = min_hole_pos;
    }
  }
  display(p_count, in_block, proc);

  printf("\nWorst fit\n");
  memcpy(blocks_cpy, blocks, sizeof(int) * b_count);
  memset(in_block, -1, sizeof(int) * p_count);
  for (int i = 0; i < p_count; i++) {
    int max_hole = -9999;
    int max_hole_pos = -1;
    for (int j = 0; j < b_count; j++) {
      if (in_block[i] != -1) break;
      int hole = blocks_cpy[j] - proc[i];
      if (hole >= 0 && hole > max_hole) {
        max_hole = hole;
        max_hole_pos = j;
      }
    }
    if (max_hole_pos != -1) {
      blocks_cpy[max_hole_pos] -= proc[i];
      in_block[i] = max_hole_pos;
    }
  }
  display(p_count, in_block, proc);

  return 0;
}

/*
OUTPUT:
Enter number of blocks, process: 2 3
Enter size of each block
100
200
Enter size of each process
60
40
250

First fit
processNo processSize blockNo
        0          60       0
        1          40       0
        2         250 Not allocated

Best fit
processNo processSize blockNo
        0          60       0
        1          40       0
        2         250 Not allocated

Worst fit
processNo processSize blockNo
        0          60       1
        1          40       1
        2         250 Not allocated
*/
