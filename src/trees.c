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

  for(leaf_c = 0, stk_ptr = 0;;) {
    if(!cells) { 
      set_car(root, genLeaf(&leaf_c, cycles, ancestor));
      set_cdr(root, genLeaf(&leaf_c, cycles, ancestor));
      if(!stk_ptr) { return; }
      cells = size_stk[stk_ptr];
      root = tr_stk[stk_ptr--];
    } else if(cells == 1) {
      set_car(root, cons(NULL, NULL));
      if(rand() % 2) { ancestor = car(root); }
      cells--;
      set_cdr(root, genLeaf(&leaf_c, cycles, ancestor));
      root = car(root);
    } else {
      set_car(root, cons(NULL, NULL));
      set_cdr(root, cons(NULL, NULL));
      int r = rand() % 3;
      if(r == 1) { ancestor = car(root); }
      if(r == 2) { ancestor = cdr(root); }
      cells -= 2;
      size_stk[++stk_ptr] = cells - (cells / 2);
      cells = cells / 2;
      tr_stk[stk_ptr] = cdr(root);
      root = car(root);
    }
  }
}

typedef struct hash_t {
  unsigned long size;
  cell_t **tbl;
} hash_t;

hash_t *hash(unsigned long size) {
  hash_t *hash = malloc(sizeof(hash_t));
  hash->size = size;
  hash->tbl = calloc(size, sizeof(cell_t *));
  return hash;
}

void hash_insert(hash_t *h, cell_t *cell, int *cell_pos) {
  int loc = (*(int *)cell * 15485863) % h->size;
  cell_t *bucket = *(h->tbl + loc);
  for(; bucket; bucket = cdr(bucket)) {
    if(car(car(bucket)) == cell) { return; } // already exists
  }
  cell_t *elem = malloc(sizeof(cell_t));
  set_car(elem, cell);
  set_cdr(elem, cell_pos);
  cell_t *link = malloc(sizeof(cell_t));
  set_car(link, elem);
  set_cdr(link, *(h->tbl + loc));
  *(h->tbl + loc) = link;
}

int hash_ref(hash_t *h, cell_t *cell) {
  int loc = (*(int *)cell * 15485863) % h->size;
  cell_t *bucket = *(h->tbl + loc);
  for(; bucket && car(car(bucket)) != cell; bucket = cdr(bucket));
  if(!bucket) { return 0; } // not found
  return *(int *)cdr(car(bucket));
}

int c;

void print_help(void *tr, traversal_t walk, hash_t *seen) {
  int loc;
  if(tr == NULL) { 
    printf("()"); 
  } else if(isAtomic(&tr)) {
    clrBit(&tr, 0);
    if(walk == REG) { 
      printf("%d", *(int *)tr); 
    } else if(walk == ADDRS) { 
      printf("\t\tleaf %d: %p\n", *(int *)tr, tr); 
    } else {  } // walk == INTACK_CHECK
  } else if(isPtr(&tr) && (loc = hash_ref(seen, tr))) {
    if(walk == ADDRS) { printf("\t\tleaf #cycle: %d#: %p\n", loc, tr); }
    else if(walk == INTACT_CHECK) { }
    else { printf("#cycle: %d#", loc); }
  } else if(isPtr(&tr)) {
    int *i = malloc(sizeof(int));
    *i = c++;
    hash_insert(seen, tr, i);
    if(walk == REG) { 
      printf("(");
      print_help(car(tr), walk, seen);
      printf(" . ");
      print_help(cdr(tr), walk, seen);
      printf(")");
    } else if(walk == ADDRS) { 
      printf("cell: %p\n", tr);
      print_help(car(tr), walk, seen);
      print_help(cdr(tr), walk, seen);
    } else {  // walk == INTACK_CHECK
      print_help(car(tr), walk, seen);
      print_help(cdr(tr), walk, seen);
    }
  } else { 
    printf("ERR: %p\n", tr); 
  }
}

void traverse_tr(void *tr, traversal_t walk) {
  c = 1;
  print_help(tr, walk, hash(1000));
  printf("\n");
}
