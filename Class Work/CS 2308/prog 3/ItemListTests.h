// include guard
#ifndef ITEM_LIST_TESTS_HEADER
#define ITEM_LIST_TESTS_HEADER

#include "ItemListClass.h"	// class definition (prototypes for methods)

// #define DEBUG
#define TEST_APPEND
#define TEST_INSERT
#define TEST_READ_FILE
#define TEST_INSERT_VAL
#define TEST_REMOVE_VAL

const int MAX_LIST_SIZE = 17;

void testAppend(ItemList &);
void testInsert(ItemList &);
void testReadFile(ItemList &);
void testInsertVal(ItemList &);
void testRemove(ItemList &);
void testBehead(ItemList &);
void testRemoveVal(ItemList &);

#endif
