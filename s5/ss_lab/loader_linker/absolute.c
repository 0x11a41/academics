#include <stdio.h>
#include <string.h>

int main() {
  FILE *fp = fopen("obj_code", "r");
  char buf[12];
  int start_addr = 0;

  fscanf(fp, "%s %s", buf, buf);
  printf("PROGRAME NAME: %s\n", buf);
  fscanf(fp, "%x", &start_addr);
  fscanf(fp, "%s", buf);
  printf("PROGRAM LENGTH: %s\n", buf);

  fscanf(fp, "%s", buf);
  while(strcmp(buf, "E") != 0) {
    if (strcmp(buf, "T") == 0) {
      fscanf(fp, "%s %s %s", buf, buf, buf);
    }
    for (int i = 0; buf[i] != '\0'; i += 2) {
      printf("%04X: %c%c\n", start_addr, buf[i], buf[i + 1]);
      start_addr++;
    }
    fscanf(fp, "%s", buf);
  }
  fclose(fp);
  return 0;
}
