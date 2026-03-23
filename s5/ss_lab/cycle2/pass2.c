#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char opcode[32], label[32], operand[32], operand_cpy[32], addr[32];

void read_intermediate(FILE* fp) {
  fscanf(fp, "%s\t%s\t%s\t%s", addr, label, opcode, operand);
  strcpy(operand_cpy, operand);
}

int search_tab(FILE* fp, char* entity) {
  rewind(fp);
  char key[32]; int val;
  while (fscanf(fp, "%s %X", key, &val) != EOF) {
    if (strcmp(key, entity) == 0) return val;
  }
  return -1;
}

int main() {
  FILE* intmt = fopen("intermediate", "r");
  FILE* symtab = fopen("symtab", "r");
  FILE* optab = fopen("optab", "r");
  FILE* obj_code = fopen("obj_code", "w");
  FILE* listing = fopen("listing", "w");

  read_intermediate(intmt);
  if (strcmp(opcode, "START") == 0) {
    fprintf(listing, "**\t%s\t%s\t%s\t**\n", label, opcode, operand_cpy);
  }
  fprintf(obj_code, "H^%s^00%s^00%s\n", label, operand, addr);
  read_intermediate(intmt);
  fprintf(obj_code, "T^00%s^**", addr);
  int len_pos = ftell(obj_code) - 2, count = 0;

  while (strcmp(opcode, "END") != 0) {
    int mnemonic, sym_addr = 0;
    char obj[30] = {0};
    if ((mnemonic= search_tab(optab, opcode)) != -1) {
      if (strcmp(operand, "**") != 0) {
        int indexed = 0, len = strlen(operand);
        if (operand[len - 1] == 'X' && operand[len - 2] == ',') {
          indexed = 0x8000;
          operand[len - 2] = '\0';
        }
        if ((sym_addr = search_tab(symtab, operand)) != -1) {
          sym_addr = sym_addr | indexed;
        } else {
          printf("undefined symbol found: %s\n", operand_cpy);
        }
      }
      snprintf(obj, 30, "%02X%04X", mnemonic, sym_addr);
    } else if (strcmp(opcode, "BYTE") == 0) {
      int len = strlen(operand);
      operand[len - 1] = '\0';
      if (*operand == 'C') {
        char tmp[30];
        for (int i = 2; i < len - 1; i++) {
          sprintf(tmp, "%02X", operand[i]);
          strcat(obj, tmp);
        }
      } else if (*operand == 'X') {
        sprintf(obj, "%s", operand + 2);
      }
    } else if (strcmp(opcode, "WORD") == 0)  {
      sprintf(obj, "%06X", atoi(operand));      
    }
    if (strcmp(opcode, "RESW") != 0 && strcmp(opcode, "RESB") != 0) {
      if (count > 30 - (strlen(obj) / 2)) {
        fseek(obj_code, len_pos, SEEK_SET);
        fprintf(obj_code, "%02X", count);
        fseek(obj_code, 0, SEEK_END);
        fprintf(obj_code, "\nT^00%s^**", addr);
        len_pos = ftell(obj_code) - 2;
        count = 0;
      }
      count += strlen(obj) / 2;
      fprintf(obj_code, "^%s", obj);
      fprintf(listing, "%s\t%s\t%s\t%s\t%s\n", addr, label, opcode, operand_cpy, obj);
    } else {
      fprintf(listing, "%s\t%s\t%s\t%s\t**\n", addr, label, opcode, operand_cpy);
    }
    read_intermediate(intmt);
  }

  fprintf(obj_code, "\nE^00%s\n", operand);
  fseek(obj_code, len_pos, SEEK_SET);
  fprintf(obj_code, "%02X", count);
  fprintf(listing, "%s\t%s\t%s\t%s\t**\n", addr, label, opcode, operand_cpy);
  
  fclose(intmt);
  fclose(symtab);
  fclose(optab);
  fclose(obj_code);
  fclose(listing);
  return 0;
}
