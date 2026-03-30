#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/socket.h>

#define PORT 8080
#define BUF_SIZ 1024
#define ADDR "127.0.0.1"

int main() {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(fd != -1);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    assert(inet_pton(AF_INET, ADDR, &server_addr.sin_addr) == 1);

    char buf[BUF_SIZ];
    while (1) {
        printf("msg: ");
        assert(fgets(buf, BUF_SIZ, stdin) != NULL);
        sendto(fd, buf, strlen(buf), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        struct sockaddr_in recv_addr;
        socklen_t recv_len = sizeof(recv_addr);
        ssize_t len = recvfrom(fd, buf, BUF_SIZ - 1, 0, (struct sockaddr*)&recv_addr, &recv_len);
        assert(len > 0);
        buf[len] = '\0';
        printf("server: %s", buf);
    }

    close(fd);
    return 0;
}
