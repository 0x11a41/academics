#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/socket.h>

#define PORT 8080
#define BUF_SIZ 1024

int main() {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(fd != -1);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    assert(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) != -1);
    printf("A client connected.\n\n");

    char buf[BUF_SIZ];
    socklen_t addrlen = sizeof(addr);
    while (1) {
        memset(buf, 0, BUF_SIZ);
        int len = recvfrom(fd, buf, BUF_SIZ, 0, (struct sockaddr*)&addr, &addrlen);
        assert(len > 0);
        printf("client: %s\nreply: ", buf);
        assert(fgets(buf, BUF_SIZ, stdin) != NULL);
        assert(sendto(fd, buf, strlen(buf), 0, (struct sockaddr*)&addr, addrlen) != -1);
    }
    close(fd);
}
