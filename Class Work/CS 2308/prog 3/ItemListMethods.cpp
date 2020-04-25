/*
  Name: ItemListArrMethods.cpp
  Author: Carl Gregory
  Date: 04/09/11
  Revised by: Ziliang Zong on 03/03/16

  Description: 
	Implements methods for class ItemList
	class ItemList definition is in ItemList.h

	Class methods are prototyped in ItemListMethods.h

*/

#include <cstdlib>
#include <iostream>

#include "ItemListClass.h"

//#define DEBUG

using namespace std;


/***************  Public  Methods ********************/

/*
	ItemList(arraySize : int)
	Constructor
	
	arraySize defaults to 10
	so this is the default constructor
	
	calls:     clearList()

	changes:
        listItem
		topItem
		nextAvailable
		currentItem
		maxSize
*/
ItemList::ItemList(int arraySize = 10)
{
    	// dynamically allocate the list array
    	listItem = new int[arraySize];
	maxSize = arraySize;
	// be sure to note that listItem[0] is undefined at this point

	// set all node links to indicate node available for insert
	clearList();

} // ItemList()

/*
	clearList() : void
	"Clears" list by "removing" all items:
        in truth, just resets all pointers to NULL
        (removes items by ignoring them)

	changes:
		topItem
		nextAvailable
		currentItem
		maxSize
*/
void ItemList::clearList()
{
	// set all node links to indicate node available for insert
	topItem = NULL;
	nextAvailable = listItem;
	currentItem = NULL;

} // clearList()


/*
	~ItemList()
	Destructor

	deletes the list array

*/
ItemList::~ItemList()
{
    delete [] listItem;
    listItem = NULL;
} // ItemList()


/*
	setCurrentValue(value : int) : bool
	changes value at currentItem to value1
	
	Steps are:
		1. if currentItem is not NULL
		   a. set value of *currentItem to value
	
	parameters: value: value to set : int

	calls:		none

	changes:	*currentItem

	returns:	true = successful change
				false = failed to change
*/
bool ItemList::setCurrentValue(int value)
{
    	bool returnValue = false;	// safest default is that change failed
     
	if (currentItem) // currentItem is not NULL
	{
        *currentItem = value;
        returnValue = true;
	}
	
	return returnValue;
} // setCurrentValue(value)


/*
	insertBeforeCurrentItem(value : int) : bool
	Inserts a new item "before" the current item;
	the inserted item becomes the current item after a successful insert,
	otherwise the current item is unchanged
    Steps are:
		1. if the list is empty (inserting first item)
		   a. set top and current pointers to the list address
		   b. set next available address
		   c. set current item to value
		2. otherwise, if there is room
		   a. move all values starting with the current item "down"
		   b. set current item to value
		   c. increment next available address
		3. otherwise, insert failed

	parameters: value: value to insert : int

	calls:		none

	changes:	currentItem becomes newly inserted item
				listItem[currentItem .. nextAvailable]
				nextAvailable

	returns:	true = successful insert
				false = failed to insert
*/
bool ItemList::insertBeforeCurrentItem(int value)
{
   	bool itWorked = false;	// safest default is insert failed
    	int* item = nextAvailable;
     
	if ( isEmpty() ) // this will be the first item
	{
	        // this "wakes up" all the list pointers
	        topItem = listItem;
	        currentItem = listItem;
	        nextAvailable = currentItem + 1;
	
	        *currentItem = value;
	
	        itWorked = true;
    	}
    	else if ( (nextAvailable - listItem) < maxSize ) // there is space available
	{
	        // move all values starting with currentItem "down"
	        for (item = nextAvailable; item > currentItem; --item)
	        {
	            *item = *(item - 1);
	        }
	        *currentItem = value;
	        ++nextAvailable;
	        
	        itWorked = true;
		} // there is space available
	else
	{
        	itWorked = false;
    	}
	return itWorked;
} // insertBeforeCurrentItem(value)


/*
	appendToList(value : int) : bool
	Inserts a new item in the next available (end-of-list) position;
	the inserted item becomes the current item after a successful insert,
	otherwise the current item is unchanged
    Steps are:
		1. if the list is empty (inserting first item)
		   a. set top and current pointers to the list address
		   b. set next available address
		   c. set current item to value
		2. otherwise, if there is room
		   a. set the current item address to the next available address
		   b. increment the next available address
		   c. set the new current item to value
		3. otherwise, insert failed

	parameters: value: value to insert : int

	calls:		none

	changes:	currentItem
				listItem[nextAvailable]
				nextAvailable

	returns:	true = successful insert
				false = failed to insert
*/
bool ItemList::appendToList(int value)
{
    	bool itWorked = false;	// safest default is insert failed

	if ( isEmpty() ) // this will be the first item
	{
	        // this "wakes up" all the list pointers
	        topItem = listItem;
	        currentItem = listItem;
	        nextAvailable = currentItem + 1;
	
	        *currentItem = value;
	
	        itWorked = true;
    	}
    	else if ( (nextAvailable - listItem) < maxSize ) // there is space available
	{
	        currentItem = nextAvailable;
	        ++nextAvailable;
	        *currentItem = value;
	
	        itWorked = true;
	} // there is space available
	else
	{
        	itWorked = false;
    	}
	return itWorked;
} // appendToList(int value)


/*
	removeCurrentItem() : bool
	removes the current item from the list
	the current item is the item after the removed item, the last item if the
	removed item was previously the last, and NULL if it was the only node
	Steps are:
		1. if the list is not empty
		   a. move all values starting with the current item "up"
		   b. move the next available address "up"

	parameters: none

	calls:		none

	changes:	nextAvailable
				currentItem

	returns:	true = successful remove
				false = failed to remove
*/
bool ItemList::removeCurrentItem()
{
    	bool itWorked = false;	// safest default is remove failed
    	int* item = currentItem;

    	if ( !isEmpty() ) // the list has at least 1 listItem
	{
	        // we "remove" by simply overwriting the values
	        for (item = currentItem; item < nextAvailable; ++item)
	        {
	            *item = *(item + 1);
	        }
	        itWorked = true;
	
	        // we "remove" the last item by simply ignoring it
	        --nextAvailable;
	        if (currentItem >= nextAvailable)
	        {
	            currentItem = nextAvailable - 1;
	        }
	        
	        // however, we now must check whether we have erased the whole list
	        if (nextAvailable <= topItem) // "<=" test is for safety
	        {
	            topItem = NULL;
	            currentItem = NULL;
	        }
	} // the list has at least 1 listItem
	else
	{
        	itWorked = false;
    	}

	return itWorked;
} // removeCurrentItem()

/*
    removeValue( value : int ) : void
    find the first litem intem containg the passed value
    removes the found value from the list
    ensures that the link between nodes is not broken
 
 
 changes:   listItem
            nextAvailable
            currentItem
 
 returns:
 */
void ItemList::removeValue(int value)
{
    
} // removeValue(value)


/*
	search(value : int) : bool
	finds the first list item containing the value value
	sets the found item to be the current item if successful,
	otherwise the current item is unchanged

	changes:	currentItem

	returns:	true  if value was found
				false if value not found
*/
bool ItemList::search(int value)
{
	bool foundIt = false;	// safest default is search failed
    	int* item = topItem;

    	if ( !isEmpty() ) // the list has at least 1 listItem
    	{
	    	item = topItem;
	        while ( (item < nextAvailable) && (!foundIt) )
	    	{
	                if (*item == value)
	               {
	               		foundIt = true; // this will stop the loop
	                	currentItem = item;
	               }
	    		++item;
	        } // while
    	} // the list has at least 1 listItem
	return foundIt;
} // search(value)

/*
	moveToNextItem() : bool
    make the next item the current item

	calls:     none

	changes:   currentItem

	returns:	true  if move was successful
				false otherwise
*/
bool ItemList::moveToNextItem()
{
    bool itWorked = false;	// safest default is remove failed
    
    // make sure there is a next item
    if ( (currentItem != NULL) && ((currentItem + 1) < nextAvailable) )
    {
        ++currentItem;
        itWorked = true;
    }
    return itWorked;
} // moveToNextItem()


/*
	moveToPreviousItem() : bool
    make the previous item the current item

	calls:     isEmpty()

	changes:   currentItem

	returns:	true  if move was successful
				false otherwise
*/
bool ItemList::moveToPreviousItem()
{
    bool itWorked = false;	// safest default is remove failed

    // make sure there is a previous item
    if ( (currentItem != NULL) && (currentItem > topItem) )
    {
        --currentItem;
        itWorked = true;
    }
    return itWorked;
} // moveToPreviousItem()


/*
	moveToTopItem() : bool
    make the top item the current item

	calls:     isEmpty()

	changes:   currentItem

	returns:	true  if move was successful
				false otherwise
*/
bool ItemList::moveToTopItem()
{
    bool itWorked = false;	// safest default is remove failed

    // make sure there is a top item
    if ( !isEmpty() )
    {
        currentItem = topItem;
        itWorked = true;
    }
    return itWorked;
} // moveToTopItem()


/*
	moveToBottomItem() : bool
    make the bottom item the current item

	calls:     isEmpty()

    changes:   currentItem

	returns:	true  if move was successful
				false otherwise
*/
bool ItemList::moveToBottomItem()
{
    bool itWorked = false;	// safest default is remove failed

    // make sure there is a bottom item
    if ( !isEmpty() )
    {
        currentItem = nextAvailable - 1;
        itWorked = true;
    }
    return itWorked;
} // moveToBottomItem()


/*
	getListLength() const : int

	changes:   none

	returns:   number of items in the list
*/
int ItemList::getListLength() const
{
    int listLength = 0;
    
    if ( isEmpty() )
    {
        listLength = 0;
    }
    else
    {
        listLength = nextAvailable - topItem;
    }
	return listLength;
} // getListLength()


/*
	displayAll() const : void
	displays all the items on the list, in order
	
	calls:		showlistItem()

	changes:	none

	returns:	the value of the last node in the list
*/
void ItemList::displayAll() const
{
    int* index;

    if ( !isEmpty() )
    {
    	for (index = topItem; index < nextAvailable; index++)
    	{
    		cout << "[" << *index << "] ";
        }
        cout << endl;
    }
} //displayAll()
