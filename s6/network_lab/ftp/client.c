#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>

#define PORT 2121
#define BUFFER_SIZE 4096
#define ADDR "127.0.0.1"

int main() {
    char buffer[BUFFER_SIZE];
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock != -1);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    assert(inet_pton(AF_INET, ADDR, &serv_addr.sin_addr) > 0);
    assert(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != -1);

    char cmd[20];
    printf("Enter command (UPLOAD/DOWNLOAD): ");
    scanf("%s", cmd);
    send(sock, cmd, strlen(cmd), 0);

    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);

    send(sock, filename, strlen(filename), 0);

    if (strcmp(cmd, "UPLOAD") == 0) {
        FILE *fp = fopen(filename, "rb");
        assert(fp != NULL);

        int bytes;
        while ((bytes = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
            send(sock, buffer, bytes, 0);
        }

        fclose(fp);
        printf("File uploaded successfully.\n");
    } else if (strcmp(cmd, "DOWNLOAD") == 0) {
        FILE *fp = fopen(filename, "wb");
        assert(fp != NULL);

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
