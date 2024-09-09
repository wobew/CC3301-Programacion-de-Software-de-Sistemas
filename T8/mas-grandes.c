#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pss.h"
       
typedef struct{
  char *nombre;
  int tamanno;
  } st;


int fun(void *ptr, int i, int j) {
  st **a= ptr;
  if(a[i]->tamanno == a[j]->tamanno) return -strcmp(a[i]->nombre, a[j]->nombre);
  return a[i]->tamanno - a[j]->tamanno;
}

Queue *q;

void aux(char *nom) {
  struct stat st_nom;
  int rc;
  rc= stat(nom, &st_nom);

  if (rc!=0) {
    exit(0);
  }
  if (S_ISREG(st_nom.st_mode)) {

    st *ptr = malloc(sizeof(st));
    ptr->nombre = strdup(nom);
    ptr->tamanno = st_nom.st_size;

    put(q, ptr);

  }

  else if (S_ISDIR(st_nom.st_mode)) {
    DIR *dir = opendir(nom);
    if (dir == NULL) {
      perror(nom);
      exit(1);
    }
    for (struct dirent *entry = readdir(dir);
         entry != NULL;
         entry = readdir(dir)) {
      if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
        continue;
      }
      char *nom_arch= malloc(strlen(nom)+strlen(entry->d_name)+2);
      strcpy(nom_arch, nom);
      strcat(nom_arch, "/");
      strcat(nom_arch, entry->d_name);
      aux(nom_arch);
      free(nom_arch);
    }
    closedir(dir);
  }
  else {
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  if (argc!=3) {
    fprintf(stderr, "uso: %s <arch|dir>\n", argv[0]);
    exit(1);
  }

  int n = atoi(argv[2]);

  q=makeQueue();
  aux(argv[1]);
  int cantidad = queueLength(q);
  st *arr[cantidad];

  for (int i = 0; i < cantidad; i++) arr[i] = get(q);

  destroyQueue(q);
  sortPtrArray(arr, 0, cantidad-1, fun);

  for(int i = cantidad - 1; i > cantidad - n - 1; i--) {
    printf("%s %d\n", arr[i]->nombre, arr[i]->tamanno);
  }

  for(int i = 0; i < cantidad; i++) {
    free(arr[i]->nombre);
    free(arr[i]);
  }

  return 0;
}
