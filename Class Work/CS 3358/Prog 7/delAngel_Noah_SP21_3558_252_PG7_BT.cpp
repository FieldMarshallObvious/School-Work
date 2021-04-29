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
    void treeLeafsCount( int loc, int &sum );
    void deleteE1ement( int value );
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

void BinarySearchTree::preOrder( )
{
    // Variable declarations
    int curNode = 0;

    cout << array[curNode] << endl;

    // Move to left node
    preOrder( ( curNode * 2 ) + 1 );

    // Move to right node
    preOrder( ( curNode * 2 ) + 2 );

    cout << endl;

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

    cout << array[curNode] << endl << endl;
}

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
void BinarySearchTree::displayLeafValues( )
{
    // Variable declarations
    int curNode = 0;

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

void BinarySearchTree::deleteE1ement( int value )
{
    // Variable declarations
    int curNode = 0,
        temp,
        minRight;

    // Call function to the delete the desired element
    deleteElement( value, curNode );
}

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

int BinarySearchTree::minElement( int loc )
{
    if( array[loc] == NULL )
        return loc;
    else
        return minElement( ( loc * 2 ) + 1 );
}

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

    // Counting Number of Leafs .
    cout << "\n\nNumber of Leafs = " <<
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
    tree.displayTree(0);

    cout << "\n\n\nNoah del Angel - April 30 , 2021\n\n";
}
