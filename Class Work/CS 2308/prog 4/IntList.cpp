
/*=====================================================================
 Program:
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 4/20/20
 Description:
 Input:
 Output:
 Compilation instructions:
 Usage:
 Modifications:
 Date Comment: 4/16/20
 ----------------------------------------------------
 ======================================================================*/

#include <cstdlib>
#include <iostream>

#include "IntList.h"

using namespace std;

//Global Variables


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
    IntList *nodePtr = new IntList();
    IntList *nodePtrOther = new IntList();
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
    cout << "in destructer" << endl;
    IntList *nodePtr = new IntList();
    IntList *nextNode = new IntList();
    
    cout << (head != NULL) << endl;
    
    if ( head != NULL )
    {
        ( *nodePtr ).head = head;
        cout << "Assign head " << endl;
        
        while ( ( *nodePtr ).head != NULL )
        {
            cout << "in while loop" << endl;
            cout << "the null status of the next node is " << (( *nodePtr ).head->next == NULL ) << endl;
            ( *nextNode ).head = ( *nodePtr ).head->next;
            
            cout << "set next node " << endl;
            
            delete ( *nodePtr ).head;
            
            ( *nodePtr ).head = ( *nextNode ).head;
        }
        
    }
    
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
    newNode = new IntList();
    nodePtr = new IntList();
    
    //Set the new node to the inputted value
    ( *newNode ).head->value = val;
    
    if ( head == NULL || (head->value == -1 && head->next == NULL) )
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
    IntList *nodePtr = new IntList();
    IntList *previousNode = new IntList();
    
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
        if( (* nodePtr).head == head )
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
void IntList::displayList()
{
    //Variable declarations
    IntList *nodePtr = new IntList();
    
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
    newNode = new IntList();
    nodePtr = new IntList();
    previousNode = new IntList();
    
    //Set previous node to NULL
    ( *previousNode ).head = NULL;
    
    //Store newNode with the inputted value
    ( *newNode ).head->value = val;
    
    if ( !head )
    {
        head = ( *newNode ).head;
        ( *newNode ).head->next = NULL;
    }
    else
    {
        ( *nodePtr ).head = head;
        
        ( *previousNode ).head = NULL;
        
        while ( ( *nodePtr ).head != NULL && cntr < (pos - 1) )
        {
            ( *previousNode ).head = ( *nodePtr ).head;
            ( *nodePtr ).head = ( *nodePtr ).head->next;
            cntr++;
        }
        
        if ( ( *previousNode ).head == NULL )
        {
            head = ( *newNode ).head;
            ( *newNode ).head->next = ( *nodePtr ).head;
        }
        
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
    nodePtr = new IntList();
    previousNode = new IntList();
    
    if ( !head )
    {
        ( *nodePtr ).head = head->next;
        delete head;
        head = ( *nodePtr ).head;
    }
    
    else
    {
        ( *nodePtr ).head = head;
        
        while ( ( *nodePtr ).head != NULL && cntr <  ( pos - 1 ) )
        {
            //Set the previous node to the current node
            ( *previousNode ).head = ( *nodePtr ).head;
            
            //Set the current node to the next node
            ( *nodePtr ).head = ( *nodePtr ).head->next;
            cntr++;
        }
        
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
    IntList *nodePtr = new IntList();
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
