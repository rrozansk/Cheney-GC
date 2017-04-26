/******************************************************************************
 * FILE:    bits.h                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 1/21/17                                                           *
 * EDITED:  4/25/17                                                           *
 * INFO:    A library for bit diddling with pointers.                         *
 *                                                                            *
 ******************************************************************************/

#ifndef BIT_DIDDLING_DEFS
#define BIT_DIDDLING_DEFS

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N   P R O T O T Y P E S                                    *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 * PURPOSE: To set a specific bit in an arbitrary pointer.                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ptr      the pointer to modify                                             *
 * bit      the specific bit to set                                           *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void setBit(void **ptr, int bit);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To clear a specific bit in an arbitrary pointer.                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ptr      the pointer to modify                                             *
 * bit      the specific bit to clear                                         *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void clrBit(void **ptr, int bit);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To flip a specific bit in an arbitrary pointer.                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ptr      the pointer to modify                                             *
 * bit      the specific bit to flip                                          *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void flpBit(void **ptr, int bit);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To determine if a specific bit is set in an arbitrary pointer.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * ptr      the pointer to modify                                             *
 * bit      the specific bit in question                                      *
 *                                                                            *
 * RETURNS: 1 if the specified bit is set, 0 otherwise.                       *
 *                                                                            *
 ******************************************************************************/
int  getBit(void **ptr, int bit);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To display an integer in its binary representation.               *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * n        the integer to display in binary                                  *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void printBin(unsigned int n);

#endif
