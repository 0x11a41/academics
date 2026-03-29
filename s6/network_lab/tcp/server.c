#include <stdio.h>
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUF_SIZ 1024

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock != -1);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    assert(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != -1);
    assert(listen(sock, 5) != -1);

    printf("server is waiting for client\n");

    socklen_t len;
    int client_fd = accept(sock, (struct sockaddr *)&addr, &len);
    assert(client_fd != -1);
    printf("client is connected\n");

    char buf[BUF_SIZ];
    while(1) {
        memset(buf, '\0', BUF_SIZ);
        int size = recv(client_fd, buf, BUF_SIZ, 0);
        assert(size != -1);
        printf("Client: %s\n", buf);
        printf("%s", buf);
        printf("Enter a msg: ");
        assert(fgets(buf, BUF_SIZ, stdin) != NULL);
        assert(send(client_fd, buf, strlen(buf), 0) != -1);
    }

    close(sock);
    return 0;
}
