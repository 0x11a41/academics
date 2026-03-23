#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  FILE* obj_code = fopen("objcode", "r");
  char buf[12] = {0};
  int loader_addr, relocation_fac, assembler_start_addr, reloc_bit;

  printf("Enter starting address at load time: ");
  scanf("%x", &loader_addr);

  fscanf(obj_code, "%s %s", buf, buf);
  printf("PROGRAM NAME: %s\n", buf);
  fscanf(obj_code, "%x", &assembler_start_addr); // starting address in header record
  fscanf(obj_code, "%s", buf);
  printf("PROGRAM LENGTH: %s\n", buf);

  relocation_fac = loader_addr - assembler_start_addr;

  fscanf(obj_code, "%s", buf);
  while (strcmp(buf, "E") != 0) {
    if (strcmp(buf, "T")  == 0) {
      fscanf(obj_code, "%s %s %X %s", buf, buf, &reloc_bit, buf);
    }
    if (reloc_bit & 0x800) {
      unsigned int objcode = strtol(buf, NULL, 16) + relocation_fac;
      printf("%X:\t%X\n", loader_addr, objcode);
    } else {
      printf("%X:\t%s\n", loader_addr, buf);
    }
    reloc_bit = reloc_bit << 1;
    loader_addr += strlen(buf) / 2;
    fscanf(obj_code, "%s", buf);
  }
  fclose(obj_code);
  return 0;
}

/*
input:
H COPY 000000 00107A
T 000000 1E FFC 140033 481039 100036 280030 300015 481061 3C0003 20002A 1C0039 30002D
T 002500 15 E00 1D0036 481061 180033 4C1000 801000 601003
E 000000

output:
Enter starting address at load time: 5000
PROGRAM NAME: COPY
PROGRAM LENGTH: 00107A
5000:	145033
5003:	486039
5006:	105036
5009:	285030
500C:	305015
500F:	486061
5012:	3C5003
5015:	20502A
5018:	1C5039
501B:	30502D
501E:	1D5036
5021:	486061
5024:	185033
5027:	4C1000
502A:	801000
502D:	601003
*/
