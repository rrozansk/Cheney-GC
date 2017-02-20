/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/15/17
 Edited:  2/19/17
*/

#ifndef TREES_STRUCT_DEFS
#define TREES_STRUCT_DEFS

/**********************************************************************

    F U N C T I O N   P R O T O T Y P E S

***********************************************************************/
void build_tr(void **root, int cells, int cycles);
void traverse_tr(void *tr, int cells);
void traverse_tr_addrs(void *tr, int cells);
void traverse_tr_intact(void *tr, int cells);

#endif
