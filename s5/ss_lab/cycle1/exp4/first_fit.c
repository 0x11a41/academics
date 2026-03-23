// first fit
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
    for (int j = 0; j < b_count; j++) {
      if (blocks[j] >= proc[i] && in_block[i] == -1) {
        blocks[j] = blocks[j] - proc[i];
        in_block[i] = j;
      }
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
        0          16       3
        1         200       2
        2          64       3
        3         170 Not allocd
        4          96       1
*/
