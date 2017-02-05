/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/15/17
 Edited:  2/5/17
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
#include <math.h>

/**********************************************************************

      F U N C T I O N S

***********************************************************************/
void *genLeaf(int *count, int cycles, cell_t *ancestor) {
  if(cycles && rand() % 2) { return ancestor;  }
  void *i = malloc(sizeof(int));
  *(int *)i = (*count)++;
  setBit((void **)&i, 0);
  return i;
}
 
void build_tr(void **r, int cells, int cycles) {
  cell_t *ancestor, *root; 
  *r = ancestor = root = cons(NULL, NULL);
  cells--;

  int size_stk[(int)floor((log(cells + 1) - 1) / log(2))];
  cell_t *tr_stk[(int)floor((log(cells + 1) - 1) / log(2))];
  int stk_ptr, leaf_c;

  for(leaf_c = 0, stk_ptr = 0;;) { // assign new value to ancestor?
    if(!cells) { 
      set_car(root, genLeaf(&leaf_c, cycles, ancestor));
      set_cdr(root, genLeaf(&leaf_c, cycles, ancestor));
      if(!stk_ptr) { return; }
      cells = size_stk[stk_ptr];
      root = tr_stk[stk_ptr--];
    } else if(cells == 1) {
      set_car(root, cons(NULL, NULL));
      cells--;
      set_cdr(root, genLeaf(&leaf_c, cycles, ancestor));
      root = car(root);
    } else {
      set_car(root, cons(NULL, NULL));
      set_cdr(root, cons(NULL, NULL));
      cells -= 2;
      size_stk[++stk_ptr] = cells - (cells / 2);
      cells = cells / 2;
      tr_stk[stk_ptr] = cdr(root);
      root = car(root);
    }
  }
}

typedef cell_t frame_t;
frame_t *stk() { return NULL; }
frame_t *push(void *data, frame_t *stk) { 
  frame_t *f = malloc(sizeof(frame_t)); // so we dont cause a collection
  f->car = data;
  f->cdr = stk;
  return f;
}

int cycle(cell_t *c, frame_t *stk) {
  for(; stk != NULL; stk = cdr(stk)) {
    if(c == car(stk)) { return 1; }
  }
  return 0;
}

void printG(void *g, frame_t *stk, traversal_t walk) {
  if(g == NULL) { printf("()"); }
  else if(!isPtr(&g) && !isAtomic(&g)) { printf("ERR: %p\n", g); }
  else if(isAtomic(&g)) {
    if(walk == INTACT_CHECK) { return; }
    else {
      clrBit(&g, 0);
      if(walk == REG) { printf("%d", *(int *)g); }
      else { printf("\t\tleaf %d: %p\n", *(int *)g, g); } 
    }
  } else { // isPtr(g)
    if(cycle(g, stk)) {
      if(walk == ADDRS) { printf("\t\tleaf #cycle#: %p\n", g); }
      else if(walk == INTACT_CHECK) { }
      else { printf("#cycle#"); }
      return;
    } 
    frame_t *s = push(g, stk);
    if(walk == INTACT_CHECK) {  
      printG(car(g), s, walk);
      printG(cdr(g), s, walk);
    }
    else if(walk == REG) {  
      printf("(");
      printG(car(g), s, walk);
      printf(" . ");
      printG(cdr(g), s, walk);
      printf(")");
    } else { // ADDRS
      printf("cell: %p\n", g);
      printG(car(g), s, walk);
      printG(cdr(g), s, walk);
    }
  }
}

void traverse_tr(void *tr, traversal_t walk) {
  printG(tr, stk(), walk);
  printf("\n");
}
