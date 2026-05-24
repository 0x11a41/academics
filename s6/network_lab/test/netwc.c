#define PORT 8080
#define ADDR "127.0.0.1"
#define BUF_SIZ 1024

static inline unsigned int nlpos(char* buf) {
  int i = 0;
  while (i < BUF_SIZ - 1 && buf[i] != '\0' && buf[i] != '\n') ++i;
  return i;
}

