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
    delete head;
    head = NULL;
}

void IntList::appendNode( int val )
{
    //Variable delcarations
    IntList *newNode;
    IntList *nodePtr;
    
    //Create new node
    newNode = new IntList();
    
    ( *newNode ).head->value = val;
    
    if ( head == NULL )
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
    IntList *nodePtr;
    IntList *previousNode;
    
    if ( !head )
        return;
    
    if( head->value == val )
    {
        ( *nodePtr ).head = head->next;
        
        delete head;
        
        head = ( *nodePtr ).head;
    }
    
    else
    {
        (*nodePtr).head = head;
        
        while ( ( *nodePtr ).head != NULL && ( *nodePtr ).head->value != val )
        {
            ( *previousNode ).head = ( *nodePtr ).head;
            
            ( *nodePtr ).head = ( *nodePtr ).head->next;
        }
    }
}

void IntList::displayList()
{
    //Variable declarations
    IntList *nodePtr;
    
    if( !head )
        return;
    else
    {
        ( *nodePtr ).head = head;
        while ( ( *nodePtr ).head != NULL )
        {
            cout << ( *nodePtr ).head->value;
            
            if( ( *nodePtr ).head->next != NULL )
                cout << " -> ";
        }
        cout << endl;
    }
}

void IntList::insertByPos( int val, int pos )
{
    
}

void IntList::removeByPos( int pos )
{
    
}

int IntList::search( int val )
{
    return 0;
}
