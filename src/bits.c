/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/21/17
 Edited:  1/21/17
*/

/**********************************************************************

    I N C L U D E S

***********************************************************************/
#include <stdio.h>

/**********************************************************************

    F U N C T I O N S

***********************************************************************/
void setBit(void **ptr, int bit) { *(int *)ptr |= 1 << bit; }

void clrBit(void **ptr, int bit) { *(int *)ptr &= ~(1 << bit); }

void flpBit(void **ptr, int bit) { *(int *)ptr ^= 1 << bit; }

int  getBit(void **ptr, int bit) { return (*(int *)ptr & 1 << bit) ? 1 : 0; }

void printBin(unsigned int n) {
  int i;
  for(i = (sizeof(int) * 8) - 1; i >= 0; i--) {
    (n & 1 << i) ? putchar('1') : putchar('0'); 
  }
  printf("\n");
}
