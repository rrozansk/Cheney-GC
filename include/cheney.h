/******************************************************************************
 * FILE:    cheney.h                                                          *
 * AUTHOR:  Ryan Rozanski                                                     *
 * CREATED: 1/14/17                                                           *
 * EDITED:  11/11/17                                                          *
 * INFO:    A library which encapsulates a cheney style garbage collected     *
 *          heap into a well defined structure and exposes its abilities      *
 *          through a simple to use API. The interface allows creation and    *
 *          destruction of an arbitrary number of heaps. Additionally, it     *
 *          exposes the heaps ability to grow dynamically and the capability  *
 *          to switch on/off this attribute at will. Note, that a heap will   *
 *          only grow dynamically when a collection, triggered as a result of *
 *          a full semi-space, fails to free any memory. The default          *
 *          expansion behavior attempts to double the size of the heap, but   *
 *          the library permits custom implementations to be set, allowing    *
 *          any expanding growth method desired. Furthermore, the heap may be *
 *          resized manually at any point in time which also permits making   *
 *          it smaller if possible. Although collection happens automatically *
 *          when needed, it may also be triggered manually whenever wanted.   *
 *          However, to preserve any allocated object(s) they must be         *
 *          reachable from a single root object. When created the heaps root  *
 *          is set to NULL since no objects have been allocated yet. As a     *
 *          result of this, the user is required to explicitly set the root,  *
 *          and getter/setter methods are provided to make managing it easy.  *
 *          The heap only allows allocation of a single object named a cons   *
 *          cell. Cells are capable of holding two references and the library *
 *          allows querying and updating the fields individually, as well as  *
 *          creating cells initialized with data or not. Cons cells can be    *
 *          used to implement more complex data structures such as stacks,    *
 *          queues, lists, and trees among others. It is also possible to     *
 *          query the heap about its current usage of the semi space and      *
 *          overall size so it can be known how many allocation before a      *
 *          collection will be triggered as well as the resulting size of the *
 *          heap after a dynamic expansion or manaul resize. Lastly, it is    *
 *          critically important to note that for the collector to properly   *
 *          differentiate between cons cells and all other data types, termed *
 *          atomic, it imposes a single rule that references to the atomic    *
 *          data must have the lowest bit set.                                *
 *                                                                            *
 ******************************************************************************/

#ifndef CHENEY_GC_STRUCT_DEFS
#define CHENEY_GC_STRUCT_DEFS

/******************************************************************************
 *                                                                            *
 *   T Y P E S                                                                *
 *                                                                            *
 ******************************************************************************/
typedef struct heap heap_t; /* Cheney style garbage collected heap */

typedef struct cell cell_t; /* Cons cells */

/******************************************************************************
 *                                                                            *
 *   F U N C T I O N   P R O T O T Y P E S                                    *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 * PURPOSE: Instantiate a new heap with an size in cons cells.                *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cells    The number of cells to instantiate the heap with. Odd numbers     *
 *          will be reduced by one.                                           *
 *                                                                            *
 * RETURNS: A pointer to a newly allocated heap or NULL if allocation fails.  *
 *                                                                            *
 ******************************************************************************/
heap_t *make_heap(unsigned long cells);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Free any heap created with the constructor. A pointer to the      *
 *          variable which holds the reference to the heap is taken to help   *
 *          minimize dangling pointers and potential crashes by setting it to *
 *          NULL when completed.                                              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     Address of the variable holding the heap.                         *
 *                                                                            *
 * RETURNS: void                                                              *
 *                                                                            *
 ******************************************************************************/
void free_heap(heap_t **heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Update an arbitrary heap to (dis)allow dynamic expansion. If set  *
 *          to allow dynamic expansion, it will only happen if a collection,  *
 *          which is the result of a full semi space, fails to free any       *
 *          allocated memory.                                                 *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to update.                                               *
 * dynamic  1 if allowed to dynamically resize, 0 otherwise.                  *
 *                                                                            *
 * RETURNS: void                                                              *
 *                                                                            *
 ******************************************************************************/
void set_dynamic(heap_t *heap, int dynamic);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query an arbitrary heap if it can dynamically expand or not.      *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to query.                                                *
 *                                                                            *
 * RETURNS: 1 if the heap can dynamically expand, 0 otherwise.                *
 *                                                                            *
 ******************************************************************************/
int get_dynamic(heap_t *heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Dictate how the heap dynamically expands by setting a custom      *
 *          expander. Note that this only affects heaps created with the      *
 *          dynamic option set.                                               *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     Which heap to use.                                                *
 * expander A function pointer to the custom expander.                        *
 *                                                                            *
 * RETURNS: void                                                              *
 *                                                                            *
 ******************************************************************************/
void set_expander(heap_t *heap, unsigned long (*expander)(unsigned long));

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query an arbitrary heap about its dynamic expansion policy.       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The given heap to query.                                          *
 *                                                                            *
 * RETURNS: The function pointer to the custom set expander or NULL if the    *
 *          default expander is being used.                                   *
 *                                                                            *
 ******************************************************************************/
unsigned long (*get_expander(heap_t *heap))(unsigned long);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Attempt manual resizing of the heap, either bigger or smaller, so *
 *          that each semi space is half of the number specified.             *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The given heap to attempt resizing.                               *
 * cells    The new size of the heap space in cells.                          *
 *                                                                            *
 * RETURNS: 1 if successful, 0 otherwise.                                     *
 *                                                                            *
 ******************************************************************************/
int resize(heap_t *heap, unsigned long cells);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Set the root of reachable objects. When a collection is triggered *
 *          all objects which are reachable from this single object will be   *
 *          safe from the garbage collection process.                         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to set the root on.                                      *
 * root     The root to set.                                                  *
 *                                                                            *
 * RETURNS: void                                                              *
 *                                                                            *
 ******************************************************************************/
void set_root(heap_t *heap, void *root);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query an arbitrary heap for it root.                              *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to query.                                                *
 *                                                                            *
 * RETURNS: The heaps root object or NULL if not set.                         *
 *                                                                            *
 ******************************************************************************/
void *get_root(heap_t *heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Trigger an arbitrary collection at any point in time which will   *
 *          free any unreferenced cons cells not reachable from the root as   *
 *          well as compacting all retained cells into the new semi space.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to trigger a collection on.                              *
 *                                                                            *
 * RETURNS: void                                                              *
 *                                                                            *
 ******************************************************************************/
void collect(heap_t *heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query an arbitrary heap about its size in cells.                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to query.                                                *
 *                                                                            *
 * RETURNS: The number of cells the entire heap could theoretically hold.     *
 *                                                                            *
 ******************************************************************************/
unsigned long heap_size(heap_t *heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query an arbitrary heap about its semi space size in cells.       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to query.                                                *
 *                                                                            *
 * RETURNS: The number of cells the heap can actually hold.                   *
 *                                                                            *
 ******************************************************************************/
unsigned long semi_size(heap_t *heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query an arbitrary heap about how many cells are allocated.       *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to query.                                                *
 *                                                                            *
 * RETURNS: The number of currently allocated cells in the heap.              *
 *                                                                            *
 ******************************************************************************/
unsigned long semi_used(heap_t *heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query an arbitrary heap about how many cells can be allocated     *
 *          before another garbage collection is triggered.                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap to query.                                                *
 *                                                                            *
 * RETURNS: The number of cells which can be allocated from the heap.         *
 *                                                                            *
 ******************************************************************************/
unsigned long semi_left(heap_t *heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Allocate a new cons cell with both fields initialized with the    *
 *          given contents.                                                   *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap in which to attempt an allocation from.                  *
 * car      the contents to store in the first field of the cell.             *
 * cdr      the contents to store in the second field of the cell.            *
 *                                                                            *
 * RETURNS: Newly allocated cons cell initialized with the given contents or  *
 *          NULL if allocation fails.                                         *
 *                                                                            *
 ******************************************************************************/
cell_t *cons(heap_t *heap, void *car, void *cdr);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Allocate a new cons cell with both fields initialized to NULL.    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * heap     The heap in which to attempt an allocation from.                  *
 *                                                                            *
 * RETURNS: Newly allocated cons cell or NULL if allocation fails.            *
 *                                                                            *
 ******************************************************************************/
cell_t *cell(heap_t *heap);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query a cons cell about the contents of its first field.          *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cell     The cons cell in question.                                        *
 *                                                                            *
 * RETURNS: The contents of the cells first field.                            *
 *                                                                            *
 ******************************************************************************/
void *car(cell_t *cell);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query a cons cell about the contents of its second field.         *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cell     The cons cell in question.                                        *
 *                                                                            *
 * RETURNS: The contents of the cells second field.                           *
 *                                                                            *
 ******************************************************************************/
void *cdr(cell_t *cell);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Update the contents of the cells first field.                     *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cell     The cons cell to update.                                          *
 * value    The new value to update the cells field with.                     *
 *                                                                            *
 * RETURNS: void                                                              *
 *                                                                            *
 ******************************************************************************/
void set_car(cell_t *cell, void *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Update the contents of the cells seoncd field.                    *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * cell     The cons cell to update.                                          *
 * value    The new value to update the cells field with.                     *
 *                                                                            *
 * RETURNS: void                                                              *
 *                                                                            *
 ******************************************************************************/
void set_cdr(cell_t *cell, void *value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query if a given pointer represents atomic data.                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * value    The pointer to test.                                              *
 *                                                                            *
 * RETURNS: 1 if atomic or NULL, 0 otherwise.                                 *
 *                                                                            *
 ******************************************************************************/
char is_atom(void **value);

/******************************************************************************
 *                                                                            *
 * PURPOSE: Query if a given pointer represents a cons cell.                  *
 *                                                                            *
 * ARGUMENT DESCRIPTION                                                       *
 * -------- -----------                                                       *
 * value    The pointer to test.                                              *
 *                                                                            *
 * RETURNS: 1 if cons cell, 0 otherwise.                                      *
 *                                                                            *
 ******************************************************************************/
char is_cell(void **value);

#endif
