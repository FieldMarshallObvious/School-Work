// Specification file for the IntList class
#ifndef INTLIST_H
#define INTLIST_H

class IntList
{
private:
   // Declare a structure for the list
   struct ListNode
   {
      int value;
      struct ListNode *next;
   };

   ListNode *head;   // List head pointer

public:
   // Constructor
   IntList();

   // Copy constructor
   IntList(const IntList &);

   // Destructor
   ~IntList();

   // List operations
   void appendNode(int val);
   void removeByVal(int val);
   void displayList();
   void insertByPos(int val, int pos);
   void removeByPos(int pos);
   int search(int val);
   void setValue(int val);
};

#endif /* INTLIST_H_ */
