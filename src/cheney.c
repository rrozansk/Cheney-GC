/******************************************************************************
 * FILE:    cheney.c                                                          *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 1/14/17                                                           *
 * EDITED:  11/11/17                                                          *
 * INFO:    Implementation of the interface located in cheney.h.              *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <stdlib.h>
#include <cheney.h>

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct heap {
  void *root;                               // ptr to all reachable objects
  void *alloc;                              // current head of free memory
  void *to, *from;                          // semi space differentiation
  unsigned long half;                       // semi space size (>= 32 bits)
  char dynamic;                             // flag for dynamic heap expansion
  unsigned long (*expander)(unsigned long); // optional custom expander
} heap_t;

typedef struct cell { void *car, *cdr; } cell_t;

/******************************************************************************
 *                                                                            *
 *   H E L P E R S                                                            *
 *                                                                            *
 ******************************************************************************/
unsigned long default_expander(unsigned long cells) { return cells * 2; }

int rescale(heap_t *heap, unsigned long semi_cells) {
  // ensure left semi-space usage to properly update pointers
  if(heap->to < heap->from) { collect(heap); }
  unsigned long allocated_cells = heap->alloc - heap->from;
  semi_cells -= semi_cells % 2;
  void *base = realloc(heap->from, semi_cells * 2 * sizeof(cell_t));
  if(!base) { return 0; }
  heap->half = semi_cells / 2;
  heap->from = base;
  heap->to = heap->from + heap->half;
  heap->alloc = heap->from + allocated_cells;
  if(is_cell(&(heap->root))) { heap->root = heap->from; }
  return 1;
}

cell_t *halloc(heap_t *heap) {
  if(heap->alloc == heap->from + heap->half) {
    collect(heap);
    if(heap->alloc == heap->from + heap->half) {
      if(!heap->dynamic) { return NULL; }
        unsigned long semi_size = heap->expander(heap->half);
        if(semi_size <= heap->half) { return NULL; }
        if(!rescale(heap, semi_size)) { return NULL; }
    }
  }
  return heap->alloc++;
}

void copy_ref(heap_t *heap, void **p) {
  if(is_atom(p)) { return; }                     // only copy/update cells refs
  cell_t *obj = *p;                              // get the cells addr
  cell_t *fwd = obj->car;                        // get the cells fwd addr
  if((cell_t *)heap->from <= fwd &&
     fwd < (cell_t *)heap->from + heap->half) {  // check if already copied
    *(void **)p = fwd;                           // install fwd ref
  } else {                                       // **else**
    cell_t *cell = heap->alloc++;                // get a new cell
    set_car(cell, obj->car);                     // copy old car ref
    set_cdr(cell, obj->cdr);                     // copy old cdr ref
    set_car(obj, cell);                          // place fwd addr at old loc
    *(void **)p = cell;                          // install new ref
  }
}

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N S                                                        *
 *                                                                            *
 ******************************************************************************/
heap_t *make_heap(unsigned long cells) {
  heap_t *heap = malloc(sizeof(heap_t));
  if(!heap) { return NULL; }
  
  heap->from = calloc(cells -= (cells % 2), sizeof(cell_t));
  if(!heap->from) {
    free(heap);
    return NULL;
  }
  heap->half = cells / 2;
  heap->alloc = heap->from;
  heap->to = heap->from + heap->half;
  heap->root = NULL;
  heap->dynamic = 0;
  heap->expander = default_expander;
  return heap;
}

void free_heap(heap_t **heap) {
  ((*heap)->from < (*heap)->to) ? free((*heap)->from) : free((*heap)->to);
  free(*heap);
  *heap = NULL;
}

void set_dynamic(heap_t *heap, int dynamic) { heap->dynamic = dynamic; }

int get_dynamic(heap_t *heap) { return heap->dynamic; }

void set_expander(heap_t *heap, unsigned long (*expander)(unsigned long)) {
  heap->expander = expander;
}

unsigned long (*get_expander(heap_t *heap))(unsigned long) {
  if(heap->expander == default_expander) { return NULL; }
  return heap->expander;
}

int resize(heap_t *heap, unsigned long cells) {
  unsigned long semi_cells = cells / 2;
  if(semi_used(heap) > semi_cells) { return 0; }
  return rescale(heap, semi_cells);
}

void set_root(heap_t *heap, void *root) { heap->root = root; }

void *get_root(heap_t *heap) { return heap->root; }

void collect(heap_t *heap) {
  cell_t *tmp = heap->from;                 // swap semi spaces
  heap->from = heap->to;
  heap->to = tmp;

  cell_t *scan = heap->alloc = heap->from;  // set scan and alloc ptrs

  copy_ref(heap, &(heap->root));            // copy the root
  for(; scan != heap->alloc; scan++) {      // scan until reaching alloc
    copy_ref(heap, &(scan->car));           // update car ref
    copy_ref(heap, &(scan->cdr));           // update cdr ref
  }
}

unsigned long heap_size(heap_t *heap) { return heap->half * 2; }

unsigned long semi_size(heap_t *heap) { return heap->half; }

unsigned long semi_used(heap_t *heap) { return heap->alloc - heap->from; }

unsigned long semi_left(heap_t *heap) { 
  return heap->half - (heap->alloc - heap->from);
}

cell_t *cell(heap_t *heap) { return halloc(heap); }

cell_t *cons(heap_t *heap, void *car, void *cdr) {
  cell_t *cell = halloc(heap);
  if(cell == NULL) { return NULL; }
  cell->car = car;
  cell->cdr = cdr;
  return cell;
}

void *car(cell_t *cell) { return cell->car;  }

void *cdr(cell_t *cell) { return cell->cdr; }

void set_car(cell_t *cell, void *v) { cell->car = v;  }

void set_cdr(cell_t *cell, void *v) { cell->cdr = v;  }

char is_atom(void **value) { return (*(int *)value & 1) != 0 || *value == NULL; }

char is_cell(void **value) { return (*(int *)value & 1) == 0 && *value != NULL; }
