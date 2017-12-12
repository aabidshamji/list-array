/***********************************************************************
 * Homework: List arrays
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "listarray.h"


/* Allocate a new listarray with the specified initial array capacity
 * Precondition:
 *  capacity > 0
 * Postcondition:
 *  Return value is NULL if memory cannot be allocated
 */
listarray_t *
new (unsigned int capacity){

  assert(capacity > 0);

  listarray_t * listarray;
  listarray = (listarray_t *) malloc (sizeof (listarray_t));

  if (listarray == NULL) {
    perror("Unable to allocate additional memory\n");
    return NULL;
  }

  node_t * new_node;
  new_node = (node_t *) malloc (sizeof (node_t));

  if (new_node == NULL) {
    perror("Unable to allocate additional memory\n");
    return NULL;
  }

  data_t * arr;
  arr = (data_t *) malloc (capacity * sizeof (data_t));

  if (arr == NULL) {
    perror("Unable to allocate additional memory\n");
    return NULL;
  }

  new_node->array = arr;
  new_node->length = capacity;
  new_node->next = NULL;

  listarray->first = new_node;
  listarray->size = 0;


  return listarray;
}

/* Return the current size of the specified list */
unsigned int
size (listarray_t * list){
  return list->size;
}

/* Add the specified item to the end of the collection
 * Preconditions:
 *  list points to a valid listarray_t
 * Produces:
 *  true if the item was added
 * Postconditions:
 *  get (list,size(list)-1) == item
 */
bool
add (listarray_t * list, data_t item){

  node_t ** last = &list->first;

  unsigned int arr_size = size(list);

  data_t * location = get_ptr(list, arr_size, last);

  if (location == NULL) {
    node_t * new_node;
    new_node = (node_t *) malloc (sizeof (node_t));
    new_node->length = 2 * (*last)->length;
    data_t * new_arr;
    new_arr = (data_t *) malloc (new_node->length * sizeof(data_t));
    new_arr[0] = item;
    (*last)->next = new_node;
  }
  else {
    *location = item;
  }

  list->size++;
  return true;

}

/* Get the item at the specified index in list
 * Preconditions:
 *  list points to a valid listarray_t
 *  index < size(list)
 * Produces:
 *   item
 * Postcondition:
 *  list is unmodified
 *  item is the element at the specified position in list
 */
data_t
get (listarray_t * list, unsigned int index){
  assert(index <= size(list));

  node_t ** last = &list->first;

  data_t * value = get_ptr(list, index, last);

  return *value;


}

/* Replace the item at the specified index in list
 * Precondition:
 *  list points to a valid listarray_t
 *  index < size(list)
 * Produces:
 *  previous
 * Postcondition:
 *  get(list,index) = item
 *  previous = get(listbefore,index)
 */
data_t
set (listarray_t * list, unsigned int index, data_t item){

  node_t ** last = &list->first;

  data_t * value = get_ptr(list, index, last);

  data_t old_val =  *value;

  *value = item;

  return old_val;
}

/* Determine whether the list contains the specified item
 * Precondition:
 *  list points to a valid listarray_t
 * Postcondition:
 *  list is unmodified
 *  Returns true if there exists an index such that get(list,index)==item
 */
bool
contains (listarray_t * list, data_t item){
  unsigned int num_elements = list->size;
  unsigned int counter = 0;
  data_t curr;
  bool contains = false;

  while (counter<num_elements) {
    curr = get(list, counter);
    if (curr == item){
      contains = true;
    }
    counter++;
  }

  return contains;

}

/* Clear the contents of the list, releasing all memory
 * Precondition:
 *  list points to a valid listarray_t
 * Postcondition:
 *   all memory associated with list is freed
 *   pointer list can no longer be used */
void
clear (listarray_t * list){

  node_t * cur = list->first;
  node_t * cur_next;
  while(cur != NULL)
  {
    cur_next = cur->next;
    free(cur->array);
    free(cur);
    cur = cur_next;
  }

  free(list);
}

/* Get pointer to data at specified index
 * Precondition:
 *  index <= size(list) [Note: equality allowed for add() function]
 * Postcondition:
 *  returns address of data item or NULL
 *  if returns NULL and last is not NULL, changes last to point to last node
 * [PRIVATE METHOD] */
data_t *
get_ptr (listarray_t * list, unsigned int index, node_t ** last){
  assert(index <= size(list));

  node_t * curr = list->first;
  int previous_passed = 0;


  while (previous_passed+curr->length <= index){
    previous_passed += curr->length;
    curr = curr->next;
  }

  int rem = index - previous_passed;

  data_t * pointer = &curr->array[rem];

  if (pointer == NULL) {
    *last = curr;
    return NULL;
  }
  else {
    return pointer;
  }

}
