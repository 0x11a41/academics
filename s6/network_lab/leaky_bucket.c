#include <stdio.h>

int main()
{
    int capacity, leak_rate, incoming, dropped, stored = 0;
    printf("bucket capacity: ");
    scanf("%d", &capacity);
    printf("leak rate: ");
    scanf("%d", &leak_rate);
    printf("Enter ctrl + c to stop this\n");
    while (1) {
        printf("\nincoming packet size: ");
        scanf("%d", &incoming);
        if (incoming <= (capacity - stored)) {
            stored += incoming;
        } else {
            dropped = incoming - (capacity - stored);
            stored = capacity;
            printf("Dropped %d bytes\n", dropped);
        }
        printf("Bucket occupancy: [%d/%d]\n", stored, capacity);
        printf("sending packets..\n");
        stored -= leak_rate;
        if (stored < 0) stored = 0;
        printf("Bucket occupancy: [%d/%d]\n", stored, capacity);
    }
    return 0;
}
