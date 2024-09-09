#include <stdio.h>

#include "suma.h"

Bcd sumaBcd(Bcd x, Bcd y) {

  Bcd carry = 0;
  Bcd res = 0;

  for(int i = 0; i < 16; i++) {
    
    Bcd suma = ((x >> (i<<2)) & 0xF) + ((y >> (i<<2)) & 0xF) + carry;
    carry = 0;
    
    if(suma > 9) {

      if(i == 15) {
        res = 0xFFFFFFFFFFFFFFFF;
        break;
      }

      suma = suma - 10;
      carry = 1;
    }
    
    res = res | (suma << (i<<2));
  }


  return res;
}