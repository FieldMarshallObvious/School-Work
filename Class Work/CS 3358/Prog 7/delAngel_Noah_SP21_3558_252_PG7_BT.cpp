#include <iostream>
using namespace std;
class BinarySearchTree {
public:
    int size;
    int* array;

    void insertE1ement(int x);
    void searchE1ement(int x);
    void preOrder( );
    void preOrder( int loc );
    void postOrder( );
    void postOrder ( int loc );
    void displayLeafValues( );
    void displayLeafValues( int loc );

    int treeLeafsCount();
    int extendSize(int x);

    BinarySearchTree(int size) {
        cout << size << endl;
        int newSize = extendSize(size);

        cout << newSize << endl;

        array = new int[newSize];

        for(int x = 0; x < size; x++) {
            array[x] = NULL;
            cout << array[x] << endl;
        }

    }
};

void BinarySearchTree::insertE1ement(int x) {
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

void BinarySearchTree::searchE1ement(int x)
{
    int currerntIndex = 0;
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
            currentIndex = (@ * currentIndex + 1);
        }
    }
}

void BinarySearchTree::preOrder( )
{
    // Variable declarations
    int curNode = 0;

    cout << array[curNode] << endl;

    // Move to left node
    preOrder( ( curNode * 2 ) + 1 );

    // Move to right node
    preOrder( ( curNode * 2 ) + 2 );

}

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

void BinarySearchTree::postOrder( )
{
    // Variable declarations
    int curNode = 0;

    // Move to the left node
    postOrder( ( curNode * 2) + 1 );

    // Move to the right node
    postOrder( ( curNode * 2 ) + 2 );

    cout << array[curNode] << endl;
}

void BinarySearchTree::postOrder ( int loc )
{
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

int BinarySearchTree::extendSize(int x) {
    int value = 0;
    for(int y = 0; y < x + 1; y++) {
        value = (2 * value) + 2;
        cout << value << endl;
    }
    return value;
}



int main( )
{
    BinarySearchTree tree(20);

    cout << "Binary Search Tree by Noah del Angel.\n\n";

    cout << "Inserting Nodes.\n\n";

    tree.insertE1ement(4);
    tree.insertE1ement(6);
    tree.insertE1ement(9);
    tree.insertE1ement(3);
    tree.insertE1ement(2);
    tree.insertE1ement(8);

    cout << "Building BST is completed.\n\n";

    // Pre-Order Traversal .
    cout << "Pre-Order Traversal of the BST : \n\n";
    tree.preOrder();

    // Post-Order Traversal .
    cout << "Post-Order Traversal of the BST : \n\n";
    tree.postOrder();
/*
    // Counting Number of Leafs .
    cout << "\n\nNumber of Leafs =   " <<
    tree.treeLeafsCount() ;

    // Display leaf values of BST
    cout << "\n\nHere are the leaf values in the BST : \n\n";
    tree.displayLeafValues();

    // Searching for an element
    cout << "\n\nSearching for 9  in the BST:\n\n";
    tree.searchE1ement(9);

    // Searching for an element in BST
    cout << "\n\nSearching for 5  in the BST:\n\n";
    tree.searchE1ement(5);

    // Deleting an element
    cout << "\n\nDeleting 7 from the BST:\n\n";
    tree.deleteE1ement(7);

    // Deleting an element
    cout << "\n\nDeleting 2 from the BST:\n\n";
    tree.deleteE1ement(2);

    // Display final tree
    cout << "\n\nDisplaying final BST:\n\n";

*/

    cout << "\n\n\nNoah del Angel - April 30 , 2021\n\n";
}
