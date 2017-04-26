/******************************************************************************
 * FILE:    trees.h                                                           *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 1/15/17                                                           *
 * EDITED:  4/25/17                                                           *
 * INFO:    A library to randomly build arbitrary binary trees using cons     *
 *          cells, along with several different ways of walking over the      *
 *          given generated tree(s). The generator as well as all tree        *
 *          traversals are also capable of handling cycles.                   *
 *                                                                            *
 ******************************************************************************/

#ifndef TREES_STRUCT_DEFS
#define TREES_STRUCT_DEFS

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N   P R O T O T Y P E S                                    *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 * PURPOSE: To randomly build an arbitrary binary tree using cons cells.      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * root     the address of the location at which to store the resulting tree  *
 * cells    how many cons cells to be used in building this tree              *
 * cycles   if we should include cycles or not when building the tree (1/0)   *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void build_tr(void **root, int cells, int cycles);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To print a graphical representation of a binary tree, possibly    *
 *          cyclic in nature.                                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * tr        the tree to traverse                                             *
 * cells     the number of cells used to construct the tree                   *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void traverse_tr(void *tr, int cells);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To print a graphical representation of a binary tree's memory     *
 *          footprint.                                                        *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * tr        the tree to traverse                                             *
 * cells     the number of cells used to construct the tree                   *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void traverse_tr_addrs(void *tr, int cells);

/******************************************************************************
 *                                                                            *
 * PURPOSE: To ensure the tree, possibly cyclical, is intact by walking it    *
 *          all (following all the pointers).                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * tr        the tree to traverse                                             *
 * cells     the number of cells used to construct the tree                   *
 *                                                                            *
 * RETURNS: N/A                                                               *
 *                                                                            *
 ******************************************************************************/
void traverse_tr_intact(void *tr, int cells);

#endif
