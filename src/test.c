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
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits.h>
#include <cheney.h>
#include <trees.h>

/**********************************************************************

    G L O B A L

***********************************************************************/
cell_t *root; // define root for the garbage collector

/**********************************************************************

    T E S T I N G   ( M A I N )

***********************************************************************/
int main(int argc, char *argv[]) {

  int HEAP_CELLS = 10;
  int GEN_TREES = 1;
  int CYCLES = 0;
  int PRINT_TREES = 1;
  int PRINT_ADDRS = 0;

  if(argc == 6) {
    HEAP_CELLS = atoi(argv[1]);
    GEN_TREES = atoi(argv[2]);
    CYCLES = atoi(argv[3]);
    PRINT_TREES = atoi(argv[4]);
    PRINT_ADDRS = atoi(argv[5]);
  } else {
    printf("\t\t*****COMMAND LINE ARGS*****\n\n");
    printf("HEAP_CELLS  [nat]: heap size in cons cells (default: 10)\n");
    printf("GEN_TREES   [nat]: trees to generate       (default: 1)\n");
    printf("CYCLES      [1/0]: include cycles          (default: 0)\n");
    printf("PRINT_TREES [1/0]: print generated trs     (default: 1)\n");
    printf("PRINT_ADDRS [1/0]: print tr addrs          (default: 0)\n\n");
  }

  if(HEAP_CELLS % 2) { HEAP_CELLS++; }
  if(HEAP_CELLS < 2) {
    printf("HEAP_CELLS must be > 1\n");
    return 0;
  } 

  if(GEN_TREES < 1) {
    printf("GEN_TREES must be > 1\n");
    return 0;
  }

  if(CYCLES != 0 && CYCLES != 1) {
    printf("CYCLES must be 0: NO or 1: YES\n");
    return 0;
  }

  if(PRINT_TREES != 0 && PRINT_TREES != 1) {
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
/*
  int tree;
  int size[GEN_TREES];
  for(tree = GEN_TREES; tree > 0; tree--) { 
    size[tree-1] = rand() % HEAP_CELLS; 
    HEAP_CELLS -= size[tree];
  }
  size[0] = HEAP_CELLS;

  cell_t *trs[GEN_TREES];
  for(tree = 0; tree < GEN_TREES; tree++) { trs[tree] = build_tr(size[tree], CYCLES); }
 
  root = trs[rand() % GEN_TREES];
  printf("generated tree %d\n", tree);
  PRINT_TREES ? traverse_tr(root, PRINT_REG) : traverse_tr(root, INTACT_CHECK);

  if(GEN_TREES > 1) { printf("root tree choosen: %d\n", tree); }
*/

  root = build_tr(HEAP_CELLS / 2, CYCLES);
  PRINT_TREES ? traverse_tr(root, PRINT_REG) : traverse_tr(root, INTACT_CHECK);

  if(PRINT_ADDRS) {
    printf("\ntree addrs:\n");
    traverse_tr(root, PRINT_ADDRS);
  }

  printf("\n\t\t***** Start collecting *****\n\n");
  clock_t start, end;
  start = clock();
  collect((void **)&root);
  end = clock();

  printf("Collection time: %fs\n\n", (double)(end - start) / CLOCKS_PER_SEC);

  printf("\t\t***** Checking root tree *****\n\n");
  PRINT_TREES ? traverse_tr(root, PRINT_REG) : traverse_tr(root, INTACT_CHECK);

  if(PRINT_ADDRS) {
    printf("\ntree addrs:\n");
    traverse_tr(root, PRINT_ADDRS);
  }

  return 0;
}
