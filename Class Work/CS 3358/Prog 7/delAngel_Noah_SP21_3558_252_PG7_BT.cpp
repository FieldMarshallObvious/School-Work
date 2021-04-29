// Author: Noah del Angel
// Due Date: 4/29/2021
// Assignment Number: 7
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// Manipulation of binary search
// trees, using array implentation.
#include <iostream>
using namespace std;
class BinarySearchTree {
public:
    int size;   // Holds the size of the array
    int* array; // Holds the pointer for the first index
                // in the array

    void insertElement(int x);
    void searchElement(int x);
    void preOrder( );
    void preOrder( int loc );
    void postOrder( );
    void postOrder ( int loc );
    void displayLeafValues( );
    void displayLeafValues( int loc );
    void treeLeafsCount( int loc, int &sum );
    void insertElement( int value );
    void displayTree( int loc );


    int minElement( int loc );
    int treeLeafsCount();
    int deleteElement( int value, int loc );
    int extendSize(int x);

    BinarySearchTree(int size) {
        int newSize = extendSize(size);

        array = new int[newSize];

        for(int x = 0; x < size; x++) {
            array[x] = NULL;
        }

    }
};

//**************************************************
// Inserts a node in the binary search with the
// inputted data
//
// x - The data to be inserted
//**************************************************
void BinarySearchTree::insertElement(int x) {
    int currentIndex = 0;
    cout << "Adding: " << x;
    while(true) {
        if(array[currentIndex] == NULL) {
            array[currentIndex] = x;
            cout << " Inserted at index: " << currentIndex << endl;
            break;
        } else if(array[currentIndex] <= x) {
            if(array[currentIndex] == x) {
                cout << "ERROR!-- Repeating element" << endl;
                break;
            } else
                cout << " Right ";
            currentIndex = (2 * currentIndex + 2);
        } else if (array[currentIndex] >= x) {
                if(array[currentIndex] == x) {
                    cout << "ERROR!-- Repeating element" << endl;
                    break;
                } else
                    cout << " Left ";
                currentIndex = (2 * currentIndex + 1);

        }
    }
}

//**************************************************
// Searches the binary tree for inputted data
//
// x - Holds the data to be found
//**************************************************
void BinarySearchTree::searchElement(int x)
{
    int currentIndex = 0;
    while(true) {
        if(array[currentIndex] == NULL) {
            cout << "Not Found" << endl;
            break;
        }
        if(array[currentIndex] == x) {
            cout << "Found at index: " << currentIndex << endl;
            break;
        } else if (array[currentIndex] < x) {
            currentIndex = (2 * currentIndex + 2);
        } else if (array[currentIndex] > x) {
            currentIndex = (2 * currentIndex + 1);
        }
    }
}

//**************************************************
// Calls recursive function to display the array
// in pre-order, and also prints the root node
//
//**************************************************
void BinarySearchTree::preOrder( )
{
    // Variable declarations
    int curNode = 0;    // Startiting posistion
                        // in the array

    cout << array[curNode] << endl;

    // Move to left node
    preOrder( ( curNode * 2 ) + 1 );

    // Move to right node
    preOrder( ( curNode * 2 ) + 2 );

    cout << endl;

}

//**************************************************
// Recursive function to display the array in
// pre order
//
// loc - Holds the current position in the tree
//**************************************************
void BinarySearchTree::preOrder( int loc )
{
    // If still in the tree
    if( array[loc] != NULL )
    {
        cout << array[loc] << endl;

        // Move to left node
        preOrder( ( loc * 2 ) + 1 );

        // Move to the right node
        preOrder( ( loc * 2 ) + 2);
    }

}

//**************************************************
// Calls recursive function to display the array
// in post-order, and also prints the last node
//
//**************************************************
void BinarySearchTree::postOrder( )
{
    // Variable declarations
    int curNode = 0;    // Startiting posistion
                        // in the array


    // Move to the left node
    postOrder( ( curNode * 2) + 1 );

    // Move to the right node
    postOrder( ( curNode * 2 ) + 2 );

    cout << array[curNode] << endl << endl;
}

//**************************************************
// Recursive function to display the array in
// post order
//
// loc - Holds the current position in the tree
//**************************************************
void BinarySearchTree::postOrder ( int loc )
{
    // If there is still nodes
    // order the array
    if( array[loc] != NULL )
    {
        // Move to the left node
        postOrder( ( loc * 2 ) + 1 );

        // Move to the right node;
        postOrder( ( loc * 2 ) + 2 );

        // Print the value of the current node
        cout << array[loc] << endl;
    }
}

//**************************************************
// Calls recursive function to display the leaf
// nodes of the BST. And, also runs checks on
// root node to determine if there are children
//
//**************************************************
void BinarySearchTree::displayLeafValues( )
{
    // Variable declarations
    int curNode = 0;    // Startiting posistion
                        // in the array

    // If the current location is null, return
    if( array[curNode] == NULL )
        return;

    // If neither of the children exist,
    // then print the node
    if( array[( ( curNode * 2 ) + 1 )] == NULL &&
        array[( ( curNode * 2 ) + 2 )] == NULL )
        cout << array[curNode] << endl;

    // Move to the left node
    displayLeafValues( ( curNode * 2) + 1 );

    // Move to the right node
    displayLeafValues( ( curNode * 2) + 2 );
}

//**************************************************
// Recursive function to display the leaf values
// of the array
//
// loc - Holds the current position in the tree
//**************************************************
void BinarySearchTree::displayLeafValues( int loc )
{
    // If the current location is null, return
    if( array[loc] == NULL )
        return;

    // If neither of the children exist,
    // then print the node
    if( array[( ( loc * 2 ) + 1 )] == NULL &&
        array[( ( loc * 2 ) + 2 )] == NULL )
        cout << array[loc] << endl;


    // Move to the right
    displayLeafValues( ( loc * 2) + 1 );

    // Move to the left
    displayLeafValues( ( loc * 2) + 2 );

}

//**************************************************
// Calls recursive function to remove the
// the element with the inputted value from the array
//
// value - Holds value to be removed
//**************************************************
void BinarySearchTree::deleteElement( int value )
{
    // Variable declarations
    int curNode = 0;    // Startiting posistion
                        // in the array
    
    // Call function to the delete the desired element
    deleteElement( value, curNode );
}


//**************************************************
// Recursive function to display the BST in
// in-order
//
// loc - Holds the current position in the tree
//**************************************************
void BinarySearchTree::displayTree( int loc )
{
    // If the current location is null, return
    if( array[loc] == NULL )
        return;

    // Move to the left node
    displayTree( ( loc * 2) + 1 );

    // If neither of the children exist,
    // then print the node
    if( array[loc] != NULL )
        cout << array[loc] << " at index: " << loc << endl;


    // Move to the right node
    displayTree( ( loc * 2) + 2 );
}

//**************************************************
// Recursive function to remove a desired element
// from the BST, using the min right rule
//
// value - Holds value to be removed
// loc - Holds the current position in the tree
//**************************************************
int BinarySearchTree::deleteElement( int value, int loc )
{
    // Variable declarations
    int temp = 0,
        minRight;

    // If the current item
    if( array[loc] != NULL )
    {
        // If the value is less than the current node
        // move to the left
        if( value < array[loc] )
            array[( loc * 2 ) + 1] = deleteElement( value, ( loc * 2 ) + 1 );

        // If the value is greater than the node
        // move to the right
        else if ( value > array[loc] )
            array[( loc * 2 ) + 2] = deleteElement( value, ( loc * 2 ) + 2 );

        else
        {
            // If the left child is empty
            // delete the current node
            // and return the right node
            if ( array[( loc * 2 ) + 1] == NULL )
            {
                temp = ( loc * 2 ) + 2;
                array[loc] = NULL;

                cout << value << " is deleted" << endl;
                return array[temp];
            }

            // If the richt child is empty
            // delete the current node
            // and return the left node
            else if ( array[( loc * 2 ) + 2] == NULL )
            {
                temp = ( loc * 2 ) + 1;
                array[loc] = NULL;

                cout << value << " is deleted" << endl;
                return array[temp];
            }

            // If a node has two children
            // get the smallest child
            temp = minElement( array[( loc * 2 ) + 2] );

            // Copy the next inorder item
            // to this node
            array[loc] = array[temp];

            // Delete the next in order item
            array[( loc * 2 ) + 2] = deleteElement( array[temp], ( loc * 2 ) + 2);
        }
    }

    // If the value to be deleted is not
    // found then output that
    else
        cout << value << " is not found" << endl;

    return array[loc];
}

//**************************************************
// Recursive function to find the minium element
// from the given posistion
//
// loc - Holds the current position in the tree
// returns the posistion of the minium element
//**************************************************
int BinarySearchTree::minElement( int loc )
{
    if( array[loc] == NULL )
        return loc;
    else
        return minElement( ( loc * 2 ) + 1 );
}

//**************************************************
// Calls the recursive function to count
// the tree leaves, and also checks the root
// to determine if it is a leaf
//
// returns the number of leaves in the BST
//**************************************************
int BinarySearchTree::treeLeafsCount()
{
    // Variable declarations
    int sum = 0,
        curNode = 0;

        // If the current location is null, return
    if( array[curNode] == NULL )
        return sum;

    // If neither of the children exist,
    // then print the node
    if( array[( ( curNode * 2 ) + 1 )] == NULL &&
        array[( ( curNode * 2 ) + 2 )] == NULL )
        sum++;

    // Move to the left node
    treeLeafsCount( ( curNode * 2) + 1, sum );

    // Move to the right node
    treeLeafsCount( ( curNode * 2) + 2, sum );

    return sum;
}

//**************************************************
// Recusrive function to determine 
//
// returns the number of leaves in the BST
//**************************************************
void BinarySearchTree::treeLeafsCount( int loc, int &sum )
{
    // If the current location is null, return
    if( array[loc] == NULL )
        return;

    // If neither of the children exist,
    // then print the node
    if( array[( ( loc * 2 ) + 1 )] == NULL &&
        array[( ( loc * 2 ) + 2 )] == NULL )
        sum++;

    // Move to the right
    treeLeafsCount( ( loc * 2) + 1, sum );

    //  Move to the left
    treeLeafsCount( ( loc * 2) + 2, sum );
}

int BinarySearchTree::extendSize(int x) {
    int value = 0;
    for(int y = 0; y < x + 1; y++) {
        value = (2 * value) + 2;
    }
    return value;
}



int main( )
{
    BinarySearchTree tree(20);

    cout << "Binary Search Tree by Noah del Angel.\n\n";

    cout << "Inserting Nodes.\n\n";

    tree.insertElement(4);
    tree.insertElement(6);
    tree.insertElement(9);
    tree.insertElement(3);
    tree.insertElement(2);
    tree.insertElement(8);

    cout << "Building BST is completed.\n\n";

    // Pre-Order Traversal .
    cout << "Pre-Order Traversal of the BST : \n\n";
    tree.preOrder();

    // Post-Order Traversal .
    cout << "Post-Order Traversal of the BST : \n\n";
    tree.postOrder();

    // Counting Number of Leafs .
    cout << "\n\nNumber of Leafs = " <<
    tree.treeLeafsCount() ;

    // Display leaf values of BST
    cout << "\n\nHere are the leaf values in the BST : \n\n";
    tree.displayLeafValues();

    // Searching for an element
    cout << "\n\nSearching for 9  in the BST:\n\n";
    tree.searchElement(9);

    // Searching for an element in BST
    cout << "\n\nSearching for 5  in the BST:\n\n";
    tree.searchElement(5);

    // Deleting an element
    cout << "\n\nDeleting 7 from the BST:\n\n";
    tree.deleteE1ement(7);

    // Deleting an element
    cout << "\n\nDeleting 2 from the BST:\n\n";
    tree.deleteE1ement(2);

    // Display final tree
    cout << "\n\nDisplaying final BST:\n\n";
    tree.displayTree(0);

    cout << "\n\n\nNoah del Angel - April 30 , 2021\n\n";
}
