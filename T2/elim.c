#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

void eliminar(char *str, char *pat) {
  int lenp = strlen(pat);
  char *aux;
  char *aux2;
  int i = 0;
  aux = str;
  aux2 = str;

  while(*aux){
    *str = *aux;
    if (*aux != *pat){
      aux++;
      str++;
    }
    else{
      aux2 = aux;
      while (*aux2 == *pat && *pat && *aux2){
        i++;
        aux2++;
        pat++;
      }
      if (i == lenp) {
        aux = aux2;
      }
      else {
        str++;
        aux++;
      }
      pat -= i;
      i = 0;
    }
  }
  *str = '\0';
}

char *eliminados(char *str, char *pat) {
  char *str2 = malloc(strlen(str) + 1);
  strcpy(str2, str);
  eliminar(str2, pat);
  char *res = malloc(strlen(str2) + 1);
  strcpy(res, str2);
  free(str2);
  return res;
}
