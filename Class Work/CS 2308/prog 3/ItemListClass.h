// include guard
#ifndef ITEM_LIST_CLASS
#define ITEM_LIST_CLASS

/*
  Name: ItemListClass.h
  Author: Carl Gregory
  Date: 04/09/11
  Revised by: Ziliang Zong on 03/03/16

  Description:
  This is a class for lists of items, in this case, integers
 		 The list is implemented with an array (25/11/11 10:36)
		 It has mutator methods to insert, remove, traverse, search, and sort
		 It can support building stacks and queues:
                [note on implementation: "circular" lists, which are very
                 useful when implementing stacks and queues directly with
                 arrays, are not implemented in this more general class of
                 objects which perform array-like functions for more than
                 stack and queue operations]

  Discussion:
  A concept of a "list of items" corresponds to ordinary occurences of:
        to-do lists, grocery lists, membership lists, and so forth
  
  To help distinguish the list from the pure array that implements it:
        "typical" array-subscript notation is avoided
            replaced with pointer operations
        terminology is "neutralized":
            instead of "first" and "last" "elements" of an "array"
            there are "top" and "bottom" "items" of a "list"
            
  Some operations on a list are shared with those we associate with arrays:
        Data are stored sequentially, making lists and arrays "linear"
          (as opposed to, say, family trees or organizational hierarchies)
        Items in these lists are all the same type
        The items can be searched and ordered (sorted)
        Lists are "traversed" (inspected item-by-item) in a "direction" from
          one point to another (usually, top to bottom or bottom to top);
          - this is usually done to either search or output (print, display)
            the list
          
  Some operations on a list are not the typical set we associate with arrays:
        - Elements of an array are typically assigned and changed
        - Items in a list are typically inserted or deleted, often rearranging
          the list in the process

  For the list itself, we have three attributes:  type, length, and size:
        size is not the number of items on the list;
            it is the MAXIMUM number of items we are able to keep on the list
        length is the number of items on the list at the moment
        type is the kind of elements kept in the list:
            - in a grocery list, the names of food items ("strings")
            - in our example, simply counting numbers (integers)

  For each item on a list, we have two attributes:  value and position
        value is simply the data of the item's type stored in the item
        position is somewhat more complicated in a computer implementation:
            for a grocery list, we can think of items as "first", "fourth"
              or "last" on the list
            this concept is familiar to array representation:
              items are numbered and represented as indices, e.g., listItem[3]
            in this implementation, using pointer notation and arithmetic,
              items are located by their addresses
            the name of the list is a pointer to the first element of the list;
              - like an array, it is the "address" of the list
              - the "top" of the list (in other systems, the "head") is also the
                address of the first item; however, it is set to NULL when the
                list is empty
              - the "next available" item is the item after the "bottom" item
                (which, in other systems, is referred to as the "end" or "tail);
                it is useful to keep this address and compute the address of
                the "bottom" item; it is equal to the name of the list when the
                list is empty
            we also keep track of a "current" item on the list
              - currentItem is the address of the list item currently being
                inspected, for whatever reason

  The public interface for class ItemList is both sparse and tight; it is
    completely centered around the current item:
        Calling programs are given direct access to ONLY the current item,
          - all searches move the current address, unless they fail
          - only the value at the current address may be set or retrieved
          - all inserts are before or after the item at the current address
            and the inserted item becomes the current item
          - only the current item may be removed:
                the calling program must position itself at the item
                - it may use class ItemList movement methods to do so
                - this includes searching for a value to remove
                - the item before the removed item becomes the current item,
                  unless it was the top item, in which case the new top item
                  becomes the current item
        Movement from Top to Bottom is not outwardly numeric;
          - Top and Bottom are not identified as being "larger" or "smaller"
          - movement toward the Bottom is by moveToNextItem()
          - movement toward the Top is by moveToPreviousItem()
        The following information may be retrieved about the list:
            the length and maximum size of the list
            whether the list is full or empty
            whether the current item is at the Top or Bottom
            the value of the current item
            

  The UML description of class ItemList is
 ________________________
 | ItemList
 |-----------------------
 | - listItem : int*
 | - topItem : int*
 | - nextAvailable : int*
 | - currentItem : int*
 | - maxSize : int
 |----------------------------
 | - showlistItem(item : int*) const : void
 |
 | - binarySearch( value : int ) : void
 |
 | + ItemList(arraySize : int)
 | + ~ItemList()
 |
 | + setCurrentValue(value : int) : bool
 |
 | + insertBeforeCurrentItem(value : int) : bool
 | + appendToList(value : int) : bool
 |
 | + selectionSort() : void
 | + binarySearch( value : int ) : int
 |
 | + removeCurrentItem() : bool
 | + removeValue( value : int ) : bool
 | + clearList() : void
 |
 | + search(value : int) : bool
 | + moveToNextItem() : bool
 | + moveToPreviousItem() : bool
 | + moveToTopItem() : bool
 | + moveToBottomItem() : bool
 |
 | + getListLength() const : int
 | + getMaxSize() const : int
 |
 | + readFile( input_file : string ) : void
 |
 | + isEmpty() : bool
 |
 | + atTop() : bool
 | + atBottom() : bool
 |
 | + getCurrentValue() const : int
 |
 | + displayAll() const : void
  ----------------------------
  
  Methods are defined in ItemListMethods.cpp

*/
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class ItemList
{
	private:
		// Minimum set of private variables
		// note: these are INDICES, not values
		int* listItem;         // list of items (in this case, integers)

		// note: these are INDICES, not values
		int* topItem;         // index of first assigned listItem
		int* nextAvailable;   // index of listItem after the last assigned item
		int* currentItem;     // everything is done in relation to this item
		int maxSize;          // set to size of listItem array in Constructor
    
        void bubbleSort(); // Orders the array from lowest to largests
		
	public:
		
		// Method prototypes
		// constructor and destructor
		ItemList(int arraySize);
		~ItemList();
		
        /* Mutator methods */
		bool setCurrentValue(int value);  // false if currentItem is NULL

		bool insertBeforeCurrentItem(int value);  // topItem if currentItem is NULL
		bool appendToList(int value);  // nextAvailable if currentItem is NULL
    
        void selectionSort();
        int binarySearch();

		bool removeCurrentItem();     // false if current is NULL
        bool removeValue(int value);
		void clearList( ); // "removes" all list items (resets all pointers)

		bool search(int value); // finds first listItem containing value

		bool moveToNextItem(); // moves current item to the next item
		bool moveToPreviousItem(); // moves current item to the previous item
		bool moveToTopItem(); // moves current item to top item
		bool moveToBottomItem(); // moves current item to tail item

        /*Accessor methods */
		int getListLength() const;    // number of currently assigned listItems
		int getMaxSize() const { return maxSize; } //Gets max size of the array
    
        void readFile( char* input_file ); //reads numbers from a file

		bool isEmpty() const {return (topItem == NULL); } //determines if the array is empty

        bool atTop()    const {return (currentItem == topItem); } //returns if at top
		bool atBottom() const {return (currentItem == (nextAvailable - 1)); } //returns if at bottom

        int getCurrentValue() const {return *currentItem; } // returns the value of the current item
		
		void displayAll() const;		// displays all listItems in order

}; // class ItemList

#endif
