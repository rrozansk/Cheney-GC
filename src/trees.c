/**********************************************************************

    F I L E   I N F O R M A T I O N

***********************************************************************/
/*
 Author:  Ryan Rozanski
 Created: 1/15/17
 Edited:  2/16/17
*/

/**********************************************************************

      I N C L U D E S

***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
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
  int stk_ptr, leaf_c, rn;

  for(leaf_c = stk_ptr = 0; root != tr_stk[0];) {
    if(!cells) { 
      set_car(root, genLeaf(&leaf_c, cycles, ancestor));
      set_cdr(root, genLeaf(&leaf_c, cycles, ancestor));
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
      rn = rand() % 3;
      if(rn == 1) { ancestor = car(root); }
      if(rn == 2) { ancestor = cdr(root); }
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

void hash_insert(hash_t *h, cell_t *cell, int cell_pos) {
  int loc = (*(int *)cell * 15485863) % h->size;
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
  int loc = (*(int *)cell * 15485863) % h->size;
  cell_t *bucket = *(h->tbl + loc);
  for(; bucket && car(car(bucket)) != cell; bucket = cdr(bucket));
  if(!bucket) { return 0; } // not found
  return *(int *)cdr(car(bucket));
}

void traverse_tr(void *tr, int cells, traversal_t walk) {
  int loc, stk_ptr, flag, rp;
  hash_t *seen = hash(1000);
  int max = (int)floor((log(cells + 1) - 1) / log(2)); // TODO: do max/stk_ptr play roles for # or parens to print?
  void *stk[(int)floor((log(cells + 1) - 1) / log(2))];
  printf("STK MAX: %d\n", max);

  for(cells = 1, stk_ptr = flag = loc = rp = 0; tr != stk[0];) {
    if(isAtomic(&tr) || (loc = hash_ref(seen, tr))) {
      if(!loc) { clrBit(&tr, 0); }
      if(walk == ADDRS) {
        loc ? printf("\t\tleaf #cycle: %d#: %p\n", loc, tr) : printf("\t\tleaf %d: %p\n", *(int *)tr, tr);
      }
      if(walk == REG) { 
        loc ? printf("#cycle: %d#", loc) : printf("%d", *(int *)tr);
        if(flag) { do { printf(")"); } while(--rp > stk_ptr); } // FIXME: print correct # of ')'
        if(stk_ptr) { printf(" . "); }
      }
      flag = 1; // printing cdr
      tr = stk[stk_ptr--]; 
    } else if(isPtr(&tr)) {
      if(walk == ADDRS) { printf("cell: %p\n", tr); } 
      if(walk == REG) { printf("(");  }
      hash_insert(seen, tr, cells++);
      rp++; // right parens building up to be printed
      flag = 0; // printing car
      stk[++stk_ptr] = cdr(tr); 
      tr = car(tr);
    } else {
      printf("error: unrecognized type\n");
      return;
    }
  }
  printf("\n");
}
