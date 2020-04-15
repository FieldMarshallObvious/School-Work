//
//  IntList.cpp
//  
//
//  Created by Noah del Angel on 4/11/20.
//
#include <cstdlib>
#include <iostream>

#include "IntList.h"

using namespace std;

//Global Variables


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

IntList::IntList( const IntList &List )
{
    ListNode *newNode = new ListNode;
    
    newNode = List.head;
    
    head = newNode;
}

IntList::~IntList( )
{
    if( head != NULL )
    {
        delete head;
        head = NULL;
    }
}

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

void IntList::removeByPos( int pos )
{
    
}

int IntList::search( int val )
{
    return 0;
}
