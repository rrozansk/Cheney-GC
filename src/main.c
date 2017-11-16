/******************************************************************************
 * FILE:    main.c                                                            *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 10/31/17                                                          *
 * EDITED:  11/16/17                                                          *
 * INFO:    An interactive tool to dynamically call the API's exposed by the  *
 *          interface located at cheney.h in a safe way.                      *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 *   I N C L U D E S                                                          *
 *                                                                            *
 ******************************************************************************/
#include <cheney.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/******************************************************************************
 *                                                                            *
 *   M A C R O S                                                              *
 *                                                                            *
 ******************************************************************************/
#define PROMPT 0 // 1 for yes; 0 for no

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N S                                                        *
 *                                                                            *
 ******************************************************************************/
char readBool(int prompt) {
  char c, p;
  char buffer[80];
  for(;;) {
    fprintf(stdout, "choice (y/n): ");
    if(!fgets(buffer, 80, stdin) ||
       !sscanf(buffer, "%c\n", &c) ||
         !(c == 'y' || c == 'n')) {
      fprintf(stdout, "invalid input\n");
      continue;
    }
    if(!prompt) { return c; }
    for(;;) {
      fprintf(stdout, "choosen: %c, sure? (y/n) ", c);
      if(!fgets(buffer, 80, stdin) ||
         !sscanf(buffer, "%c\n", &p) ||
         !(p == 'y' || p == 'n')) {
        fprintf(stdout, "invalid input\n");
        continue;
      }
      if(p == 'y') { return c; }
      if(p == 'n') { break; }
    }
  }
}

unsigned long readULong(unsigned long lo, unsigned long hi, char prompt) {
  unsigned long choice;
  char c;
  char buffer[80];
  for(;;) {
    fprintf(stdout, "choice (%lu-%lu): ", lo, hi);
    if(!fgets(buffer, 80, stdin) ||
       !sscanf(buffer, "%lu\n", &choice) ||
       choice < lo || choice > hi) {
      fprintf(stdout, "invalid input\n");
      continue;
    }
    if(!prompt) { return choice; }
    for(;;) {
      fprintf(stdout, "choosen: %lu, sure? (y/n) ", choice);
      if(!fgets(buffer, 80, stdin) ||
         !sscanf(buffer, "%c\n", &c) ||
         !(c == 'y' || c == 'n')) {
        fprintf(stdout, "invalid input\n");
        continue;
      }
      if(c == 'y') { return choice; }
      if(c == 'n') { break; }
    }
  }
}

int main(int argc, char *argv[]) {
  fprintf(stdout, "Interactive Cheney Garbage Collector\n"
                  "v2.0\n"
                  "Ryan Rozanski\n");

  if(argc != 1) {
    fprintf(stderr, "unexpected arguments to program\nexiting...\n");
    exit(EXIT_FAILURE);
  }

  heap_t *heap;
  clock_t t1, t2;

  // void *root;
  // void *ref1, *ref2; // atom or cell

  for(srand(time(NULL)), heap = NULL;;) {
    fprintf(stdout, "\n"
                    "What would you like to do?\n"
                    "0)  Make Heap\n"
                    "1)  Free Heap\n"
                    "2)  Set Dynamic Heap\n"
                    "3)  Get Dynamic Heap\n"
                    "4)  Set Heap Expander\n"
                    "5)  Get Heap Expander\n"
                    "6)  Resize Heap\n"
                    "7)  Set Heap Root\n"
                    "8)  Get Heap Root\n"
                    "9)  Collect Heap\n"
                    "10) Show Heap Size\n"
                    "11) Show Heap Semi Size\n"
                    "12) Show Heap Used\n"
                    "13) Show Heap Left\n"
                    "14) Cons\n"
                    "15) Cell\n"
                    "16) Car\n"
                    "17) Cdr\n"
                    "18) Set Car\n"
                    "19) Set Cdr\n"
                    "20) Cell?\n"
                    "21) Atom?\n"
                    "22) Exit\n"
                    "\n");
    switch(readULong(0, 22, PROMPT)) {
      case 0: // Make Heap
        if(heap){ fprintf(stdout, "failure; driver not capable of allocating multiple heaps\n"); }
        else {
          fprintf(stdout, "how large would you like to make the heap? (in cells)\n");
          if(!(heap = make_heap(readULong(0, ULONG_MAX, PROMPT)))) {
            fprintf(stderr, "heap allocation unsuccessful, exiting...\n");
            exit(EXIT_FAILURE);
          }
          fprintf(stdout, "heap allocation successfull\n");
        }
        break;
      case 1: // Free Heap
        if(heap) {
          free_heap(&heap);
          fprintf(stdout, "successfully free'd heap\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 2: // Set Dynamic Heap
        if(heap) {
          fprintf(stdout, "expand heap when a collection cannot recover memory?\n");
          set_dynamic(heap, readBool(PROMPT) == 'y');
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 3: // Get Dynamic Heap
        if(heap) {
          fprintf(stdout, "dynamic heap expansion status: %s\n",
            get_dynamic(heap) ? "ON" : "OFF");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 4: // Set Heap Expander TODO
        if(heap) {
          // set_expaner(heap, --);
          // a func to interp user math expr?
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 5: // Get Heap Expander TODO
        if(heap) {
          // expander = get_expaner(heap);
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 6: // Resize Heap
        if(heap) {
          fprintf(stdout, "new heap size? (in cells)\n");
          if(!resize(heap, readULong(0, ULONG_MAX, PROMPT))) {
            fprintf(stdout, "failure; unable to resize heap to requested size\n");
          }
          else { fprintf(stdout, "successfully resized heap\n"); }
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 7: // Set Heap Root TODO
        if(heap) {
          // set_root(heap, root);
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 8: // Get Heap Root TODO
        if(heap) {
          // root = get_root(heap);
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 9: // Collect Heap
        if(heap) {
          fprintf(stdout, "starting collection...\n");
          t1 = clock();
          collect(heap);
          t2 = clock();
          fprintf(stdout, "finished collecting in: %fs\n",
            (double)(t2 - t1) / CLOCKS_PER_SEC);
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 10: // Show Heap Size
        if(heap) { fprintf(stdout, "heap cell size: %lu\n", heap_size(heap)); }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 11: // Show Heap Semi Size
        if(heap) { fprintf(stdout, "semi cell size: %lu\n", semi_size(heap)); }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 12: // Show Heap Used
        if(heap) { fprintf(stdout, "used cells: %lu\n", semi_used(heap)); }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 13: // Show Heap Left
        if(heap) { fprintf(stdout, "free cells: %lu\n", semi_left(heap)); }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 14: // Cons TODO
        if(heap) {
          //cell_t *cons(heap_t *heap, void *car, void *cdr);
          // possibly alloc atoms
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 15: // Cell TODO
        if(heap) {
          // cell_t *cell(heap_t *heap);
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 16: // Car TODO
        if(heap) {
          // void *car(cell_t *cell);
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 17: // Cdr TODO
        if(heap) {
          // void *cdr(cell_t *cell);
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 18: // Set Car TODO
        if(heap) {
          // void set_car(cell_t *cell, void *value);
          // possibly alloc atom
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 19: // Set Cdr TODO
        if(heap) {
          // void set_cdr(cell_t *cell, void *value);
          // possibly alloc atom
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 20: // Cell? TODO
        if(heap) {
          // char is_cell(void **value);
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 21: // Atom? TODO
        if(heap) {
          // char is_atom(void **value);
          fprintf(stdout, "failure; option currently under development\n");
        }
        else { fprintf(stdout, "failure; no heap currently allocated\n"); }
        break;
      case 22: // Exit
        fprintf(stdout, "exiting...\n\n");
        exit(EXIT_SUCCESS);
      default: // Panic
        fprintf(stdout, "panic! unknown bad state\nexiting...\n\n");
        exit(EXIT_FAILURE);
    }
  }
}
