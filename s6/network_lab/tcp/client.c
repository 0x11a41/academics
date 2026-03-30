#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>

#define PORT 8080
#define BUF_SIZ 1024
#define ADDR "127.0.0.1"

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(fd != -1);

    struct sockaddr_in addr;
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;
    assert(inet_pton(AF_INET, ADDR, &addr.sin_addr.s_addr) == 1);

    assert(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == 0);
    printf("connected to server\n\n");

    char buf[BUF_SIZ];
    while (1) {
        memset(buf, 0, BUF_SIZ);
        printf("Enter msg: ");
        assert(fgets(buf, BUF_SIZ, stdin) != NULL);
        assert(send(fd, buf, strlen(buf), 0) != -1);
        int len = recv(fd, buf, BUF_SIZ, 0);
        assert(len > 0);
        printf("response: %s", buf);
    }
    close(fd);
    return 0;
}
