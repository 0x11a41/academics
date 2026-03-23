// TCP SERVER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER];

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(1);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len)) == -1) {
        perror("Client acceptance failed");
        exit(1);
    }

    printf("Client connected\n");

    while (1) {
        memset(buffer, 0, MAX_BUFFER);

        if (recv(client_socket, buffer, sizeof(buffer), 0) <= 0) {
            printf("Client disconnected or error receiving message\n");
            break;
        }

        printf("Client: %s\n", buffer);

        printf("Server: ");
        fgets(buffer, MAX_BUFFER, stdin);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    close(server_socket);

    return 0;
}

/*
OUTPUT
./server
Server is listening on port 8080...
Client connected
Client: hello 0x11a4a

Server: it is 0x11a41 idiot!
*/
