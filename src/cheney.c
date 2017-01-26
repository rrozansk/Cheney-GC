/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/14/17
 Edited:  1/25/17
*/

/**********************************************************************

    I N C L U D E S

***********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <cheney.h>

/**********************************************************************

    G L O B A L S

***********************************************************************/
cell_t *fromSpace, *toSpace;
cell_t *scanPtr, *freePtr;

int semiSize;

#if DEBUG 
int copy_alloc;
#endif

/**********************************************************************

    F U N C T I O N S

***********************************************************************/
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
  if(freePtr == fromSpace+semiSize) { collect((void **)&root); }
  return freePtr++;
}

void hinit(unsigned int cells) {
  fromSpace = calloc(cells + (cells % 2), sizeof(cell_t));
  if(fromSpace == NULL) {
    fprintf(stderr, "allocation of heap unsuccesful, exiting...\n");
    exit(EXIT_FAILURE);
  }
  freePtr = fromSpace;
  semiSize = cells / 2;
  toSpace = fromSpace + semiSize;
}

void copy_ref(void **p) {
  if(!isPtr(p)) { return; }
  cell_t *obj = *p;
  if(fromSpace <= obj && obj < fromSpace+semiSize) { 
    *(cell_t **)p = obj; 
  } else {
    #if DEBUG 
    copy_alloc++;
    #endif
    cell_t *cell = freePtr++;
    set_car(cell, ((cell_t *)obj)->car);
    set_cdr(cell, ((cell_t *)obj)->cdr);
    *(cell_t **)p = cell;
  }
}

void collect(void **r) {
  cell_t *tmp = fromSpace;
  fromSpace = toSpace;
  freePtr = fromSpace;
  scanPtr = freePtr;
  toSpace = tmp;
  #if DEBUG 
  copy_alloc = 0;
  #endif

  copy_ref(r);
  while(scanPtr != freePtr) {
    copy_ref(&(scanPtr->car));
    copy_ref(&(scanPtr->cdr));
    scanPtr++;
  }
  #if DEBUG 
  printf("collection copied %d refs\n", copy_alloc);
  #endif
}
