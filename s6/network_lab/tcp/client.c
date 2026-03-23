// TCP CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER];

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        exit(1);
    }

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to server\n");

    while (1) {
        printf("Client: ");
        fgets(buffer, MAX_BUFFER, stdin);
        send(client_socket, buffer, strlen(buffer), 0);

        memset(buffer, 0, MAX_BUFFER);

        if (recv(client_socket, buffer, sizeof(buffer), 0) <= 0) {
            printf("Server disconnected or error receiving message\n");
            break;
        }

        printf("Server: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}

/*
OUTPUT
./client
Connected to server
Client: hello 0x11a4a
Server: it is 0x11a41 idiot!
*/
