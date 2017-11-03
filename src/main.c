/******************************************************************************
 * FILE:    main.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 10/31/17                                                          *
 * EDITED:  11/3/17                                                           *
 * INFO:    An interactive visualization tool for cheney garbage collection.  *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <cheney.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/******************************************************************************
 *                                                                            *
 *   G L O B A L S                                                            *
 *                                                                            *
 ******************************************************************************/
void *root; // define root for the garbage collector

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N S                                                        *
 *                                                                            *
 ******************************************************************************/

// To set a specific bit in an arbitrary pointer.
void setBit(void **ptr, int bit) { *(int *)ptr |= 1 << bit; }

// To clear a specific bit in an arbitrary pointer.
void clrBit(void **ptr, int bit) { *(int *)ptr &= ~(1 << bit); }

// To flip a specific bit in an arbitrary pointer.
void flpBit(void **ptr, int bit) { *(int *)ptr ^= 1 << bit; }

// To determine if a specific bit is set in an arbitrary pointer.
int  getBit(void **ptr, int bit) { return (*(int *)ptr & 1 << bit) ? 1 : 0; }

// To display an integer in its binary representation.
void printBin(unsigned int n) {
  int i;
  for(i = (sizeof(int) * 8) - 1; i >= 0; i--) {
    (n & 1 << i) ? putchar('1') : putchar('0'); 
  }
  printf("\n");
}

// randomly build an arbitrary binary tree using cons cells.
// root    ->  the address of the location at which to store the resulting tree
// cells   ->  how many cons cells to be used in building this tree
// cycles  ->  if we should include cycles or not when building the tree (1/0)
void build_tr(void **r, int cells, int cycles) {
  int size_stk[(int)ceil(log(cells + 1) / log(2))+1];
  void **tr_stk[(int)ceil(log(cells + 1) / log(2))+1];
  cell_t *ancestor = NULL;
  int stk_ptr, leaf, *i;

  for(leaf = stk_ptr = 0; r != tr_stk[0];) {
    if(!cells) { 
      if(cycles && rand() % 2 && ancestor) {
        *r = ancestor;
      } else {
        *(i = malloc(sizeof(int))) = leaf++;
        setBit((void **)&i, 0);
        *r = i;
      }
      cells = size_stk[stk_ptr];
      r = tr_stk[stk_ptr--];
    } else {
      *r = cons(NULL, NULL);
      cells--;
      if(rand() % 2 || !ancestor) { ancestor = *r; }
      size_stk[++stk_ptr] = cells / 2;
      cells -= cells / 2;
      tr_stk[stk_ptr] = &(((cell_t *)(*r))->cdr);
      r = &(((cell_t *)(*r))->car);
    }
  }
}

typedef struct hash_t {
  long size;
  cell_t **tbl;
} hash_t;

hash_t *hash(unsigned long size) {
  hash_t *hash = malloc(sizeof(hash_t));
  hash->size = size;
  hash->tbl = calloc(size, sizeof(cell_t *));
  return hash;
}

void hash_insert(hash_t *h, cell_t *cell, int cell_pos) {
  int loc = (*(unsigned int *)cell * 53) % h->size;
  cell_t *bucket = *(h->tbl + loc);
  for(; bucket; bucket = cdr(bucket)) {
    if(car(car(bucket)) == cell) { return; } // already exists
  }
  cell_t *elem = malloc(sizeof(cell_t));
  set_car(elem, cell);
  int *i = malloc(sizeof(int));
  *i = cell_pos;
  set_cdr(elem, i);
  cell_t *link = malloc(sizeof(cell_t));
  set_car(link, elem);
  set_cdr(link, *(h->tbl + loc));
  *(h->tbl + loc) = link;
}

int hash_ref(hash_t *h, cell_t *cell) {
  int loc = (*(unsigned int *)cell * 53) % h->size;
  cell_t *bucket = *(h->tbl + loc);
  for(; bucket && car(car(bucket)) != cell; bucket = cdr(bucket));
  if(!bucket) { return 0; } // not found
  return *(int *)cdr(car(bucket));
}

void hash_free(hash_t *h) {
  cell_t *buckets, *bucket, *link;
  for(h->size -= 1, buckets = *(h->tbl + h->size); h->size >= 0; h->size -= 1) {
    for(; buckets;) {
      bucket = car(buckets);
      link = buckets;
      buckets = cdr(buckets);
      free(link);
      free(cdr(bucket));
      free(bucket);
    }
  }
  free(h->tbl);
  free(h);
}

// ensure the tree, possibly cyclical, is intact by walking it all
// (following all the pointers).
// tr     ->   the tree to traverse
// cells  ->   the number of cells used to construct the tree
void traverse_tr_intact(void *tr, int cells) { 
  hash_t *seen = hash(1000);
  void *stk[(int)ceil(log(cells + 1) / log(2)) + 1];

  for(cells = 0; tr != stk[0];) { // cells as stk_ptr
    if(isAtomic(&tr) || hash_ref(seen, tr)) {
      tr = stk[cells--];
    } else if(isPtr(&tr)) {
      hash_insert(seen, tr, 1);
      stk[++cells] = cdr(tr);
      tr = car(tr);
    } else {
      fprintf(stderr, "error: unrecognized type in generated tree\n");
      exit(EXIT_FAILURE);
    }
  }
  hash_free(seen);
}

//print a graphical representation of a binary tree's memory footprint.
//tr      ->  the tree to traverse
//cells   ->  the number of cells used to construct the tree
void traverse_tr_addrs(void *tr, int cells) { 
  int loc, stk_ptr;
  hash_t *seen = hash(1000);
  void *stk[(int)ceil(log(cells + 1) / log(2)) + 1];

  for(cells = 1, stk_ptr = loc = 0; tr != stk[0];) {
    if(isAtomic(&tr) || (loc = hash_ref(seen, tr))) {
      if(!loc) { clrBit(&tr, 0); }
      loc ? printf("\t\tleaf #cycle %d#: %p\n", loc, tr) : printf("\t\tleaf %d: %p\n", *(int *)tr, tr);
      tr = stk[stk_ptr--];
    } else if(isPtr(&tr)) {
      printf("cell: %p\n", tr);
      hash_insert(seen, tr, cells++);
      stk[++stk_ptr] = cdr(tr);
      tr = car(tr);
    } else {
      fprintf(stderr, "error: unrecognized type in generated tree\n");
      exit(EXIT_FAILURE);
    }
  }
  printf("\n");
  hash_free(seen);
}

//print a graphical representation of a binary tree, possibly cyclic in nature.
//tr      ->  the tree to traverse
//cells   ->  the number of cells used to construct the tree
void traverse_tr(void *tr, int cells) {
  int loc, stk_ptr;
  hash_t *seen = hash(1000);
  cells = (int)ceil(log(cells + 1) / log(2)) + 1;
  void *stk[cells];
  int parens[cells];
  for(cells--; cells >= 0; cells--) { parens[cells] = 0; }

  for(cells = 1, stk_ptr = loc = 0; tr != stk[0];) {
    if(isAtomic(&tr) || (loc = hash_ref(seen, tr))) {
      if(!loc) { clrBit(&tr, 0); }
      loc ? printf("#cycle: %d#", loc) : printf("%d", *(int *)tr); 
      for(; parens[stk_ptr]; parens[stk_ptr]--) { printf(")"); }
      if(stk_ptr) { printf(" . "); }
      tr = stk[stk_ptr--];
    } else if(isPtr(&tr)) {
      printf("(");
      hash_insert(seen, tr, cells++);
      parens[stk_ptr]++;
      stk[++stk_ptr] = cdr(tr);
      tr = car(tr);
    } else {
    fprintf(stderr, "error: unrecognized type in generated tree\n");
      exit(EXIT_FAILURE);
    }
  }
  for(; parens[0]; parens[0]--) { printf(")"); }
  printf("\n");
  hash_free(seen);
}

int main(int argc, char *argv[]) {
  fprintf(stdout, "Interactive Cheney Garbage Collector\nv1.0\nRyan Rozanski\n\n");

  srand(time(NULL)); // seed random

  int HEAP_CELLS = 10;
  int TREE_SIZE = 5;
  int CYCLES = 0;
  int PRINT_TREE = 1;
  int PRINT_ADDRS = 0;

  printf("\t\t*****COMMAND LINE ARGS*****\n\n");
  printf("HEAP_CELLS  [nat]: heap size in cons cells (default: 10)\n");
  printf("TREE_SIZE   [nat]: size of tree            (default: 5)\n");
  printf("CYCLES      [1/0]: include cycles          (default: 0)\n");
  printf("PRINT_TREES [1/0]: print generated trs     (default: 1)\n");
  printf("PRINT_ADDRS [1/0]: print tr addrs          (default: 0)\n\n");

  if(argc == 6) {
    HEAP_CELLS = atoi(argv[1]);
    TREE_SIZE = atoi(argv[2]);
    CYCLES = atoi(argv[3]);
    PRINT_TREE = atoi(argv[4]);
    PRINT_ADDRS = atoi(argv[5]);
  }

  if(HEAP_CELLS % 2) { HEAP_CELLS++; }
  if(HEAP_CELLS < 2) {
    printf("HEAP_CELLS must be > 1\n");
    return 0;
  } 

  if(TREE_SIZE < 1) {
    printf("TREE_SIZE must be > 0\n");
    return 0;
  }

  if(CYCLES != 0 && CYCLES != 1) {
    printf("CYCLES must be 0: NO or 1: YES\n");
    return 0;
  }

  if(PRINT_TREE != 0 && PRINT_TREE != 1) {
    printf("PRINT_TREES must be 0: NO or 1: YES\n");
    return 0;
  }

  if(PRINT_ADDRS != 0 && PRINT_ADDRS != 1) {
    printf("PRINT_ADDRS must be 0: NO or 1: YES\n");
    return 0;
  }

  printf("\t\t***** TESTING CHENEY GC *****\n\n");
  printf("\t\t***** Initializing heap *****\n\n");
  printf("cell size:  %ld\n", sizeof(cell_t));
  printf("heap cells: %d\n", HEAP_CELLS);
  printf("MB eqv:     %lf\n\n", (sizeof(cell_t) * HEAP_CELLS) / 1000000.0);
  hinit(HEAP_CELLS);

  printf("\t\t***** Constructing root tree *****\n\n");
 
  srand(time(NULL));
  build_tr(&root, TREE_SIZE, CYCLES);

  if(PRINT_TREE) {
    printf("tree:\n");
    traverse_tr(root, TREE_SIZE);
  }
  
  if(PRINT_ADDRS) {
    printf("\ntree addrs:\n");
  traverse_tr_addrs(root, TREE_SIZE);
  }

  if(!PRINT_TREE && !PRINT_ADDRS) { traverse_tr_intact(root, TREE_SIZE); }

  printf("\n\t\t***** Start collecting *****\n\n");
  clock_t start, end;
  start = clock();
  collect();
  end = clock();

  printf("Collection time: %fs\n\n", (double)(end - start) / CLOCKS_PER_SEC);

  printf("\t\t***** Checking root tree *****\n\n");

  if(PRINT_TREE) {
    printf("tree:\n");
    traverse_tr(root, TREE_SIZE);
  }

  if(PRINT_ADDRS) {
    printf("\ntree addrs:\n");
    traverse_tr_addrs(root, TREE_SIZE);
  }

  if(!PRINT_TREE && !PRINT_ADDRS) { traverse_tr_intact(root, TREE_SIZE); }

  exit(EXIT_SUCCESS);
}
