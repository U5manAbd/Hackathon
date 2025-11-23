#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;

    Node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

// ---------- Utility Functions ----------
int getHeight(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// ---------- Rotations ----------

// Right Rotation (for LL case)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x; // New root
}

// Left Rotation (for RR case)
Node* leftRotate(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;

    // Perform rotation
    x->left = y;
    y->right = T2;

    // Update heights
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x; // New root
}

// ---------- Insert Operation ----------
Node* insertNode(Node* root, int key) {

    // 1. Normal BST insertion
    if (!root)
        return new Node(key);

    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    else
        return root; // No duplicates

    // 2. Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3. Get balance factor
    int bf = getBalance(root);

    // 4. Fix imbalance

    // LL Case
    if (bf > 1 && key < root->left->key)
        return rightRotate(root);

    // RR Case
    if (bf < -1 && key > root->right->key)
        return leftRotate(root);

    // LR Case
    if (bf > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (bf < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; // Balanced
}

// ---------- Search ----------
bool searchNode(Node* root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    if (key < root->key) return searchNode(root->left, key);
    return searchNode(root->right, key);
}

// ---------- Find Min Value Node (for deletion) ----------
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// ---------- Deletion ----------
Node* deleteNode(Node* root, int key) {

    if (!root) return root;

    // 1. Normal BST deletion
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        // Node with 1 or 0 children
        if (!root->left || !root->right) {

            Node* temp = root->left ? root->left : root->right;

            if (!temp) { // No child
                temp = root;
                root = nullptr;
            } else { // One child
                *root = *temp;
            }

            delete temp;
        } 
        else {
            // Node with 2 children → get inorder successor
            Node* temp = minValueNode(root->right);
            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    // 2. Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3. Get balance factor
    int bf = getBalance(root);

    // 4. Fix imbalances

    // LL Case
    if (bf > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (bf > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (bf < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (bf < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; // Balanced
}

// ---------- Traversal ----------
void preOrder(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// ---------- Main (Demo) ----------
int main() {
    Node* root = nullptr;

    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    cout << "Preorder traversal of AVL Tree:\n";
    preOrder(root);

    cout << "\nSearching 25: " << (searchNode(root, 25) ? "Found" : "Not Found");

    root = deleteNode(root, 40);

    cout << "\nAfter deleting 40 (preorder):\n";
    preOrder(root);

    return 0;
}
