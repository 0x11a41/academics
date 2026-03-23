// worst fit
#include <stdio.h>

int main() {
  int b_count, p_count;
  printf("Enter number of blocks, process: ");
  scanf("%d%d", &b_count, &p_count);

  int blocks[b_count], proc[p_count], in_block[p_count];
  printf("Enter size of each block\n");
  for (int i = 0; i < b_count; i++)
    scanf("%d", &blocks[i]);
  printf("Enter size of each process\n");
  for (int i = 0; i < p_count; i++) {
    scanf("%d", &proc[i]);
    in_block[i] = -1;
  }

  for (int i = 0; i < p_count; i++) {
    int max_hole = -99999;
    int max_hole_pos = -1;
    for (int j = 0; j < b_count; j++) {
      if (in_block[i] != -1) break;
      int hole = blocks[j] - proc[i];
      if (hole >= 0 && hole > max_hole) {
        max_hole = hole;
        max_hole_pos = j;
      }
    }
    if (max_hole_pos != -1) {
      blocks[max_hole_pos] -= proc[i];
      in_block[i] = max_hole_pos;
    }
  }

  printf("processNo processSize blockNo\n");
  for (int i = 0; i < p_count; i++) {
    if (in_block[i] == -1) printf("%9d %11d Not allocd\n", i, proc[i]);
    else printf("%9d %11d %7d\n", i, proc[i], in_block[i] + 1);
  }
  return 0;
}
/*
OUTPUT:
Enter number of blocks, process: 3 5
Enter size of each block
150
256
80
Enter size of each process
16
200
64
170
96
processNo processSize blockNo
        0          16       2
        1         200       2
        2          64       1
        3         170 Not allocd
        4          96 Not allocd
*/
