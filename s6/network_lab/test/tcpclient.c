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

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  assert(inet_pton(AF_INET, ADDR, &addr.sin_addr) != -1);
  socklen_t socklen = sizeof(addr);

  assert(connect(fd, (struct sockaddr*)&addr, socklen) != -1);
  printf("connected to %s:%d\n", ADDR, PORT);

  char buf[BUF_SIZ];
  while (1)
  {
    printf("msg: ");
    assert(fgets(buf, BUF_SIZ, stdin) != NULL);
    buf[nlpos(buf)] = '\0';
    send(fd, buf, BUF_SIZ, 0);

    memset(buf, 0, BUF_SIZ);
    int bytes = recv(fd, buf, BUF_SIZ, 0);
    if (bytes == 0) {
      printf("SERVER DISCONNECTED\n");
      break;
    }
    printf("[server]: %s\n", buf);
  }

  shutdown(fd, SHUT_RDWR);
  close(fd);
  return 0;
}
