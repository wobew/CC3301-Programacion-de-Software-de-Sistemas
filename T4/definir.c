#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

int main(int argc, char *argv[]) {

  if (argc != 4) {
        fprintf(stderr, "Uso: ./definir <diccionario> <llave> <definicion>\n");
        return 1;
    }

  FILE *f = fopen(argv[1], "r+");
  if (!f) {
        perror(argv[1]);
        return 1;
    }

  char buf[81];
  fseek(f, 0, SEEK_END);
  int n = ftell(f) / 81;
  int m = hash_string(argv[2]) % n;
  fseek(f, m*81, SEEK_SET);
  long inicio = ftell(f);
  
  while(fread(buf, 1, 81, f) > 0) {
    if (buf[0] == ' ') {
        fseek(f, -81, SEEK_CUR);
        fputs(argv[2], f);
        fputc(':', f);
        fputs(argv[3], f);
        break;
    } 
    else if (strncmp(buf, argv[2], strlen(argv[2])) == 0) {
        fprintf(stderr, "La llave %s ya se encuentra en el diccionario\n", argv[2]);
        fclose(f);
        return 1;
    }
    if (ftell(f) == n * 81) {
        fseek(f, 0, SEEK_SET);
    }
    if (ftell(f) == inicio) {
        fprintf(stderr, "dicc-full.txt: el diccionario esta lleno\n");
        fclose(f);
        return 1;
    }
  }

  fclose(f);
  return 0;
}

  