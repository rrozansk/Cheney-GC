/******************************************************************************
 * FILE:    testCHENEY.c                                                      *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 10/31/17                                                          *
 * EDITED:  11/1/17                                                           *
 * INFO:    Test file for implementation of the interface located in cheney.h *
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
#define TOTAL_TESTS 18

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
testResultCHENEY_t testAtomicNullCheck() {
  int *i = (int *)NULL;
  return (isAtomic((void **)&i)) ? CHENEY_PASS : CHENEY_FAIL;
}

testResultCHENEY_t testAtomicCheckSuccess() {
  int *i = (int *)0b1;
  return (isAtomic((void **)&i)) ? CHENEY_PASS : CHENEY_FAIL;
}

testResultCHENEY_t testAtomicCheckFailure() {
  int *i = (int *)0b0; // 0b0 == NULL
  return (isAtomic((void **)&i)) ? CHENEY_PASS : CHENEY_FAIL;
}

testResultCHENEY_t testPointerNullCheck() {
  int *i = (int *)NULL;
  return (isPtr((void **)&i)) ? CHENEY_FAIL : CHENEY_PASS;
}

testResultCHENEY_t testPointerCheckSuccess() { // 0b0 == NULL
  int *i = (int *)0b0;
  return (isPtr((void **)&i)) ? CHENEY_FAIL : CHENEY_PASS;
}

testResultCHENEY_t testPointerCheckFailure() {
  int *i = (int *)0b1;
  return (isPtr((void **)&i)) ? CHENEY_FAIL : CHENEY_PASS;
}

testResultCHENEY_t testInitCollectorEvenCells() {
// void hinit(unsigned long cells) {
  return CHENEY_FAIL;
}

testResultCHENEY_t testInitCollectorOddCells() {
// void hinit(unsigned long cells) {
  return CHENEY_FAIL;
}

testResultCHENEY_t testAutomaticCollection() {
// void collect() {
  return CHENEY_FAIL;
}

testResultCHENEY_t testManualCollection() {
// void collect() {
  return CHENEY_FAIL;
}

testResultCHENEY_t testCellAlloc() {
// cell_t *halloc() {
  return CHENEY_FAIL;
}

testResultCHENEY_t testConsCellAlloc() {
// cell_t *cons(void *car, void *cdr) {
  return CHENEY_FAIL;
}

testResultCHENEY_t testConsCellCar() {
// void *car(cell_t *cell) { return cell->car;  }
  return CHENEY_FAIL;
}

testResultCHENEY_t testConsCellCdr() {
// void *cdr(cell_t *cell) { return cell->cdr; }
  return CHENEY_FAIL;
}

testResultCHENEY_t testConsCellSetCar() {
// void set_car(cell_t *cell, void *v) { cell->car = v;  }
  return CHENEY_FAIL;
}

testResultCHENEY_t testConsCellSetCdr() {
// void set_cdr(cell_t *cell, void *v) { cell->cdr = v;  }
  return CHENEY_FAIL;
}

testResultCHENEY_t testCyclicCollection() {
  return CHENEY_FAIL;
}

testResultCHENEY_t testDynamicHeapExpansion() {
  return CHENEY_FAIL;
}

/******************************************************************************
 *                                                                            *
 *   M A I N                                                                  *
 *                                                                            *
 ******************************************************************************/
void *TESTS[TOTAL_TESTS][2] = {
  { testAtomicNullCheck,                      "testAtomicNullCheck"           },
  { testAtomicCheckSuccess,                   "testAtomicCheckSuccess"        },
  { testAtomicCheckFailure,                   "testAtomicCheckFailure"        },
  { testPointerNullCheck,                     "testPointerNullCheck"          },
  { testPointerCheckSuccess,                  "testPointerCheckSuccess"       },
  { testPointerCheckFailure,                  "testPointerCheckFailure"       },
  { testInitCollectorEvenCells,               "testInitCollectorEvenCells"    },
  { testInitCollectorOddCells,                "testInitCollectorOddCells"     },
  { testAutomaticCollection,                  "testAutomaticCollection"       },
  { testManualCollection,                     "testManualCollection"          },
  { testCellAlloc,                            "testCellAlloc"                 },
  { testConsCellAlloc,                        "testConsCellAlloc"             },
  { testConsCellCar,                          "testConsCellCar"               },
  { testConsCellCdr,                          "testConsCellCdr"               },
  { testConsCellSetCar,                       "testConsCellSetCar"            },
  { testConsCellSetCdr,                       "testConsCellSetCdr"            },
  { testCyclicCollection,                     "testCyclicCollection"          },
  { testDynamicHeapExpansion,                 "testDynamicHeapExpansion"      }
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
