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


IntList::IntList()
{

    (*head).value = -1;
    
    (*head).next = NULL;
}

IntList::IntList(const IntList &List)
{
    //(*head) = List;
}

IntList::~IntList()
{
    
}

void IntList::appendNode(int val)
{
    //Variable delcarations
    IntList *newNode;
    IntList *nodePtr;
    
    //Create new node
    newNode = new IntList;
    
    ( *newNode ).head->value = val;
    
    if ( !head )
    {
        head = ( *newNode ).head;
    }
    
    else
    {
        (*nodePtr).head = head;
        
        while ( ( *nodePtr ).head->next )
        {
            (*nodePtr).head = ( *nodePtr ).head->next;
        }
        
        (*nodePtr).head->next = ( *newNode ).head;
    }
}

void IntList::removeByVal(int val)
{
    //Variable declarations
    ListNode *nodePtr;
    ListNode *previousNode;
    
    if ( !head )
        return;
    
    if( (*head)->value == val )
    {
        
    }
}

void IntList::displayList()
{
    
}

void IntList::insertByPos(int val, int pos)
{
    
}

void IntList::removeByPos(int pos)
{
    
}

int IntList::search(int val)
{
    return 0;
}
