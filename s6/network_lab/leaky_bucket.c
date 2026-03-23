// LEAKY BUCKET
#include <stdio.h>

int main() {
    int bucket_size, incoming, outgoing, n;
    int store = 0, dropped;

    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);

    printf("Enter number of packet inputs: ");
    scanf("%d", &n);

    printf("Enter outgoing rate: ");
    scanf("%d", &outgoing);

    while (n != 0) {
        printf("\nEnter incoming packet size: ");
        scanf("%d", &incoming);

        if (incoming <= (bucket_size - store)) {
            store = store + incoming;
            printf("Bucket buffer size = %d out of %d\n", store, bucket_size);
        } else {
            dropped = incoming - (bucket_size - store);
            store = bucket_size;
            printf("Dropped packets = %d\n", dropped);
            printf("Bucket buffer size = %d out of %d\n", store, bucket_size);
        }

        printf("Current bucket status = %d out of %d\n", store, bucket_size);

        store = store - outgoing;
        if (store < 0)
            store = 0;

        printf("Bucket status after outgoing = %d out of %d\n", store, bucket_size);

        n--;
    }

    return 0;
}
