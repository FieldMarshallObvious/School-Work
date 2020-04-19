
/*=====================================================================
 Program: IntList.cpp
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 4/20/20
 Description: A program that creates a linked list of integers
 Input:
 Output: (to the console)
         2 -> 4 -> 6 -> 8 -> 10
 Compilation instructions: These compilation instructions assume you are running this
                           program on a linux machine. Enter the command `make` into
                           the console. Then enter ./a.out. A list of these e
 Usage: 
 Modifications:
 Date Comment: 4/16/20
 ----------------------------------------------------
 ======================================================================*/

#include <cstdlib>
#include <iostream>

#include "IntList.h"

using namespace std;

/*=====================================================================
 Function: Constructor
 Description: Initiliazes values for each object
 Parameters:
 ======================================================================*/
IntList::IntList( )
{
    //Initialize new struct object
    ListNode *newNode = new ListNode;
    
    //Assign pointer to new struct
    head = newNode;
    
    //Assign values of new struct
    head->value = -1;

    head->next = NULL;
}

/*=====================================================================
 Function: Copy Constructor
 Description: Assigns values of the new object to the old one
 Parameters: IntList & List
 ======================================================================*/
IntList::IntList( const IntList &List )
{
    //Varaible declarations
    IntList *nodePtr = new IntList ( );
    IntList *nodePtrOther = new IntList( );
    ListNode *newNode = new ListNode;
    
    //Assign pointer to new struct
    head = newNode;
    
    //Assign values of new struct
    head->value = -1;
    
    head->next = NULL;
    
    //Assign nodePtr's to the begging
    //of their respective lists
    ( *nodePtr ).head = head;
    ( *nodePtrOther ).head = List.head;
    
    while ( ( *nodePtrOther ).head != NULL )
    {
        //Assign current node to node
        //from the other list
        ( *nodePtr ).head->value = ( *nodePtrOther ).head->value;
        
        
        //If this is the end of the list
        if (( *nodePtrOther ).head->next != NULL )
            //Create a new next node
            ( *nodePtr ).head->next = ( new IntList )->head;
        
        //Move nodes to their next value
        ( *nodePtr ).head = ( *nodePtr ).head->next;
        
        ( *nodePtrOther ).head = ( *nodePtrOther ).head->next;
    }
    
}

/*=====================================================================
 Function: Destructor
 Description: Deletes and sets all used pointers to NULL. To clean
              memory of all used addresses.
 Parameters:
 ======================================================================*/
IntList::~IntList( )
{
    //Variable declarations
    IntList *nodePtr = new IntList( );
    IntList *nextNode = new IntList( );
    
    //If the head does exist walk through it's list
    //and remove it
    if ( head != NULL )
    {
        //set the node to the begging
        //of the list
        ( *nodePtr ).head = head;
        
        //While the current node is not set to
        //NULL
        while ( ( *nodePtr ).head != NULL )
        {
            //Perserve the next node
            ( *nextNode ).head = ( *nodePtr ).head->next;
            
            //Delete the current node
            delete ( *nodePtr ).head;
            
            //Set the current node to the perserved next
            ( *nodePtr ).head = ( *nextNode ).head;
        }
        
    }
    
    //If head does not exist remove
    //the newly created nodePtr's
    else
    {
        delete ( *nodePtr ).head;
        delete ( *nextNode ).head;
    }
}

/*=====================================================================
 Function: appendNode
 Description: Adds a new node, with the given value, to the end of the
              linked list.
 Parameters: int val
 ======================================================================*/
void IntList::appendNode( int val )
{
    //Variable delcarations
    IntList *newNode;
    IntList *nodePtr;
    
    //Create new nodes
    newNode = new IntList( );
    nodePtr = new IntList( );
    
    //Set the new node to the inputted value
    ( *newNode ).head->value = val;
    
    if ( head == NULL || ( head->value == -1 && head->next == NULL ) )
    {
        head = ( *newNode ).head;
    }
    
    else
    {
        ( *nodePtr ).head = head;
        
        while ( ( *nodePtr ).head->next != NULL )
        {
            ( *nodePtr ).head = ( *nodePtr ).head->next;
        }
        
        ( *nodePtr ).head->next = ( *newNode ).head;
    }
}

/*=====================================================================
 Function: removeByval
 Description: Removes the item in the list that matches the passed
              value.
 Parameters: int val
 ======================================================================*/
void IntList::removeByVal( int val )
{
    //Variable declarations
    IntList *nodePtr = new IntList( );
    IntList *previousNode = new IntList( );
    
    //If there is no head initliazed return
    if ( !head )
        return;
    
    //If the head is value the function was
    //looking for delete
    if( head->value == val )
    {
        //Acquire the next node
        ( *nodePtr ).head = head->next;
        
        delete head;
        
        //Set the head to the next node
        head = ( *nodePtr ).head;
    }
    
    else
    {
        //Set the current node to the begging of the list
        ( *nodePtr ).head = head;
        
        //While the current node is not NULL, and it is
        //not equal to the value iterate through the list
        while ( ( *nodePtr ).head != NULL && ( *nodePtr ).head->value != val )
        {
            //Set the previous node to the current node
            ( *previousNode ).head = ( *nodePtr ).head;
            
            //Set the current node to the next node
            ( *nodePtr ).head = ( *nodePtr ).head->next;
        }
        
        //If the current node is the head of
        //the list
        if( ( * nodePtr ).head == head )
        {
            //set the head equal to the next item
            head = ( *nodePtr ).head->next;
            
            //delete the first item
            delete ( *nodePtr ).head;
            
            //Set the old pointer to NULL
            nodePtr = NULL;
            
            return;
        }
        
        //If the current node is not at the end of
        //the list
        if( ( * nodePtr ).head != NULL)
        {
            //Set the previous node next to the node after
            //the current node
            ( *previousNode ).head->next = ( *nodePtr ).head->next;

            //Delete the current node
            delete ( *nodePtr ).head;
            
            //Set the current node equal to null
            nodePtr = NULL;
        }
        //If the current node is at the end of
        //the list
        else
        {
            //Delete the previous node
            delete ( *previousNode ).head;
            
            //set the previous node to null
            previousNode = NULL;
        }
    }
}

/*=====================================================================
 Function: displayList
 Description: Displays all nodes in the list. Between each non-NULL
              node the function writes '->'.
 Parameters:
 ======================================================================*/
void IntList::displayList( )
{
    //Variable declarations
    IntList *nodePtr = new IntList( );
    
    //If there is no head intiliazed return
    if( !head )
        return;
    
    else
    {
        //Set the nodePtr to the begging of the list
        ( *nodePtr ).head = head;
        
        //While the current node is not set to NULL
        while ( ( *nodePtr ).head != NULL )
        {
            //Cout the current Node's value
            cout << ( *nodePtr ).head->value;
            
            //If the this is not the last item in the
            //list print a ->
            if( ( *nodePtr ).head->next != NULL )
                cout << " -> ";
            
            //Set the current node to the next node
            ( *nodePtr ).head = ( *nodePtr ).head->next;
        }
        
        //After the looped incremebt by a line
        cout << endl;
    }
}

/*=====================================================================
 Function: insertByPos
 Description: Creates a new node, with the passed value, in the posistion
              passed to the function.
 Parameters: int val, int pos
 ======================================================================*/
void IntList::insertByPos( int val, int pos )
{
    //Variable delcarations
    IntList *newNode;
    IntList *nodePtr;
    IntList *previousNode;
    int cntr = 0;
    
    //Create new nodes
    newNode = new IntList( );
    nodePtr = new IntList( );
    previousNode = new IntList( );
    
    //Set previous node to NULL
    ( *previousNode ).head = NULL;
    
    //Store newNode with the inputted value
    ( *newNode ).head->value = val;
    
    //If the head is not initialzed
    if ( !head )
    {
        //Set the head equal to the
        //new node
        head = ( *newNode ).head;
        
        //Set the head next to NULL
        ( *newNode ).head->next = NULL;
    }
    
    else
    {
        //Set the nodePtr to the the begging
        //of the list
        ( *nodePtr ).head = head;
        
        //set the previous node to NULL
        ( *previousNode ).head = NULL;
        
        //While the current node is not NULL, and
        //the counter is less than the passed posistion
        while ( ( *nodePtr ).head != NULL && cntr < (pos - 1) )
        {
            ( *previousNode ).head = ( *nodePtr ).head;
            ( *nodePtr ).head = ( *nodePtr ).head->next;
            cntr++;
        }
        
        //If the previousNode head is NULL
        if ( ( *previousNode ).head == NULL )
        {
            head = ( *newNode ).head;
            ( *newNode ).head->next = ( *nodePtr ).head;
        }
        
        //If the previous node is not NULL
        else
        {
            ( *previousNode ).head->next = ( *newNode ).head;
            ( *newNode ).head->next = ( *nodePtr ).head;
        }
    }
}

/*=====================================================================
 Function: removeByPos
 Description: Removes a node from the passed posistion.
 Parameters: int pos
 ======================================================================*/
void IntList::removeByPos( int pos )
{
    //Variable declarations
    IntList *nodePtr;
    IntList *previousNode;
    int cntr = 0;
    
    //Create new nodes
    nodePtr = new IntList( );
    previousNode = new IntList( );
    
    //If head is not intialized
    if ( !head )
    {
        ( *nodePtr ).head = head->next;
        delete head;
        head = ( *nodePtr ).head;
    }
    
    else
    {
        //Set the nodePtr to the begging of the list
        ( *nodePtr ).head = head;
        
        //Iterate through the list while the head is
        //not NULL, and the counter is less that
        //passed posistion
        while ( ( *nodePtr ).head != NULL && cntr <  ( pos - 1 ) )
        {
            //Set the previous node to the current node
            ( *previousNode ).head = ( *nodePtr ).head;
            
            //Set the current node to the next node
            ( *nodePtr ).head = ( *nodePtr ).head->next;
            cntr++;
        }
        
        //If the current node is at the begging of the list
        if( (* nodePtr).head == head )
        {
            head = ( *nodePtr ).head->next;
            delete ( *nodePtr ).head;
            
            nodePtr = NULL;
            return;
            
        }
        
        //If the current node is not at the end of
        //the list
        if( ( * nodePtr ).head != NULL && cntr == ( pos - 1 ) )
        {
            //Set the previous node next to the node after
            //the current node
            ( *previousNode ).head = ( *nodePtr ).head->next;
            
            //Delete the current node
            delete ( *nodePtr ).head;
            
            //Set the current node equal to null
            nodePtr = NULL;
        }
        //If the current node is at the end of
        //the list
        else if ( ( * nodePtr ).head == NULL && cntr == ( pos - 1 ) )
        {
            //Delete the previous node
            delete ( *previousNode ).head;
            
            //set the previous node to null
            previousNode = NULL;
        }
        
        else
        {
            return;
        }
    }
    
}

/*=====================================================================
 Function: search
 Description: Finds the first node that contains the passed value. Then
              the function returns the posistion of that value.
 Parameters: int val
 ======================================================================*/
int IntList::search( int val )
{
    //Variable declarations
    IntList *nodePtr = new IntList( );
    int cntr = 0;
    bool found = false;
    
    //If there is no head intiliazed return
    if( !head )
        return -1;
    
    else
    {
        //Set the nodePtr to the begging of the list
        ( *nodePtr ).head = head;
        
        //While the current node is not set to NULL
        while ( ( *nodePtr ).head != NULL && ( *nodePtr ).head->value != val )
        {
            //Set the current node to the next node
            ( *nodePtr ).head = ( *nodePtr ).head->next;
            
            cntr++;
            if ( ( *nodePtr ).head != NULL && ( *nodePtr ).head->value == val )
            {
                found = true;
            }
        }
        
        if ( found != true )
        {
            cntr = -1;
        }
    }
    
    return cntr;
}
