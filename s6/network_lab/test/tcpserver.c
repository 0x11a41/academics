#include <stdio.h>
#include <sys/socket.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "netwc.c"

int main()
{
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  assert(fd != -1);

  int opt = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(PORT);
  socklen_t socklen = sizeof(addr);

  assert(bind(fd, (struct sockaddr*)&addr, socklen) != -1);
  assert(listen(fd, 5) != -1);

  printf("WAITING FOR CLIENT...\n");
  int client_fd = accept(fd, (struct sockaddr*)&addr, &socklen);
  assert(client_fd != -1);
  printf("CLIENT CONNECTED\n");

  char buf[BUF_SIZ];
  while (1)
  {
    memset(buf, 0, sizeof(char) * BUF_SIZ);
    int bytes = recv(client_fd, buf, sizeof(char) * BUF_SIZ, 0);
    if (bytes == 0) {
      printf("CLIENT DISCONNECTED\n");
      break;
    }
    printf("[client]: %s\n", buf);
    printf("response: ");
    assert(fgets(buf, sizeof(char) * BUF_SIZ, stdin) != NULL);
    buf[nlpos(buf)] = '\0';
    send(client_fd, buf, sizeof(char) * BUF_SIZ, 0);
  }

  shutdown(fd, SHUT_RDWR);
  close(fd);
  return 0;
}
