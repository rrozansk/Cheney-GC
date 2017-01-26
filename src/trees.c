/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/15/17
 Edited:  1/25/17
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
int LEAF_COUNT;
int CYCLES;

cell_t *ANCESTOR;

traversal_t TREE_WALK;

/**********************************************************************

      F U N C T I O N S

***********************************************************************/
void *encodeInt() {
  void *i = malloc(sizeof(int));
  *(int *)i = LEAF_COUNT++;
  setBit((void **)&i, 0);
  return i;
}

// generate a tr using cells from the heap. 
// CYCLES = 0 :: tr is perfectly balanced and has #leafs = #cells+1
// CYCLES = 1 :: tr randomly holds an ancestral ref and randomly assigns it
void build_tr_help(cell_t *cell, int cells_left) {                                                 // *** NOTE:: still need to do cycle creation in tr generation
  cell_t *last_cell;
  switch(cells_left) {
  case 0:  // no cells left to allocate, so populate the leafs
    set_car(cell, encodeInt());
    set_cdr(cell, encodeInt());
    break;
  case 1: // random build left or right and populate leaf
    last_cell = cons(NULL, NULL);
    build_tr_help(last_cell, 0);
    (rand() % 2) ? set_car(cell, last_cell) : set_cdr(cell, last_cell);

    (car(cell) == last_cell) ? set_cdr(cell, encodeInt()) : set_car(cell, encodeInt());
    break;
  default:
    set_car(cell, cons(NULL, NULL));
    set_cdr(cell, cons(NULL, NULL));
    cells_left -= 2;
    int left = cells_left / 2;
    int right = cells_left - left;

    build_tr_help((cell_t *)car(cell), left);
    build_tr_help((cell_t *)cdr(cell), right);
    break;
  }
}

cell_t *build_tr(int cells, int cycles) {
  srand(time(NULL));                      // seed random for tr builder
  cell_t *root = cons(NULL, NULL);        // halloc the root
  CYCLES = cycles;                        // generate cycles or not
  ANCESTOR = root;                        // set ancestor for cycles
  LEAF_COUNT = 0;                         // reset leaf counter
  build_tr_help(root, cells-1);           // generate a tr
  return root;                            // return tr
}

void print_tr_help(void *tr) {                                                  // *** NOTE:: still need to do cycle detection to print properly
  if(tr == NULL) { printf("()"); }
  else if(isAtomic(&tr)) {
    clrBit((void **)&tr, 0);
    switch(TREE_WALK) {
    case PRINT_REG:
      printf("%d", *(int *)tr);
      break;
    case PRINT_ADDRS:
      printf("\t\tleaf %d: %p\n", *(int *)tr, tr);
      break;
    case INTACT_CHECK:
      break;
    default:
      fprintf(stderr, "ERROR: unknown traversal type\nexiting...\n");
      exit(EXIT_FAILURE);
      break;
    }
  }
  else if(isPtr(&tr)) {
    switch(TREE_WALK) {
    case PRINT_REG:     
      printf("(");
      print_tr_help(((cell_t *)tr)->car);
      printf(" . ");
      print_tr_help(((cell_t *)tr)->cdr);
      printf(")");
      break;
    case PRINT_ADDRS:
      printf("cell: %p\n", tr); // fallthrough
    case INTACT_CHECK:  
      print_tr_help(((cell_t *)tr)->car);
      print_tr_help(((cell_t *)tr)->cdr);
      break;
    default:
      fprintf(stderr, "ERROR: unknown traversal type\nexiting...\n");
      exit(EXIT_FAILURE);
      break;
    }

  }
  else { printf("ERR: %p\n", tr); }
}

void traverse_tr(void *tr, traversal_t walk_type) {
  TREE_WALK = walk_type;
  print_tr_help((void *)tr);
  printf("\n");
}
