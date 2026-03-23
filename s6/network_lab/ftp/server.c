// FTP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2121
#define BUFFER_SIZE 4096

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("FTP Server started on port %d...\n", PORT);

    // Accept connection
    client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (client_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    char command[20] = {0};
    int bytes = recv(client_socket, command, sizeof(command) - 1, 0);
    if (bytes <= 0) {
        printf("Failed to receive command.\n");
        close(client_socket);
        close(server_fd);
        return 1;
    }

    command[bytes] = '\0';

    if (strncmp(command, "UPLOAD", 6) == 0) {
        char filename[100] = {0};
        recv(client_socket, filename, sizeof(filename) - 1, 0);

        FILE *fp = fopen(filename, "wb");
        if (!fp) {
            perror("File open failed");
            close(client_socket);
            close(server_fd);
            return 1;
        }

        while ((bytes = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
            fwrite(buffer, 1, bytes, fp);
        }

        fclose(fp);
        printf("File uploaded: %s\n", filename);
    } 
    else if (strncmp(command, "DOWNLOAD", 8) == 0) {
        char filename[100] = {0};
        recv(client_socket, filename, sizeof(filename) - 1, 0);

        FILE *fp = fopen(filename, "rb");
        if (!fp) {
            printf("File not found.\n");
        } else {
            while ((bytes = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
                send(client_socket, buffer, bytes, 0);
            }
            fclose(fp);
            printf("File sent: %s\n", filename);
        }
    }

    close(client_socket);
    close(server_fd);

    return 0;
}
