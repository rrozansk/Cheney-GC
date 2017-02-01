/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/15/17
 Edited:  1/31/17
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

/**********************************************************************

      G L O B A L S

***********************************************************************/
int leaf_c;

traversal_t TREE_WALK;

/**********************************************************************

      F U N C T I O N S

***********************************************************************/
void *encodeLeaf() {
  void *i = malloc(sizeof(int));
  *(int *)i = leaf_c++;
  setBit((void **)&i, 0);
  return i;
}
 
// generate a tr using cells from the heap. 
// CYCLES = 0 :: tr is perfectly balanced and has #leafs = #cells+1
// CYCLES = 1 :: tr randomly holds an ancestral ref and randomly assigns it
void build_tr_help(cell_t *root, int cells, int cycles, void *ancestor) {
  if(!cells) { 
    set_car(root, encodeLeaf());
    set_cdr(root, encodeLeaf());
  }
  else if(cells == 1 && rand() % 2) {
      set_car(root, cons(NULL, NULL));
      build_tr_help(car(root), 0, cycles, ancestor);
      set_cdr(root, encodeLeaf());
  }
  else if(cells == 1) {
      set_cdr(root, cons(NULL, NULL));
      build_tr_help(cdr(root), 0, cycles, ancestor);
      set_car(root, encodeLeaf());
  }
  else {
    set_car(root, cons(NULL, NULL));
    set_cdr(root, cons(NULL, NULL));

    cells -= 2;
    int left = cells / 2;
    int right = cells - left;

    build_tr_help(car(root), left, cycles, ancestor);
    build_tr_help(cdr(root), right, cycles, ancestor);
  }
}

void build_tr(void **root, int cells, int cycles) {
  leaf_c = 0;                                // reset leaf counter
  srand(time(NULL));
  *(void **)root = cons(NULL, NULL);
  build_tr_help(*root, --cells, cycles, root); // generate a tr
}

void print_tr_help(void *tr) {
  if(tr == NULL) { printf("()"); }
  else if(!isPtr(&tr) && !isAtomic(&tr)) { printf("ERR: %p\n", tr); }
  else {
    switch(TREE_WALK) {
      case REG:
        if(isAtomic(&tr)) { 
          clrBit((void **)&tr, 0);
          printf("%d", *(int *)tr); 
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

void traverse_tr(void *tr, traversal_t walk_t) {
  if(walk_t != REG && walk_t != ADDRS && walk_t != INTACT_CHECK) {
    fprintf(stderr, "ERROR: unknown traversal type\nexiting...\n");
    exit(EXIT_FAILURE);
  }
  TREE_WALK = walk_t;
  print_tr_help((void *)tr);
  printf("\n");
}
