/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/15/17
 Edited:  1/25/17
*/

#ifndef TREES_STRUCT_DEFS
#define TREES_STRUCT_DEFS

/**********************************************************************

    E N U M E R A T I O N S

***********************************************************************/
typedef enum { PRINT_REG, PRINT_ADDRS, INTACT_CHECK } traversal_t;

/**********************************************************************

    F U N C T I O N   P R O T O T Y P E S

***********************************************************************/
cell_t *build_tr(int cells, int cycles);
void traverse_tr(void *tr, traversal_t walk);

#endif
