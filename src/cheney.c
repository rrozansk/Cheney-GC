/******************************************************************************
 * FILE:    cheney.c                                                          *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 1/14/17                                                           *
 * EDITED:  4/24/17                                                           *
 * INFO:    Implementation of the interface located in cheney.h.              *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <cheney.h>

/******************************************************************************
 *                                                                            *
 *   G L O B A L S                                                            *
 *                                                                            *
 ******************************************************************************/
cell_t *from, *to;
cell_t *scan, *alloc;

unsigned long half;

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N S                                                        *
 *                                                                            *
 ******************************************************************************/
int isAtomic(void **p) {  return (*(int *)p & 1) != 0 || *p == NULL; }

int isPtr(void **p) { return (*(int *)p & 1) == 0 && *p != NULL; }

cell_t *cons(void *car, void *cdr) {
  cell_t *cell = halloc();
  cell->car = car;
  cell->cdr = cdr;
  return cell;
}

void *car(cell_t *cell) { return cell->car;  }

void *cdr(cell_t *cell) { return cell->cdr; }

void set_car(cell_t *cell, void *v) { cell->car = v;  }

void set_cdr(cell_t *cell, void *v) { cell->cdr = v;  }

cell_t *halloc() {
  if(alloc == from + half) { 
    collect();
    if(alloc >= from + half) {
      fprintf(stderr, "failure: insufficient memory, exiting...\n");
      exit(EXIT_FAILURE);
    }
  }
  return alloc++;
}

void hinit(unsigned long cells) {
  from = calloc(cells += (cells % 2), sizeof(cell_t));
  if(from == NULL) {
    fprintf(stderr, "failure: allocation of heap unsuccessful, exiting...\n");
    exit(EXIT_FAILURE);
  }
  alloc = from;
  half = cells / 2;
  to = from + half;
}

void copy_ref(void **p) {
  if(isAtomic(p)) { return; }            // only copy/update cell refs
  cell_t *obj = *p;                      // get the cells addr
  cell_t *fwd = obj->car;                // get the cells fwd addr
  if(from <= fwd && fwd < from + half) { // check if obj was already copied
    *(void **)p = fwd;                   // install fwd ref
  } else {                               // **else**
    cell_t *cell = alloc++;              // get a new cell
    set_car(cell, obj->car);             // copy old car ref
    set_cdr(cell, obj->cdr);             // copy old cdr ref
    set_car(obj, cell);                  // place fwd addr at old cells loc
    *(void **)p = cell;                  // install new ref
  }
}

void collect() {
  cell_t *tmp = from;                    // swap semi spaces
  scan = alloc = from = to;              // also set scan and alloc ptrs
  to = tmp;

  copy_ref(&root);                       // copy the root
  for(; scan != alloc; scan++) {         // scan until the allocating stops
    copy_ref(&(scan->car));              // update car ref
    copy_ref(&(scan->cdr));              // update cdr ref
  }
  printf("collection copied %d refs\n", abs(from-alloc));
}
