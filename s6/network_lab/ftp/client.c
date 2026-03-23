#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2121
#define BUFFER_SIZE 4096

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return 1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    char command[20];
    printf("Enter command (UPLOAD/DOWNLOAD): ");
    scanf("%19s", command);

    // Send command to server
    send(sock, command, strlen(command), 0);

    char filename[100];
    printf("Enter filename: ");
    scanf("%99s", filename);

    // Send filename to server
    send(sock, filename, strlen(filename), 0);

    if (strcmp(command, "UPLOAD") == 0) {
        FILE *fp = fopen(filename, "rb");
        if (!fp) {
            perror("File open failed");
            close(sock);
            return 1;
        }

        int bytes;
        while ((bytes = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
            send(sock, buffer, bytes, 0);
        }

        fclose(fp);
        printf("File uploaded successfully.\n");
    } 
    else if (strcmp(command, "DOWNLOAD") == 0) {
        FILE *fp = fopen(filename, "wb");
        if (!fp) {
            perror("File creation failed");
            close(sock);
            return 1;
        }

        int bytes;
        while ((bytes = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
            fwrite(buffer, 1, bytes, fp);
        }

        fclose(fp);
        printf("File downloaded successfully.\n");
    }

    close(sock);
    return 0;
}
