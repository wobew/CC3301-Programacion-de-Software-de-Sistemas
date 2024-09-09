#include <string.h>

int count(char *str, char *str2) {

    int i = 0;
    int j = 0;

    while (*str && *str == ' ') str++;

    while (*str) {

         if (*str != ' ' && (*(str + 1) == ' ' || *(str + 1) == '\0')) i++;

        str++;
    }

    while (*str2 && *str2 == ' ') str2++;

    while (*str2) {

         if (*str2 != ' ' && (*(str2 + 1) == ' ' || *(str2 + 1) == '\0')) j++;

        str2++;
    }

    return i-j;
}


void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {

    int t1= count(p[0], p[1]);

    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}