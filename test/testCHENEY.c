/******************************************************************************
 * FILE:    testCHENEY.c                                                      *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 10/31/17                                                          *
 * EDITED:  10/31/17                                                          *
 * INFO:    ...                                                               *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <cheney.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *                                                                            *
 *   G L O B A L S                                                            *
 *                                                                            *
 ******************************************************************************/
void *root; // define root for the garbage collector

/******************************************************************************
 *                                                                            *
 *   C O N S T A N T S                                                        *
 *                                                                            *
 ******************************************************************************/
#define TOTAL_TESTS 1

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResultCHENEY { CHENEY_PASS, CHENEY_FAIL } testResultCHENEY_t;

/******************************************************************************
 *                                                                            *
 *   T E S T S                                                                *
 *                                                                            *
 ******************************************************************************/   
testResultCHENEY_t test___() {
  // CHENEY_PASS 
  return CHENEY_FAIL;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { test___,                                      "test___"                   },
};

int main() {

  testResultCHENEY_t result;
  int test, passes, fails;
  for(test = passes = fails = 0; test < TOTAL_TESTS; test++) {
    result = ((testResultCHENEY_t (*)(void))(TESTS[test][0]))();
    if(result == CHENEY_PASS) {
      passes++;
      fprintf(stdout, "PASS: %s\n", (char *)TESTS[test][1]);
    } else {
      fprintf(stdout, "FAIL: %s\n", (char *)TESTS[test][1]);
      fails++;
    }
    fflush(stdout); // so if segfault/crash we know last successful test
  }

  fprintf(stdout, "\n--------------------\n"
                    "Passes:           %i\n"
                    "Fails:            %i\n"
                    "Total Tests:      %i\n", passes, fails, passes+fails);

  return 0;  
}

//int main(int argc, char *argv[]) {
//
//  int HEAP_CELLS = 10;
//  int TREE_SIZE = 5;
//  int CYCLES = 0;
//  int PRINT_TREE = 1;
//  int PRINT_ADDRS = 0;
//
//  printf("\t\t*****COMMAND LINE ARGS*****\n\n");
//  printf("HEAP_CELLS  [nat]: heap size in cons cells (default: 10)\n");
//  printf("TREE_SIZE   [nat]: size of tree            (default: 5)\n");
//  printf("CYCLES      [1/0]: include cycles          (default: 0)\n");
//  printf("PRINT_TREES [1/0]: print generated trs     (default: 1)\n");
//  printf("PRINT_ADDRS [1/0]: print tr addrs          (default: 0)\n\n");
//
//  if(argc == 6) {
//    HEAP_CELLS = atoi(argv[1]);
//    TREE_SIZE = atoi(argv[2]);
//    CYCLES = atoi(argv[3]);
//    PRINT_TREE = atoi(argv[4]);
//    PRINT_ADDRS = atoi(argv[5]);
//  }
//
//  if(HEAP_CELLS % 2) { HEAP_CELLS++; }
//  if(HEAP_CELLS < 2) {
//    printf("HEAP_CELLS must be > 1\n");
//    return 0;
//  } 
//
//  if(TREE_SIZE < 1) {
//    printf("TREE_SIZE must be > 0\n");
//    return 0;
//  }
//
//  if(CYCLES != 0 && CYCLES != 1) {
//    printf("CYCLES must be 0: NO or 1: YES\n");
//    return 0;
//  }
//
//  if(PRINT_TREE != 0 && PRINT_TREE != 1) {
//    printf("PRINT_TREES must be 0: NO or 1: YES\n");
//    return 0;
//  }
//
//  if(PRINT_ADDRS != 0 && PRINT_ADDRS != 1) {
//    printf("PRINT_ADDRS must be 0: NO or 1: YES\n");
//    return 0;
//  }
//
//  printf("\t\t***** TESTING CHENEY GC *****\n\n");
//  printf("\t\t***** Initializing heap *****\n\n");
//  printf("cell size:  %ld\n", sizeof(cell_t));
//  printf("heap cells: %d\n", HEAP_CELLS);
//  printf("MB eqv:     %lf\n\n", (sizeof(cell_t) * HEAP_CELLS) / 1000000.0);
//  hinit(HEAP_CELLS);
//
//  printf("\t\t***** Constructing root tree *****\n\n");
// 
//  srand(time(NULL));
//  build_tr(&root, TREE_SIZE, CYCLES);
//
//  if(PRINT_TREE) {
//    printf("tree:\n");
//    traverse_tr(root, TREE_SIZE);
//  }
//  
//  if(PRINT_ADDRS) {
//    printf("\ntree addrs:\n");
//    traverse_tr_addrs(root, TREE_SIZE);
//  }
//
//  if(!PRINT_TREE && !PRINT_ADDRS) { traverse_tr_intact(root, TREE_SIZE); }
//
//  printf("\n\t\t***** Start collecting *****\n\n");
//  clock_t start, end;
//  start = clock();
//  collect();
//  end = clock();
//
//  printf("Collection time: %fs\n\n", (double)(end - start) / CLOCKS_PER_SEC);
//
//  printf("\t\t***** Checking root tree *****\n\n");
//
//  if(PRINT_TREE) {
//    printf("tree:\n");
//    traverse_tr(root, TREE_SIZE);
//  }
//
//  if(PRINT_ADDRS) {
//    printf("\ntree addrs:\n");
//    traverse_tr_addrs(root, TREE_SIZE);
//  }
//
//  if(!PRINT_TREE && !PRINT_ADDRS) { traverse_tr_intact(root, TREE_SIZE); }
//
//  return 0;
//}
