#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LOSS_THRESHOLD 30

int main()
{
  srand(time(NULL));
  int n = 4, i = 0, seq = 1;

  while (i < n) {
    printf("\n[sender] sending frame %d (seq: %d)\n", i, seq);
    int entropy = rand() % 100;
    sleep(1);
    if (entropy < LOSS_THRESHOLD) {
      printf("![NETWORK] frame lost\n");
      printf("[sender] Retransmitting frame %d\n", i);
    } else {
      printf("[receiver] frame %d received (seq: %d)\n", i, seq);
      printf("[receiver] sending ACK %d (seq: %d)\n", i, seq);
      entropy = rand() % 100;
      if (entropy < LOSS_THRESHOLD) {
        printf("![NETWORK] frame lost\n");
        printf("[sender] Retransmitting frame %d\n", i);
      } else {
        printf("[sender] ACK %d received (seq: %d)\n", i, seq);
        i++;
        seq ^= 1;
      }
    }
  }

  return 0;
}
