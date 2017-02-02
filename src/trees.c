/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/15/17
 Edited:  2/1/17
*/

/**********************************************************************

      I N C L U D E S

***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cheney.h>
#include <trees.h>
#include <bits.h>
#include <math.h>

/**********************************************************************

      F U N C T I O N S

***********************************************************************/
void *genLeaf(int *count, int cycles, cell_t *ancestor) {
  if(cycles && rand() % 2) { return ancestor;  }
  void *i = malloc(sizeof(int));
  *(int *)i = (*count)++;
  setBit((void **)&i, 0);
  return i;
}
 
void build_tr(void **r, int cells, int cycles) {
  cell_t *ancestor, *root; 
  *r = ancestor = root = cons(NULL, NULL);
  cells--;

  int size_stk[(int)floor((log(cells + 1) - 1) / log(2))];
  cell_t *tr_stk[(int)floor((log(cells + 1) - 1) / log(2))];
  int stk_ptr, leaf_c;

  for(leaf_c = 0, stk_ptr = 0;;) {
    if(!cells) { 
      set_car(root, genLeaf(&leaf_c, cycles, ancestor));
      set_cdr(root, genLeaf(&leaf_c, cycles, ancestor));
      if(!stk_ptr) { return; }
      cells = size_stk[stk_ptr];
      root = tr_stk[stk_ptr--];
    } else if(cells == 1) {
      set_car(root, cons(NULL, NULL));
      cells--;
      set_cdr(root, genLeaf(&leaf_c, cycles, ancestor));
      root = car(root);
    } else {
      set_car(root, cons(NULL, NULL));
      set_cdr(root, cons(NULL, NULL));
      cells -= 2;
      size_stk[++stk_ptr] = cells - (cells / 2);
      cells = cells / 2;
      tr_stk[stk_ptr] = cdr(root);
      root = car(root);
    }
  }
}

traversal_t TREE_WALK;
void print_tr_help(void *tr) {
  if(tr == NULL) { printf("()"); }
  else if(!isPtr(&tr) && !isAtomic(&tr)) { printf("ERR: %p\n", tr); }
  else {
    switch(TREE_WALK) {
      case REG:
        if(isAtomic(&tr)) { 
          clrBit((void **)&tr, 0);
          printf("%d", *(int *)tr);
          //free(tr);
        } else {
          printf("(");
          print_tr_help(((cell_t *)tr)->car);
          printf(" . ");
          print_tr_help(((cell_t *)tr)->cdr);
          printf(")");
        }
        break;
      case ADDRS:
        if(isAtomic(&tr)) { 
          clrBit((void **)&tr, 0);
          printf("\t\tleaf %d: %p\n", *(int *)tr, tr);
          //free(tr);
          break;
        }
        printf("cell: %p\n", tr); // fallthrough
      case INTACT_CHECK:
        if(isPtr(&tr)) {
          print_tr_help(((cell_t *)tr)->car);
          print_tr_help(((cell_t *)tr)->cdr);
        }
        break;
    }
  } 
}

// call exit(EXIT_FAILURE); if intact check fails?? ...can i even!?
// combine these funcs?
void traverse_tr(void *tr, traversal_t walk_t) {
  if(walk_t != REG && walk_t != ADDRS && walk_t != INTACT_CHECK) {
    fprintf(stderr, "ERROR: unknown traversal type\nexiting...\n");
    exit(EXIT_FAILURE);
  }
  TREE_WALK = walk_t;
  print_tr_help((void *)tr);
  printf("\n");
}
