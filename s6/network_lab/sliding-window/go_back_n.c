#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOSS_CHANCE 20

int main()
{
    srand(time(NULL));
    int win_size, n, s = 0;
    printf("Enter total frames: ");
    scanf("%d", &n);
    printf("Enter window size: ");
    scanf("%d", &win_size);
    int acked[n], expected_frame = 0;
    for (int i = 0; i < n; i++) acked[i] = 0;

    while (s < n) {
        for (int i = s; i < n && i < s + win_size; i++) {
            printf("\n[sender] sending frame %d\n", i);

            if (rand() % 100 < LOSS_CHANCE) {
                printf("![NETWORK] frame lost.\n");
            } else {
                printf("[receiver] got frame %d.\n", i);

                if (i == expected_frame) {
                    printf("[receiver] frame %d is expected. sending ACK...\n", i);

                    if (rand() % 100 < LOSS_CHANCE) {
                        printf("![NETWORK] ACK lost.\n");
                    } else {
                        printf("[sender] got ACK (frame %d)\n", i);
                        acked[i] = 1;
                        expected_frame++;
                    }
                } else {
                    printf("[receiver] frame %d is out of order (expected %d). Dropping\n", i, expected_frame);
                }
            }
        }

        while (s < n && acked[s]) {
            s++;
            printf("sliding window... [%d -> %d]\n", s - 1, s);
        }
    }
    return 0;
}
