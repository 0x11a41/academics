#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_tab(FILE* fp, char* entity) {
  rewind(fp);
  char key[32], val[32];
  while (fscanf(fp, "%s %s", key, val) != EOF) {
    if (strcmp(key, entity) == 0) {
      return 1; // entity found
    }
  }
  return 0; // not found
}

int main() {
  FILE* input = fopen("input", "r");
  FILE* optab = fopen("optab", "r");
  FILE* symtab = fopen("symtab", "w+");
  FILE* intmt = fopen("intermediate", "w");
  FILE* length = fopen("length", "w");

  char label[32], opcode[32], operand[32];
  int locctr = 0, start_addr = 0;
  fscanf(input, "%s %s %s", label, opcode, operand);
  if (strcmp(opcode, "START") == 0) {
    locctr = start_addr = strtol(operand, NULL, 16);
    fprintf(intmt, "**\t%s\t%s\t%s\n", label, opcode, operand);
  }

  fscanf(input, "%s %s %s", label, opcode, operand);

  while (strcmp(opcode, "END") != 0) {
    if (strcmp(label, "**") != 0) {
      if (search_tab(symtab, label)) {
        printf("duplicate label found: %s\n", label);
        exit(-1);
      } else {
        fprintf(symtab, "%s\t%04X\n", label, locctr);
      }
    }
    fprintf(intmt, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    if (search_tab(optab, opcode)) {
      locctr += 3;
    } else if (strcmp(opcode, "WORD") == 0) {
      locctr += 3;
    } else if (strcmp(opcode, "BYTE") == 0) {
      int len = strlen(operand) - 3;
      if (*operand == 'X') len /= 2;
      locctr += len;
    } else if (strcmp(opcode, "RESW") == 0) {
      locctr += 3 * atoi(operand);
    } else if (strcmp(opcode, "RESB") == 0) {
      locctr += atoi(operand);
    } else {
      printf("invalid opcode found: %s\n", opcode);
      exit(-1);
    }
    fscanf(input, "%s %s %s", label, opcode, operand);
  }

  fprintf(intmt, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
  fprintf(length, "%04X", locctr - start_addr);

  fclose(length);
  fclose(intmt);
  fclose(symtab);
  fclose(optab);
  fclose(input);
  return 0;
}
