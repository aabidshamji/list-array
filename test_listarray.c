/***********************************************************************
 * Homework: List arrays
 ***********************************************************************/

#include <stdbool.h>
#include <stdio.h>

#include "listarray.h"

#define TEST(EXP,RESULT) if (EXP != RESULT) { ++errors; printf ("  Error for: %s\n", #EXP);}

/* Test collection example */
void
testExample (void)
{
  printf("--EXAMPLE TEST--\n");

  int errors = 0;

  listarray_t * list = new (5);

  TEST( size (list),   0 );   // list is empty
  TEST( add (list,42), true); // added item
  TEST( size (list),   1 );   // list is appropriate size
  TEST( get (list,0),  42);   // check item was added / indexable

  clear(list);
  printf ("Done: errors = %d\n", errors);
} // testExample


/* Test all methods for a single node (no expansions) */
void
testBasic (void)
{
  printf("--BASIC TESTS--\n");

  const unsigned int CAPACITY = 10;
  int errors = 0;

  listarray_t * list = new (CAPACITY);

  TEST( size(list), 0 );        // initial list is empty

  int i; // index for all loops

  /* Test add (successful), size (incremented), and get (new item) */
  for (i=0 ; i<CAPACITY ; i++) {
    TEST( add (list,i), true);  // added item i
    TEST( size (list),  i+1 );  // list is appropriate size
    TEST( get (list,i), i);     // check index i is item i
  }

  /* Test contains (true and false) at all locations*/
  for (i=0 ; i< 2*CAPACITY ; i++) {
    TEST( contains (list,i), i<CAPACITY); // list contains item
  }

  /* Test set (return), size (same), and get (new value) */
  for ( i=0 ; i<CAPACITY ; i++) {
    TEST( set (list, i, i + CAPACITY), i);
    TEST( size (list), CAPACITY ) ;
    TEST( get (list,i), i + CAPACITY);
  }

  clear (list); // should run without memory errors

  printf ("Done: errors = %d\n", errors);
} // testBasic

void
test_size (void) {
  printf("--TEST SIZE--\n");

  const unsigned int CAPACITY = 2;
  int errors = 0;

  listarray_t * list = new (CAPACITY);

  /* Testing over two nodes for increasing size*/
  for (int i=0 ; i< CAPACITY ; i++) {
    TEST( add (list,i), true); // list contains item
    TEST( size(list), i+1);
  }

  clear (list); // should run without memory errors

  printf ("Done: errors = %d\n", errors);

}

void
test_add (void) {
  printf("--TEST ADD--\n");

  const unsigned int CAPACITY = 10;
  int errors = 0;

  listarray_t * list = new (CAPACITY);

  /* Testing over two nodes for increasing size*/
  for (int i=0 ; i< CAPACITY ; i++) {
    TEST( add (list,i), true); // list contains item
    TEST( get (list, size(list)-1), i); // tests if the element has been added at the correct node
  }

  clear (list); // should run without memory errors

  printf ("Done: errors = %d\n", errors);

}

void
test_get (void) {
  printf("--TEST GET and SET--\n");

  const unsigned int CAPACITY = 10;
  int errors = 0;

  listarray_t * list = new (CAPACITY);

  /* Testing over two nodes*/
  for (int i=0 ; i< CAPACITY ; i++) {
    TEST( add (list,0), true); // setting the elements in the list to 0
  }

  /* sets some of the edge and middle values to 1 and checks in set return the
    preivous values which should all be 0
    */
  TEST ( set (list, 0, 1), 0);
  TEST ( set (list, CAPACITY-1, 1), 0);

  TEST ( get (list, 0), 1);
  TEST ( get (list, CAPACITY-1), 1);


  clear (list); // should run without memory errors

  printf ("Done: errors = %d\n", errors);

}


void
test_contains (void) {
  printf("--TEST CONTAINS--\n");

  const unsigned int CAPACITY = 10;
  int errors = 0;

  listarray_t * list = new (CAPACITY);

  /* Testing over two nodes for increasing size*/
  for (int i=0 ; i< 2*CAPACITY ; i++) {
    TEST( add (list,i), true); // list contains item
  }

  // checks if all the ints enterned are within the list
  for (int i = 0; i < list->size; i++) {
    TEST (contains (list, i), true);
  }

  // checks that some larger values are not within the list
  for (int i = 2; i < (list->size)*2; i++) {
    TEST (contains (list, i), false);
  }

  // checks that some smaller values are not within the list
  for (int i = 2; i < 0; i++) {
    TEST (contains (list, i), false);
  }

  clear (list); // should run without memory errors

  printf ("Done: errors = %d\n", errors);

}


/* Driver program for test suite */
int
main (void)
{
  testExample();
  testBasic();

  test_size();
  test_add();

  test_get();

  return 0;
  // Add more test collections here
} // main
