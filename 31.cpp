// Implement a binary search tree with insertion, search and in-order traversal.

#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    // C++ constructor with a member initiallizer list.
    // ClassName(Type param) : member1(value1), member2(value2), ... {}
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
/*BST is a class that manages nodes of type Node.
root is a private pointer to the top node of the tree.
Everything related to tree operations (insertion, search, traversals, deletion) lives inside this class.*/

class BST {
private:
    Node* root;

    // --- Helper functions ---

    // Recursive insertion
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
/*each Node contains:
data → the integer value stored in that node.
left → a pointer to the left child Node (or nullptr if none).
right → a pointer to the right child Node (or nullptr if none).

node is a pointer to a Node (Node*).
To access members of a struct via a pointer, you use ->.
node->left means “follow the pointer node and access its left field”.
If you had a Node object, not a pointer, you’d use .:
Node n(10);
n.left = nullptr; // object, use dot

Compare the value to insert (val) with node->data.
If val is smaller, we go left.
Call insert(node->left, val) recursively:
This returns a pointer to the new subtree (or unchanged subtree).
Assign it back: node->left = ...
Ensures that if a new node was created, it is linked to this node’s left.
*/
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    // Recursive search
    bool search(Node* node, int val) {
        if (!node) return false;
        if (val == node->data) return true;
        else if (val < node->data)
            return search(node->left, val);
        else
            return search(node->right, val);
    }
/*
 node is a pointer to a Node.
 if (!node) checks if the pointer is null (i.e., we've reached a leaf's child).
 inorder is declared as void, meaning it does not return a value.
 Writing just:return;
 stops the function immediately and goes back to the caller.
 There is no value returned, because the function’s return type is void
 When traversing a tree, leaf nodes have nullptr children.
 Without this check, recursion would try to dereference a null pointer (node->left or node->right), causing a crash.
  */
    // Recursive in-order traversal
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Recursive pre-order traversal
    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Recursive post-order traversal
    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // Find minimum node in a subtree
    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    // Recursive deletion
    Node* remove(Node* node, int val) {
        if (!node) return nullptr;

        if (val < node->data)
            node->left = remove(node->left, val);
        else if (val > node->data)
            node->right = remove(node->right, val);
        else {
            // Node found
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                // Node with 2 children: find inorder successor
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }
        return node;
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) { root = insert(root, val); }
    bool search(int val) { return search(root, val); }
    void remove(int val) { root = remove(root, val); }

    void inorder() { inorder(root); cout << endl; }
    void preorder() { preorder(root); cout << endl; }
    void postorder() { postorder(root); cout << endl; }
};

int main() {
    BST tree;

    // Insert nodes
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "In-order traversal: ";
    tree.inorder();   // 20 30 40 50 60 70 80

    cout << "Pre-order traversal: ";
    tree.preorder();  // 50 30 20 40 70 60 80

    cout << "Post-order traversal: ";
    tree.postorder(); // 20 40 30 60 80 70 50

    // Search
    int key = 60;
    if (tree.search(key))
        cout << key << " found in the tree.\n";
    else
        cout << key << " not found in the tree.\n";

    key = 25;
    if (tree.search(key))
        cout << key << " found in the tree.\n";
    else
        cout << key << " not found in the tree.\n";

    // Delete a node
    cout << "Deleting 30...\n";
    tree.remove(30);

    cout << "In-order after deletion: ";
    tree.inorder();  // 20 40 50 60 70 80
    tree.insert(30);
    tree.inorder();

    return 0;
}

/*
 Why it’s mostly safe:
We never dereference null pointers without checking (if (!node) return;).
We only access node->left, node->right, and node->data when node is valid. 
So access violations (segfaults) won’t happen in this simple code.
 
What’s not safe / missing
Memory leaks:
When you create a node:
Node* newNode = new Node(val);
That memory lives until the program ends, because we never delete the nodes.
In a big program or with lots of insertions/deletions, this would leak memory.
Deletion fixes this:
If you implement deleteNode(int val), you must delete the node pointer after removing it from the tree, otherwise memory leaks.
Dangling pointers:
If a node is deleted but some code still has a pointer to it, dereferencing it causes undefined behavior.
Our current code avoids this because we don’t store extra external pointers to nodes.
*/
