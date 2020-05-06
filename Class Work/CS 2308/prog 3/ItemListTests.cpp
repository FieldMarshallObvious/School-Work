/*
  Name: ItemListTests.cpp
  Author: Carl Gregory
  Date: 04/09/11
  Revised by: Ziliang Zong on 03/03/16

  Description: 
               Main Program for ItemList (array) class tests
               see ItemListClass.h for class description
*/

#include <cstdlib>
#include <iostream>

// class definition (prototypes for methods) header
//is placed in header file for this program

#include "ItemListTests.h"// contains named constants, including array size
		 	 // also #define "flags" to turn tests on and off

using namespace std;

int main(int argc, char *argv[])
{
    int myListSize;
    
    system("clear");    // clear the screen. This works in Linux.
    
    
    cout << "Please enter a maximum list size, ";
    cout << "(and don't make me process any devious values): ";
    cin >> myListSize;
    
	ItemList list(myListSize);

	cout << "Filling list and displaying after insert." << endl;
	cout << endl;

#ifdef TEST_APPEND
    cout << "THE TEST APPEND FUNCTION IS CALLED" << endl;
	testAppend(list);
	list.displayAll();
	testRemove(list);
	list.displayAll();
	testAppend(list);
	list.displayAll();
	testBehead(list);
	list.displayAll();
#endif
#ifdef TEST_INSERT
    cout << "THE TEST INSERT FUNCTION IS CALLED" << endl;
	testInsert(list);
	list.displayAll();
	testRemove(list);
	list.displayAll();
	testInsert(list);
	list.displayAll();
	testBehead(list);
	list.displayAll();
#endif
#ifdef TEST_READ_FILE
    cout << "THE READ FILE FUNCTION IS CALLED" << endl;
	testReadFile(list);
	list.displayAll();
	testRemove(list);
	list.displayAll();
	testReadFile(list);
	list.displayAll();
	testBehead(list);
	list.displayAll();
#endif
#ifdef TEST_INSERT_VAL
    cout << "THE INSERT VAL FUNCTION IS CALLED" << endl;
	testInsertVal(list);
	list.displayAll();
	testRemove(list);
	list.displayAll();
	testInsertVal(list);
	list.displayAll();
	testBehead(list);
	list.displayAll();
#endif
#ifdef TEST_REMOVE_VAL
    cout << "THE REMOVE VAL FUNCTION IS CALLED" << endl;
	testInsertVal(list);
	list.displayAll();
	testRemoveVal(list);
	list.displayAll();
	testAppend(list);
	list.displayAll();
	testRemoveVal(list);
	list.displayAll();
#endif
	
    cout << endl;
    cout << "End of main program:  " << endl << endl;
    return EXIT_SUCCESS;
} // main()

/*
	testAppend()
	tests the ItemList method that inserts at end of list
*/
void testAppend(ItemList &list)
{
	int i;			// counter for for() loops
	int sizeList;
	int maxListSize;
	int insertValue;
	bool success = false;
	
	cout << "Testing appendToList(v):" << endl;
	maxListSize = list.getMaxSize();
	cout << "maximum list size is " << maxListSize << endl;
    	cout << endl;
    
    	/* to test error checking, 
	we will try to insert 2 more than the maximum allowed 
	*/
	for (i = 0; i < maxListSize + 2; ++i)
	{
		insertValue = maxListSize - i;
		
		success = list.appendToList(insertValue);
		if (success)
		{
			list.displayAll();
        	}
		else
		{
			cout << "append " << insertValue << " failed" << endl;
        	}
	} // for (i = 0; i < maxListSize + 2; ++i)
} // testinsert()

/*
	testInsert()
	tests the ItemList method that inserts at top of list
*/
void testInsert(ItemList &list)
{
	int i;			// counter for for() loops
	int sizeList;
	int maxListSize;
	int insertValue;
	
	cout << "Testing insertBeforeCurrentItem(v):" << endl;
	maxListSize = list.getMaxSize();
	cout << "maximum list size is " << maxListSize << endl;
    	cout << endl;
    
       /* to test error checking,
       we will try to insert 2 more than the maximum allowed
       */
	for (i = 0; i < maxListSize + 2; ++i)
	{
		insertValue = maxListSize - i;    // descending insert values
		if (list.insertBeforeCurrentItem(insertValue))
		{
			list.displayAll();
		}
		else
		{
			cout << "Insert " << insertValue << " failed" << endl;
        }
	} // while (i < maxListSize)
} // testInsert()

/*
	testReadFile()
	tests the ItemList method that reads items from a file
*/
void testReadFile(ItemList &list)
{
    cout << "Testing readReadFile(v): " << endl;
    
    char inputFile[] = "numbers.txt";
    
    cout << "Array size before reading information: " << list.getListLength() << endl;
    
    list.readFile( inputFile );
    
    cout << "Array size after reading information: " << list.getListLength() << endl;
    
} // testReadFile()

/*
	testInsertVal()
	tests the ItemList method that inserts before node containing value
*/
void testInsertVal(ItemList &list)
{
	int i;			// counter for for() loops
	int sizeList;
	int maxListSize;
	int insertValue;
	bool success;

	cout << "Testing Insert(v, x):" << endl;
	maxListSize = list.getMaxSize() / 2;
	cout << "maximum list size is " << maxListSize << endl;
   	cout << endl;

    	// first fill the list half way
	for (i = 0; i < maxListSize; ++i)
	{
		insertValue = maxListSize - i;
		success = list.insertBeforeCurrentItem(insertValue);
		if (!success)
		{
			cout << "Insert " << insertValue << " failed" << endl;
        	}
	} 

	cout << endl;
	cout << "List to insert value into:" << endl;
	list.displayAll();
	
	// now try some inserts
	for (i = 0; i < maxListSize+3; ++i)
	{
		insertValue = maxListSize - i;
		success = false;
		if ( list.search(i) )
		{
            		success = list.insertBeforeCurrentItem(insertValue);
        	}
		if (success)
		{
			cout << "Insert " << insertValue;
			cout << " before " << i;
			cout << " succeeded" << endl;
		}
		else
		{
			cout << "Insert " << insertValue;
			cout << " before " << i;
			cout << " failed" << endl;
		}
		list.displayAll();
	}

} // testInsertVal()

/*
	testRemove()
	tests the ItemList method that removes a node from end of list
*/
void testRemove(ItemList &list)
{
	int i;			// counter for for() loops
	int sizeList;
	int maxListSize;
	
	cout << "Testing remove():" << endl;
	maxListSize = list.getMaxSize();
	cout << "maximum list size is " << maxListSize << endl;
    	cout << endl;

	for (i = 0; i < maxListSize + 3; ++i)
	{
		if (list.moveToBottomItem() && list.removeCurrentItem())
		{
			list.displayAll();
        	}
		else
		{
			cout << "Remove failed" << endl;
        	}
	} // while (i < maxListSize)
} // testRemove()

/*
	testRemoveVal()
	tests the ItemList method that removes the first node containing x
*/
void testRemoveVal(ItemList &list)
{
	int i;			// counter for for() loops
	int sizeList;
	int maxListSize;
	int searchValue;
	bool success;
	
	cout << "Testing remove(x):" << endl;
	maxListSize = list.getMaxSize();
	cout << "maximum list size is " << maxListSize << endl;
    	cout << endl;
    
	cout << "List to remove value from:" << endl;
	list.displayAll();
	// now try some removes
	for (i = 0; i < maxListSize+3; ++i)
	{
		searchValue = maxListSize - i;
		success = false;
        
        success = list.removeValue( searchValue );
        
		if (success)
		{
			cout << "Remove " << searchValue;
			cout << " succeeded" << endl;
		}
		else
		{
			cout << "Remove " << searchValue;
			cout << " failed" << endl;
		}
		list.displayAll();
	}
	
} // testRemoveVal()

/*
	testBehead()
	tests the ItemList method that removes from beginning of list
*/
void testBehead(ItemList &list)
{
	int i;			// counter for for() loops
	int sizeList;
	int maxListSize;
	
	cout << "Testing behead():" << endl;
	maxListSize = list.getMaxSize();
	cout << "maximum list size is " << maxListSize << endl;
    	cout << endl;

	for (i = 0; i < maxListSize + 3; ++i)
	{
		if (list.moveToTopItem() && list.removeCurrentItem())
		{
			list.displayAll();
        }
		else
		{
			cout << "Behead failed" << endl;
        }
	} // while (i < maxListSize)
} // testBehead()
