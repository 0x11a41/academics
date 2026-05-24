#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>

#define PORT 2121
#define BUFFER_SIZE 4096

int main() {
    char buffer[BUFFER_SIZE];
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(server_fd != -1);

    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    assert(bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == 0);
    assert(listen(server_fd, 3) == 0);

    printf("FTP Server started on port %d...\n", PORT);
    int client_sock = accept(server_fd, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
    assert(client_sock != -1);
    printf("Client connected.\n");

    char cmd[20] = {0};
    int bytes = recv(client_sock, cmd, sizeof(cmd) - 1, 0);
    assert(bytes > 0);
    cmd[bytes] = '\0';

    if (strncmp(cmd, "UPLOAD", 6) == 0) {
        char filename[100] = {0};
        recv(client_sock, filename, sizeof(filename) - 1, 0);

        FILE *fp = fopen(filename, "wb");
        assert(fp != NULL);

        while ((bytes = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0) {
            fwrite(buffer, 1, bytes, fp);
        }

        fclose(fp);
        printf("File uploaded: %s\n", filename);
    } else if (strncmp(cmd, "DOWNLOAD", 8) == 0) {
        char filename[100] = {0};
        recv(client_sock, filename, sizeof(filename) - 1, 0);

        FILE *fp = fopen(filename, "rb");
        if (!fp) {
            printf("File not found.\n");
        } else {
            while ((bytes = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
                send(client_sock, buffer, bytes, 0);
            }
            fclose(fp);
            printf("File sent: %s\n", filename);
        }
    }

    close(client_sock);
    close(server_fd);

    return 0;
}
