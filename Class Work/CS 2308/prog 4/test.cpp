// This program is used to test the correctness
// of the member functions implemented in the IntList class

#include <iostream>
#include <cstdlib>

using namespace std;

#include "IntList.h"

int main()
{
   // Create an instance of IntList
   IntList list;

   // Build the list
   list.appendNode(2);  // Append 2 to the list
   list.appendNode(4);  // Append 4 to the list
   list.appendNode(6);  // Append 6 to the list
   list.appendNode(8);  // Append 8 to the list
   list.appendNode(10);  // Append 10 to the list

   // Display the nodes.
   cout << "Here are the initial values:\n";
   list.displayList();
   cout << endl;

   // Insert the value 5 into the list.
   cout << "Now inserting the value 5 at position 2.\n";
   list.insertByPos(5, 2);

   // Display the nodes now.
   cout << "Here are the nodes now.\n";
   list.displayList();
   cout << endl;

   // Delete the node holding 10.
   cout << "Now deleting the node holding 10.\n";
   list.removeByVal(10);

   // Display the nodes.
   cout << "Here are the nodes left.\n";
   list.displayList();
   cout << endl;

   // Remove node at position 1.
   cout << "Now removing node at position 1.\n";
   list.removeByPos(1);
   list.displayList();
   cout << endl;

   // Try a position that is too big.
   cout << "Now try to remove node at position 99.\n";
   list.removeByPos(99);
   list.displayList();
   cout << endl;

   // Search the position of node with value 6.
   cout << "Now search the position of node with value 6.\n";
   cout << "The node with value 6 is located at position: " << list.search(6) << endl;
   cout << endl;

   // Search the position of node with value -999 (does not exist).
   cout << "Now search the position of node with value -999 (does not exist).\n";
   cout << "The node with value -999 is located at position: " << list.search(-999) << endl;
   cout << endl;

   // Delete the node with value 6.
   cout << "Now delete the node with value 6.\n";
   list.removeByVal(6);
   list.displayList();
   cout << endl;

   // Copy the value in list to the second list.
   cout << "Here are the nodes in the second list.\n";
   IntList list2 = list;
   list2.displayList();
   cout << endl;

   return 0;
}
