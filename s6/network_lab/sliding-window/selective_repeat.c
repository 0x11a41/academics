// SELECTIVE REPEAT
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_SIZE 2
#define TOTAL_FRAMES 8
#define LOSS_CHANCE 20

int main() {
    srand(time(NULL));
    int s = 0, acked[TOTAL_FRAMES] = {0};

    while (s < TOTAL_FRAMES) {
        for (int i = s; i < s + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!acked[i]) {
                printf("SENDER: Sending Frame %d\n", i);
                usleep(400000);

                if (rand() % 100 < LOSS_CHANCE) {
                    printf("[NETWORK] Frame %d was lost\033[0m\n", i);
                } else {
                    printf("RECEIVER: Received Frame %d. Sending ACK %d\n", i, i);
                    acked[i] = 1;
                }
            }
        }

        // Slide window only if base frame is acknowledged
        while (s < TOTAL_FRAMES && acked[s]) {
            printf("SENDER: ACK %d received. Sliding Window...\n\n", s);
            s++;
        }
        usleep(500000);
    }

    printf("%d frames sent and acknowledged successfully\n", TOTAL_FRAMES);
    return 0;
}
