/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/21/17
 Edited:  1/21/17
*/

#ifndef BIT_DIDDLING_DEFS
#define BIT_DIDDLING_DEFS

/**********************************************************************

      F U N C T I O N   P R O T O T Y P E S

***********************************************************************/
void setBit(void **ptr, int bit);
void clrBit(void **ptr, int bit);
void flpBit(void **ptr, int bit);
int  getBit(void **ptr, int bit);
void printBin(unsigned int n);

#endif
