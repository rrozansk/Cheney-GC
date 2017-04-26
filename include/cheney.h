/******************************************************************************
 * FILE:    cheney.h                                                          *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 1/14/17                                                           *
 * EDITED:  4/25/17                                                           *
 * INFO:    A library to create a garbage collected heap of cons cells.       *
 *          Exposes APIs to create, mutate, and query cons cells as well as   *
 *          setup and manage the heap.                                        *
 *                                                                            *
 *                                                                            *
 ******************************************************************************/

#ifndef CHENEY_GC_STRUCT_DEFS
#define CHENEY_GC_STRUCT_DEFS

/******************************************************************************
 *                                                                            *
 *   C O N S   C E L L                                                        *
 *                                                                            *
 ******************************************************************************/
typedef struct cell { void *car, *cdr; } cell_t;

/******************************************************************************
 *                                                                            *
 *   H E A P   R O O T                                                        *
 *                                                                            *
 ******************************************************************************/
extern void *root;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N   P R O T O T Y P E S                                    *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 * PURPOSE: To test if a give pointer represents atomic data.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * p        the pointer to test                                               *
 *                                                                            *
 * RETURNS: The result of the test. 1 if atomic, 0 otherwise.                 *
 *                                                                            *
 ******************************************************************************/
int isAtomic(void **p);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To test if a give pointer represents a cons cell.                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * p        the pointer to test                                               *
 *                                                                            *
 * RETURNS: The result of the test. 1 if pointer, 0 otherwise.                *
 *                                                                            *
 ******************************************************************************/
int isPtr(void **p);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To construct a new cons cell with the given contents.             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * car      the contents to store in the car field of the cell                *
 * cdr      the contents to store in the cdr field of the cell                *
 *                                                                            *
 * RETURNS: The newly allocated cons cell with the given contents set.        *
 *                                                                            *
 ******************************************************************************/
cell_t *cons(void *car, void *cdr);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To get the car of a cons cell.                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cell     the cons cell in question                                         *
 *                                                                            *
 * RETURNS: The contents in the car field of the cell.                        *
 *                                                                            *
 ******************************************************************************/
void *car(cell_t *cell);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To get the cdr of a cons cell.                                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cell     the cons cell in question                                         *
 *                                                                            *
 * RETURNS: The contents in the cdr field of the cell.                        *
 *                                                                            *
 ******************************************************************************/
void *cdr(cell_t *cell);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To mutate the car of a cons cell.                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cell     the cell to mutate                                                *
 * v        the new value of the cells car                                    *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void set_car(cell_t *cell, void *v);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To mutate the cdr of a cons cell.                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cell     the cell to mutate                                                *
 * v        the new value of the cells cdr                                    *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void set_cdr(cell_t *cell, void *v);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To instantiate a new heap.                                        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cells    the size of the heap in cells                                     *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void hinit(unsigned long cells);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To heap allocate a new cons cell.                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * N/A      N/A                                                               *
 *                                                                            *
 * RETURNS: The newly allocated cons cell from the heap.                      *
 *                                                                            *
 ******************************************************************************/
cell_t *halloc();

/******************************************************************************
 *                                                                            *
 * PURPOSE: To initiate a garbage collection on the heap.                     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * N/A      N/A                                                               *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void collect();

#endif
