// STOP_AND_WAIT
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_FRAMES 4
#define LOSS_CHANCE 30

int main() {
    srand(time(NULL));
    int current_frame = 0;
    int seq_num = 0;
    bool ack_received = false;

    while (current_frame < TOTAL_FRAMES) {
        printf("SENDER: Sending Frame %d (Seq: %d)\n", current_frame, seq_num);

        sleep(1);

        int random_event = rand() % 100;
        if (random_event < LOSS_CHANCE) { // frame lost
            printf("[NETWORK] ! Frame %d was lost.\n", current_frame);
            printf("SENDER: Timeout! No ACK received. Retransmitting\n\n");
        } else {
            printf("RECEIVER: Frame %d received. Sending ACK %d\n", current_frame, seq_num);

            random_event = rand() % 100;
            if (random_event < (LOSS_CHANCE / 2)) {
                printf("[NETWORK] ! ACK %d was lost.\n", seq_num);
                printf("SENDER: No ACK received. Retransmitting\n\n");
            } else {
                printf("SENDER: ACK %d received successfully.\n\n", seq_num);
                current_frame++;
                seq_num ^= 1;
            }
        }
    }

    printf("%d frames transmitted successfully.\n", TOTAL_FRAMES);
    return 0;
}
