/******************************************************************************
 * FILE:    cheney.c                                                          *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 10/31/17                                                          *
 * EDITED:  12/28/17                                                          *
 * INFO:    Table driven testing for the interface located at cheney.h.       *
 *          Extending the test suite is possible if so desired and can be     *
 *          done with minimal effort. First, it requires defining a new test. *
 *          A test is just a function which takes no arguments and returns a  *
 *          'testResult_t' type as defined below. Second, an entry must be    *
 *          added to the table. A table entry is an array literal containing  *
 *          two items. Index zero contains the name of test function just     *
 *          written. Index one contains a short string description to print   *
 *          when ran which identifies the specific test. Third, and finally,  *
 *          the integer value of 'TOTAL_TESTS' must be incremeted by one.     *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <cheney.h>
#include <stdio.h>

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef enum testResult { PASS, FAIL } testResult_t; /* Test function return */

typedef testResult_t (*testFunction_t)();  /* Test function prototype */

/******************************************************************************
 *                                                                            *
 *   H E L P E R S                                                            *
 *                                                                            *
 ******************************************************************************/
unsigned long custom_expander(unsigned long size) { return size + 20; }

/******************************************************************************
 *                                                                            *
 *   T E S T S                                                                *
 *                                                                            *
 ******************************************************************************/
testResult_t MakeFreeHeapOddCells() {
  heap_t *heap = make_heap(9);
  if(!heap) { return FAIL; }

  free_heap(&heap);

  return !heap ? PASS : FAIL;
}

testResult_t MakeFreeHeapEvenCells() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  free_heap(&heap);

  return !heap ? PASS : FAIL;
}

testResult_t GetDynamicDefault() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  int dynamic = get_dynamic(heap);
  free_heap(&heap);

  return !dynamic ? PASS : FAIL;
}

testResult_t SetGetDynamicOn() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  set_dynamic(heap, 1);
  int dynamic = get_dynamic(heap);
  free_heap(&heap);

  return dynamic ? PASS : FAIL;
}

testResult_t SetGetDynamicOnOff() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  set_dynamic(heap, 1);
  int on_dynamic = get_dynamic(heap);
  set_dynamic(heap, 0);
  int on_again = get_dynamic(heap);
  free_heap(&heap);

  return on_dynamic && !on_again ? PASS : FAIL;
}

testResult_t GetDefaultExpander() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  unsigned long (*expander)(unsigned long) = get_expander(heap);
  free_heap(&heap);

  return !expander ? PASS : FAIL;
}

testResult_t SetGetCustomExpander() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  set_expander(heap, custom_expander);

  unsigned long (*expander)(unsigned long) = get_expander(heap);
  free_heap(&heap);

  return expander == custom_expander ? PASS : FAIL;
}

testResult_t GetDefaultRoot() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  void *root = get_root(heap);
  free_heap(&heap);

  return !root ? PASS : FAIL;
}

testResult_t SetGetCustomRoot() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  void *s_root = &heap;
  set_root(heap, s_root);
  void *g_root = get_root(heap);
  free_heap(&heap);

  return s_root == g_root ? PASS : FAIL;
}

testResult_t EmptyCollections() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  int why_not;
  for(why_not = 10; why_not; why_not--) { collect(heap); }
  free_heap(&heap);

  return PASS;
}

testResult_t HeapSize() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  unsigned long size = heap_size(heap);
  free_heap(&heap);

  return size == 8 ? PASS : FAIL;
}

testResult_t HeapSemiSize() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  unsigned long size = semi_size(heap);
  free_heap(&heap);

  return size == 4 ? PASS : FAIL;
}

testResult_t HeapSemiUsed() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  unsigned long size = semi_used(heap);
  free_heap(&heap);

  return size == 0 ? PASS : FAIL;
}

testResult_t HeapSemiLeft() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  unsigned long size = semi_left(heap);
  free_heap(&heap);

  return size == 4 ? PASS : FAIL;
}

testResult_t HeapResizeSmaller() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  int successful = resize(heap, 4);
  int size = heap_size(heap);
  free_heap(&heap);

  return successful && size == 4 ? PASS : FAIL;
}

testResult_t HeapResizeLarger() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  int successful = resize(heap, 16);
  int size = heap_size(heap);
  free_heap(&heap);

  return successful && size == 16 ? PASS : FAIL;
}

testResult_t EmptyCellAllocation() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  cell_t *_cell = cell(heap);
  free_heap(&heap);

  return _cell ? PASS : FAIL;
}

testResult_t InitializedCellAllocation() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  cell_t *_cell = cons(heap, heap, heap);
  free_heap(&heap);

  return _cell ? PASS : FAIL;
}

testResult_t CellFirstFieldGetter() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  int foo, bar;
  cell_t *_cell = cons(heap, &foo, &bar);
  void *val = car(_cell);
  free_heap(&heap);

  return val == &foo ? PASS : FAIL;
}

testResult_t CellSecondFieldGetter() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  int foo, bar;
  cell_t *_cell = cons(heap, &foo, &bar);
  void *val = cdr(_cell);
  free_heap(&heap);

  return val == &bar ? PASS : FAIL;
}

testResult_t CellFirstFieldSetter() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  cell_t *_cell = cons(heap, heap, heap);
  set_car(_cell, NULL);
  void *val = car(_cell);
  free_heap(&heap);

  return !val ? PASS : FAIL;
}

testResult_t CellSecondFieldSetter() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  cell_t *_cell = cons(heap, heap, heap);
  set_cdr(_cell, NULL);
  void *val = cdr(_cell);
  free_heap(&heap);

  return !val ? PASS : FAIL;
}

testResult_t AtomicDataPass() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  void *value = (void *)0b1;

  return is_atom(&value) ? PASS : FAIL;
}

testResult_t AtomicDataFail() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  return !is_atom((void **)&heap) ? PASS : FAIL;
}

testResult_t AtomicDataNull() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  void *value = NULL;

  return is_atom(&value) ? PASS : FAIL;
}

testResult_t CellDataPass() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  cell_t *value = cell(heap);

  return is_cell((void **)&value) ? PASS : FAIL;
}

testResult_t CellDataFail() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  void *value = (void *)0b1;

  return !is_cell(&value) ? PASS : FAIL;
}

testResult_t CellDataNull() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  cell_t *value = NULL;

  return !is_cell((void **)&value) ? PASS : FAIL;
}

testResult_t CorrectAmountCollected() {
  heap_t *heap = make_heap(10);
  if(!heap) { return FAIL; }

  int cells;
  for(cells = 5; cells; cells--) {
    if(!cell(heap)) {
      free_heap(&heap);
      return FAIL;
    }
  }

  if(!(semi_used(heap) == 5 &&
       semi_left(heap) == 0 &&
       cell(heap))) { // cause collection of 5 and alloc of 1
      free_heap(&heap);
      return FAIL;
  }

  return (semi_used(heap) == 1 && semi_left(heap) == 4) ? PASS : FAIL;
}

testResult_t StaticHeapCellAllocationFailure() { 
  heap_t *heap = make_heap(8); // non-dynamic by default
  if(!heap) { return FAIL; }

  void *root = cell(heap);
  set_root(heap, root);
  set_car(root, cell(heap));
  set_cdr(root, cell(heap));
  set_cdr(cdr(root), cell(heap));

  cell_t *_cell = cell(heap);
  free_heap(&heap);
 
  return (!_cell) ? PASS : FAIL;
}

testResult_t DynamicHeapDefaultExpand() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  set_dynamic(heap, 1); // default expander

  void *root = cell(heap);
  set_root(heap, root);
  set_car(root, cell(heap));
  set_cdr(root, cell(heap));
  set_cdr(cdr(root), cell(heap));
  set_cdr(car(root), cell(heap)); // collection with expansion
  
  unsigned long size = heap_size(heap);
  unsigned long used = semi_used(heap);
  unsigned long left = semi_left(heap);
  free_heap(&heap);

  return (size == 16 && used == 5 && left == 3) ? PASS : FAIL;
}

testResult_t DynamicHeapCustomExpand() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  set_dynamic(heap, 1);
  set_expander(heap, custom_expander);

  void *root = cell(heap);
  set_root(heap, root);
  set_car(root, cell(heap));
  set_cdr(root, cell(heap));
  set_cdr(cdr(root), cell(heap));
  set_cdr(car(root), cell(heap)); // collection with expansion
  
  // custom expander for semi_size -> semi_size+20=24 *2=48
  unsigned long size = heap_size(heap);
  unsigned long used = semi_used(heap);
  unsigned long left = semi_left(heap);
  free_heap(&heap);

  return (size == 48 && used == 5 && left == 19) ? PASS : FAIL;
}

testResult_t SafeRootedObjects() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  void *root = cell(heap); // make tiny 3 node tree
  set_root(heap, root);
  set_car(root, cell(heap));
  set_cdr(root, cell(heap));
  collect(heap);
  
  if(semi_used(heap) != 3 || semi_left(heap) != 1) { return FAIL; }

  root = get_root(heap); // check if tree still intact
  if(!is_cell(&root)) { return FAIL; }

  void *tmp = car(root);
  if(!is_cell(&tmp)) { return FAIL; }
  tmp = cdr(root);
  if(!is_cell(&tmp)) { return FAIL; }

  tmp = car(cdr(root));
  if(!is_atom(&tmp)) { return FAIL; }
  tmp = cdr(cdr(root));
  if(!is_atom(&tmp)) { return FAIL; }
  tmp = car(car(root));
  if(!is_atom(&tmp)) { return FAIL; }
  tmp = cdr(car(root));
  if(!is_atom(&tmp)) { return FAIL; }

  free_heap(&heap);
  return PASS;
}

testResult_t ResizeSmallerAfterCollection() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  void *root = cell(heap);
  set_root(heap, root);
  set_car(root, cell(heap));
  set_cdr(root, cell(heap));

  collect(heap);
  resize(heap, 6); // exact resize
  collect(heap);
  unsigned long size = heap_size(heap);
  unsigned long used = semi_used(heap);
  unsigned long left = semi_left(heap);
  free_heap(&heap);

  return (size == 6 && used == 3 && left == 0) ? PASS : FAIL;
}

testResult_t ResizeLallerAfterCollection() {
  heap_t *heap = make_heap(6);
  if(!heap) { return FAIL; }

  void *root = cell(heap);
  set_root(heap, root);
  set_car(root, cell(heap));
  set_cdr(root, cell(heap));

  collect(heap);
  resize(heap, 12); // exact resize
  collect(heap);
  unsigned long size = heap_size(heap);
  unsigned long used = semi_used(heap);
  unsigned long left = semi_left(heap);
  free_heap(&heap);

  return (size == 12 && used == 3 && left == 3) ? PASS : FAIL;
}

testResult_t DynamicResizeFromRightSemi() {
  heap_t *heap = make_heap(8);
  if(!heap) { return FAIL; }

  set_dynamic(heap, 1); // default expander

  collect(heap); // cause allocation from right semi space

  //void *root = cell(heap); NOTE: invalid ref after a collection
  // ALWAYS use set/get_root to manage root, instead:
  set_root(heap, cell(heap));
  if(!get_root(heap)) { return FAIL; }
  set_car(get_root(heap), cell(heap));
  set_cdr(get_root(heap), cell(heap));
  set_cdr(cdr(get_root(heap)), cell(heap));
  set_cdr(car(get_root(heap)), cell(heap)); // collection with expansion
  
  unsigned long size = heap_size(heap);
  unsigned long used = semi_used(heap);
  unsigned long left = semi_left(heap);
  free_heap(&heap);

  return (size == 16 && used == 5 && left == 3) ? PASS : FAIL;
}

testResult_t DynamicHeapOnOff() {
  heap_t *heap = make_heap(2);
  if(!heap) { return FAIL; }

  set_dynamic(heap, 1);
  set_root(heap, cell(heap));

  cell_t *_cell = cell(heap); // collect and expand heap to 4 cells
  if(heap_size(heap) != 4) { return FAIL; }

  set_dynamic(heap, 0);

  set_car(get_root(heap), _cell);

  // allocation failure since heap cannot expand anymore
  if((_cell = cell(heap))) { return FAIL; }

  free_heap(&heap);

  return PASS;
}

/******************************************************************************
 *                                                                            *
 *   T E S T    T A B L E                                                     *
 *                                                                            *
 ******************************************************************************/
#define FUNCTION    0  // function ptr @idx 0
#define NAME        1  // test name @idx 1
#define TOTAL_TESTS 37 // # tests in array/table

void *TESTS[TOTAL_TESTS][2] = {
  { MakeFreeHeapOddCells,                 "MakeFreeHeapOddCells"              },
  { MakeFreeHeapEvenCells,                "MakeFreeHeapEvenCells"             },
  { GetDynamicDefault,                    "GetDynamicDefault"                 },
  { SetGetDynamicOn,                      "SetGetDynamicOn"                   },
  { SetGetDynamicOnOff,                   "SetGetDynamicOnOff"                },
  { GetDefaultExpander,                   "GetDefaultExpander"                },
  { SetGetCustomExpander,                 "SetGetCustomExpander"              },
  { GetDefaultRoot,                       "GetDefaultRoot"                    },
  { SetGetCustomRoot,                     "SetGetCustomRoot"                  },
  { EmptyCollections,                     "EmptyCollections"                  },
  { HeapSize,                             "HeapSize"                          },
  { HeapSemiSize,                         "HeapSemiSize"                      },
  { HeapSemiUsed,                         "HeapSemiUsed"                      },
  { HeapSemiLeft,                         "HeapSemiLeft"                      },
  { HeapResizeSmaller,                    "HeapResizeSmaller"                 },
  { HeapResizeLarger,                     "HeapResizeLarger"                  },
  { EmptyCellAllocation,                  "EmptyCellAllocation"               },
  { InitializedCellAllocation,            "InitializedCellAllocation"         },
  { CellFirstFieldGetter,                 "CellFirstFieldGetter"              },
  { CellSecondFieldGetter,                "CellSecondFieldGetter"             },
  { CellFirstFieldSetter,                 "CellFirstFieldSetter"              },
  { CellSecondFieldSetter,                "CellSecondFieldSetter"             },
  { AtomicDataPass,                       "AtomicDataPass"                    },
  { AtomicDataFail,                       "AtomicDataFail"                    },
  { AtomicDataNull,                       "AtomicDataNull"                    },
  { CellDataPass,                         "CellDataPass"                      },
  { CellDataFail,                         "CellDataFail"                      },
  { CellDataNull,                         "CellDataNull"                      },
  { CorrectAmountCollected,               "CorrectAmountCollected"            },
  { StaticHeapCellAllocationFailure,      "StaticHeapCellAllocationFailure"   },
  { DynamicHeapDefaultExpand,             "DynamicHeapDefaultExpand"          },
  { DynamicHeapCustomExpand,              "DynamicHeapCustomExpand"           },
  { SafeRootedObjects,                    "SafeRootedObjects"                 },
  { ResizeSmallerAfterCollection,         "ResizeSmallerAfterCollection"      },
  { ResizeLallerAfterCollection,          "ResizeLallerAfterCollection"       },
  { DynamicResizeFromRightSemi,           "DynamicResizeFromRightSemi"        },
  { DynamicHeapOnOff,                     "DynamicHeapOnOff"                  },
};

/******************************************************************************
 *                                                                            *
 *   T E S T    D R I V E R                                                   *
 *                                                                            *
 ******************************************************************************/
int main() {

  testResult_t result;
  testFunction_t test;

  int passes = 0;
  int fails = 0;

  int idx;
  for(idx = 0; idx < TOTAL_TESTS; idx++) {
    test = TESTS[idx][FUNCTION];
    result = test();
    if(result == PASS) {
      passes++;
      fprintf(stdout, "PASS: %s\n", (char *)TESTS[idx][NAME]);
    } else {
      fprintf(stdout, "FAIL: %s\n", (char *)TESTS[idx][NAME]);
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
